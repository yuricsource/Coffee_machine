#include "Hardware.h"
#include <stdio.h>
#include "esp_idf_version.h"
#include "esp_mac.h"
#include "esp_private/esp_clk.h"
#include "soc/clk_tree_defs.h"
#include "esp_clk_tree.h"

namespace Hal
{

Hardware *Hardware::_pHardware;

Hardware::Hardware() :
	_wifiDriver()
{
	esp_chip_info(&_mcuInfo);
	esp_base_mac_addr_get(_macAdrress.data());
	esp_clk_tree_src_get_freq_hz(SOC_MOD_CLK_CPU, ESP_CLK_TREE_SRC_FREQ_PRECISION_APPROX, &_clockSpeed);
    printf("SDK Version         		: %s\n", (char *)esp_get_idf_version());
	printf("CPU Cores           		: %d\n", _mcuInfo.cores);
	printf("APB Clock           		: %ld Hz\n", _clockSpeed);
	printf("CPU Revision        		: %d\n", _mcuInfo.revision);
	printf("Embedded Flash      		: %s\n", (_mcuInfo.features & CHIP_FEATURE_EMB_FLASH) ? "YES" : "NO");
	printf("Wi-Fi Modle         		: %s\n", (_mcuInfo.features & CHIP_FEATURE_WIFI_BGN) ? "YES" : "NO");
	printf("Bluetooth Classic   		: %s\n", (_mcuInfo.features & CHIP_FEATURE_BT) ? "YES" : "NO");
	printf("Bluetooth LE        		: %s\n", (_mcuInfo.features & CHIP_FEATURE_BLE) ? "YES" : "NO");
	printf("MAC Address         		: %02X:%02X:%02X:%02X\n",
		   _macAdrress[0],
		   _macAdrress[1],
		   _macAdrress[2],
		   _macAdrress[3]);
	printf("MCU Free Heap       		: %ld\n", esp_get_free_heap_size());
	Dwt::DelayMicrosecond(10);
	Dwt::DelayMilliseconds(10);
    if (_pHardware == nullptr)
		_pHardware = this;
	else
		printf("!!! Error: Only one instance of System can be created !!!\n");
}

Hardware::~Hardware()
{
}

uint32_t Hardware::Milliseconds()
{
	return xTaskGetTickCount() * portTICK_PERIOD_MS;
}

void Hardware::SoftwareReset()
{
	esp_restart();
}

} // namespace Hal