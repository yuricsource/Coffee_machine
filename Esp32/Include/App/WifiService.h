#pragma once
#include "RTOSExtra.h"
#include "Hardware.h"
#include "freertos/FreeRTOS.h"
#include "RTOSExtra.h"
#include "freertos/task.h"
#include "thread.hpp"
#include "esp_err.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_wifi.h"
#include "WifiDriver.h"
#include "lwip/ip_addr.h"
// #include "ConfigurationAgent.h"
#include "Hardware.h"
#include <array>

namespace Applications
{

using Hal::WifiAuthenticationMode;
using Hal::WifiModeConfiguration;
using Hal::WifiSsid;
using Hal::WifiPassword;
using Hal::WifiDriver;
using std::array;

class WifiService : public cpp_freertos::Thread
{
public:
    WifiService() : cpp_freertos::Thread("WIFISVC", configWIFISVC_STACK_DEPTH, 3)
    {
    }

    inline bool IsConnected()
    {
        return _connected;
    }

    void ConfigurationUpdated();

    static const uint8_t MaxWifiListSettings = 10;

protected:
    void Run() override;

private:
    enum class WifiState : uint8_t
    {
        Idle,
        ResetAdapter,
        ConfigureTransmitter,
        WaitingTransmitter,
        PrepareWifiConnection,
        StaticIpRequest,
        StaticIpDone,
        DhcpStart,
        DhcpRequest,
        DhcpWaiting,
        DhcpDone,
        StartHotspot,
        SetStaticIp,
        StartDhcpServer,

        WifiStateCount
    };

    WifiState _wifiState = WifiState::Idle;
    bool _connected = false;
    bool _useDhcp = true;

    ip_addr_t _ipAddress = {};
    ip_addr_t _maskAddress = {};
    ip_addr_t _gatewayAddress = {};
    ip_addr_t _dnsServer = {};
	WifiAuthenticationMode _authentication = WifiAuthenticationMode::Open;
	WifiModeConfiguration _wifiMode = WifiModeConfiguration::Client;    
	uint8_t _channel = 8;
    
    class WifiSettings
    {
    public:
        WifiSsid Ssid = {};
        WifiPassword Password = {};
    };

    std::array <WifiSettings, MaxWifiListSettings> _listWifiSettings;
    void changeState(WifiState wifiState);
    const char *WifiStateStrings[static_cast<uint8_t>(WifiState::WifiStateCount)] = 
    {
        "Idle",
        "ResetAdapter",
        "ConfigureTransmitter",
        "WaitingTransmitter",
        "PrepareWifiConnection",
        "StaticIpRequest",
        "StaticIpDone",
        "DhcpStart",
        "DhcpRequest",
        "DhcpWaiting",
        "DhcpDone",
        "StartHotspot",
        "SetStaticIp",
        "StartDhcpServer"
    };
private:
    /// @brief	Hide Copy constructor.
    WifiService(const WifiService &) = delete;

    /// @brief	Hide Assignment operator.
    WifiService &operator=(const WifiService &) = delete;

    /// @brief	Hide Move constructor.
    WifiService(WifiService &&) = delete;

    /// @brief	Hide Move assignment operator.
    WifiService &operator=(WifiService &&) = delete;
};

} // namespace Applications