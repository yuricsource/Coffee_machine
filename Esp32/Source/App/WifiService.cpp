#include "WifiService.h"
#include "Logger.h"
// #include "RTOSExtra.h"
#include "DebugAssert.h"

namespace Applications
{

using Hal::Hardware;
using Utilities::Logger;
// using Configuration::BoardConfiguration;
// using Configuration::ConfigurationAgent;

void WifiService::ConfigurationUpdated()
{
    // memcpy(_ssid.data(), "Yuri_R2",sizeof("Yuri_R2"));
    // memcpy(_password.data(), "Australia4us",sizeof("Australia4us"));
    // memcpy(&_ipAddress, &configuration->GetConfiguration()->WifiConfig.IPAddress, sizeof(ip_addr_t));
    // memcpy(&_maskAddress, &configuration->GetConfiguration()->WifiConfig.Mask, sizeof(ip_addr_t));
    // memcpy(&_gatewayAddress, &configuration->GetConfiguration()->WifiConfig.GatewayAddress, sizeof(ip_addr_t));
    // memcpy(&_dnsServer, &configuration->GetConfiguration()->WifiConfig.DnsServer,  sizeof(ip_addr_t));
    changeState(WifiState::ResetAdapter);
}

void WifiService::changeState(WifiState wifiState)
{
    _wifiState = wifiState;
    Logger::LogInfo(Logger::LogSource::Wifi, "wifiState: %d",static_cast<uint8_t>(wifiState));
}


void WifiService::Run()
{
    // tcpip_adapter_init();
    //DebugAssert(esp_netif_init(), ESP_OK);

    WifiDriver &_wifiDriver = Hardware::Instance()->GetWifi();
    memcpy(_listWifiSettings[0].Ssid.data(), "Yuri_R2",sizeof("Yuri_R2"));
    memcpy(_listWifiSettings[0].Password.data(), "Australia4us",sizeof("Australia4us"));
    Logger::LogInfo(Logger::LogSource::Wifi, "Running Wifi.");
    for (;;)
    {
        vTaskDelay(100);
        switch (_wifiState)
        {
        case WifiState::Idle:
        {
            _connected = false;
            vTaskDelay(100);
            changeState(WifiState::ResetAdapter);
        }
        break;
        case WifiState::ResetAdapter:
        {
            _wifiDriver.Disable();
            changeState(WifiState::ConfigureTransmitter);
        }
        break;
        case WifiState::ConfigureTransmitter:
        {
            if (_wifiMode == WifiModeConfiguration::Client)
            {
                Logger::LogInfo(Logger::LogSource::Wifi, "SSID: %s.",_listWifiSettings[0].Ssid.data());
                _wifiDriver.SetMode(WifiModeConfiguration::Client);
                _wifiDriver.SetSsid(_listWifiSettings[0].Ssid.data(),_listWifiSettings[0].Ssid.size());
                _wifiDriver.SetPassword(_listWifiSettings[0].Password.data(),_listWifiSettings[0].Password.size());
                _wifiDriver.SetAuthentication(_authentication);
            }
            else
            {
               Logger::LogInfo(Logger::LogSource::Wifi, "SSID: %s.",_listWifiSettings[0].Ssid.data());
                _wifiDriver.SetMode(WifiModeConfiguration::HotSpot);
                _wifiDriver.SetSsid(_listWifiSettings[0].Ssid.data(),_listWifiSettings[0].Ssid.size());
                _wifiDriver.SetPassword(_listWifiSettings[0].Password.data(),_listWifiSettings[0].Password.size());
                _wifiDriver.SetAuthentication(_authentication);
                _wifiDriver.SetChannel(_channel);
            }
            _wifiDriver.Enable();
            changeState(WifiState::WaitingTransmitter);
        }
        case WifiState::WaitingTransmitter:
        {
            changeState(WifiState::PrepareWifiConnection);
        }
        break;
        case WifiState::PrepareWifiConnection:
        {
            if (_wifiMode == WifiModeConfiguration::Client)
            {
                if (_useDhcp)
                    changeState(WifiState::DhcpRequest);
                else
                    changeState(WifiState::StaticIpRequest);
            }
            else
            {
                changeState(WifiState::StartHotspot);
            }
        }
        break;
        case WifiState::StaticIpRequest:
        {
            changeState(WifiState::StaticIpDone);
        }
        break;
        case WifiState::StaticIpDone:
        {

        }
        break;
        case WifiState::DhcpRequest:
        {
            changeState(WifiState::DhcpWaiting);
        }
        break;
        case WifiState::DhcpWaiting:
        {
            // esp_netif_ip_info_t ip_info = {};
            // // esp_netif_t *gnetif = _wifiDriver.GetWifiClientNetif();
            
            // // assert(gnetif);
            // // DebugAssert(esp_netif_get_ip_info(gnetif, &ip_info), ESP_OK);
    
            // Logger::LogInfo(Logger::LogSource::Wifi, "Ip: %s",ip4addr_ntoa((const ip4_addr_t*)&ip_info.ip));
            // Hardware::Instance()->GetCamera().Init();
            // changeState(WifiState::DhcpDone);
            
        }
        break;
        case WifiState::DhcpDone:
        {
            
        }
        break;
        case WifiState::StartHotspot:
        {
            if (_useDhcp)
                    changeState(WifiState::StartDhcpServer);
                else
                    changeState(WifiState::StartDhcpServer);
        }
        break;
        case WifiState::SetStaticIp:
        {
            changeState(WifiState::StaticIpDone);
        }
        break;
        case WifiState::StartDhcpServer:
        {

            // esp_netif_ip_info_t ip_info = {};
            // // esp_netif_t *gnetif = _wifiDriver.GetWifiHostNetif();
            
            // // assert(gnetif);
            // // DebugAssert(esp_netif_get_ip_info(gnetif, &ip_info), ESP_OK);
    
            // Logger::LogInfo(Logger::LogSource::Wifi, "Ip: %s",ip4addr_ntoa((const ip4_addr_t*)&ip_info.ip));
            // Hardware::Instance()->GetCamera().Init();
            // changeState(WifiState::DhcpDone);
        }
        break;

        default:
            break;
        }
    }
}

} // namespace Applications