
#include "WifiDriver.h"
#include "string.h"
#include "lwip/sockets.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "freertos/event_groups.h"
#include "Dwt.h"
#include "DebugAssert.h"
#include "esp_mac.h"
#include "Logger.h"

#ifdef __cplusplus
extern "C"
{
#endif
// #include "Wifi/WifiDefaultSettings.h"
#ifdef __cplusplus
}
#endif

namespace Hal
{
#define EXAMPLE_ESP_MAXIMUM_RETRY  5
#define WIFI_CONNECTED_BIT BIT0
static int s_retry_num = 0;
/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;
static WifiDriver::WifiDriverStatus *_driverStatusLevel;
static void wifi_event_handler(void *arg, esp_event_base_t event_base,
							   int32_t event_id, void *event_data)
{
	if (event_id == WIFI_EVENT_AP_STACONNECTED)
	{
		wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *)event_data;
		Utilities::Logger::LogInfo("station " MACSTR " join, AID=%d\n",
			   MAC2STR(event->mac), event->aid);
		if (_driverStatusLevel != nullptr)
			*_driverStatusLevel = Hal::WifiDriver::WifiDriverStatus::Connected;
	}
	else if (event_id == WIFI_EVENT_AP_STADISCONNECTED)
	{
		wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *)event_data;
		Utilities::Logger::LogInfo("station " MACSTR " leave, AID=%d\n",
			   MAC2STR(event->mac), event->aid);
		if (_driverStatusLevel != nullptr)
			*_driverStatusLevel = Hal::WifiDriver::WifiDriverStatus::Disconnected;
	}
	else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
	{
		esp_wifi_connect();
		if (_driverStatusLevel != nullptr)
			*_driverStatusLevel = Hal::WifiDriver::WifiDriverStatus::Starting;
	}
	else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
	{
		if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY)
		{
			esp_wifi_connect();
			xEventGroupClearBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
			s_retry_num++;
			Utilities::Logger::LogInfo("retry to connect to the AP\n");
		}
		Utilities::Logger::LogInfo("connect to the AP fail\n");
		if (_driverStatusLevel != nullptr)
			*_driverStatusLevel = Hal::WifiDriver::WifiDriverStatus::Disconnected;
	}
	else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
	{
		ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
		Utilities::Logger::LogInfo("got ip:" IPSTR, IP2STR(&event->ip_info.ip));
		s_retry_num = 0;
		xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
		if (_driverStatusLevel != nullptr)
			*_driverStatusLevel = Hal::WifiDriver::WifiDriverStatus::Connected;
	}
}

WifiDriver::WifiDriver()
{
	_driverStatusLevel = &_status;
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		nvs_flash_erase();
		ret = nvs_flash_init();	
	}
	s_wifi_event_group = xEventGroupCreate();
	esp_netif_init();
	esp_event_loop_create_default();
	_hotstopNetif = esp_netif_create_default_wifi_ap();
	assert(_hotstopNetif);
	_clientNetif = esp_netif_create_default_wifi_sta();
	assert(_clientNetif);
	esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL));
}

WifiDriver::~WifiDriver()
{
}

bool WifiDriver::SetSsid(const char *ssid, uint8_t len)
{
	if (_ssid.size() < len)
		return false;

	memset(_ssid.data(), 0, _ssid.size());
	memcpy(_ssid.data(), ssid, len);

	return true;
}

bool WifiDriver::SetPassword(const char *passwd, uint8_t len)
{
	if (_password.size() < len)
		return false;
	memset(_password.data(), 0, _password.size());
	memcpy(_password.data(), passwd, len);

	return true;
}

bool WifiDriver::SetMode(WifiModeConfiguration wifiConfiguration)
{
	if (_isEnabled)
		return false;

	_wifiConfiguration = wifiConfiguration;

	return true;
}

bool WifiDriver::SetAuthentication(WifiAuthenticationMode authentication)
{
	if (_isEnabled)
		return false;

	_authentication = authentication;

	return true;
}

void WifiDriver::ResetDriver()
{
	Disable();
	Dwt::DelayMicrosecond(100);
	Enable();
}

bool WifiDriver::SetChannel(uint8_t channel)
{
	if (_isEnabled)
		return false;

	_channel = channel;

	return true;
}

bool WifiDriver::Enable()
{
	if (_isEnabled)
		return true;

	wifi_config_t wifi_config = {};

	wifi_interface_t wifiMode = static_cast<wifi_interface_t>(_wifiConfiguration);

	if (_wifiConfiguration == WifiModeConfiguration::HotSpot)
	{
		strcpy((char *)wifi_config.ap.ssid, _ssid.data());
		wifi_config.ap.ssid_len = strlen(_ssid.data());
		wifi_config.ap.max_connection = 4;
		wifi_config.ap.authmode = static_cast<wifi_auth_mode_t>(_authentication);
		strcpy((char *)wifi_config.ap.password, _password.data());

		wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
		esp_wifi_init(&cfg);
		esp_wifi_set_mode(WIFI_MODE_AP);
		esp_wifi_start();
	}
	else if (_wifiConfiguration == WifiModeConfiguration::Client)
	{
		strcpy((char *)wifi_config.sta.password, _password.data());
		strcpy((char *)wifi_config.sta.ssid, _ssid.data());
		wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
		esp_wifi_init(&cfg);
		esp_wifi_set_mode(WIFI_MODE_STA);
		esp_wifi_start();
	}
	else
	{

	}

	esp_wifi_set_config(wifiMode, &wifi_config);

	_isEnabled = true;

	return _isEnabled;
}

bool WifiDriver::Disable()
{
	if (_isEnabled == false)
		return true;

	esp_wifi_disconnect();
	esp_wifi_stop();
	esp_wifi_deinit();

	_isEnabled = false;

	return true;
}
} // namespace Hal
