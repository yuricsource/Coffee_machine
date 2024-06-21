#pragma once

#include "Hardware.h"
#include "WifiService.h"
#include "CommandProcessorService.h"
#include "DeviceClientService.h"

namespace Applications
{

class ApplicationAgent
{
public:
    ApplicationAgent();

    void Initialize();

    static inline ApplicationAgent *Instance()
    {
        if (_applications == nullptr)
        {
            _applications = new ApplicationAgent();
        }
        return _applications;
    }

    WifiService* GetWifiService() { return _wifiService; }
    CommandProcessorService* GetCommandService() { return _commandProcessor; }
    DeviceClientService* GetDeviceClientService() { return _deviceClientService; }

private:
    static ApplicationAgent *_applications;
    WifiService * _wifiService;
    CommandProcessorService * _commandProcessor;
    DeviceClientService * _deviceClientService;

private:
    /// @brief	Hide Copy constructor.
    ApplicationAgent(const ApplicationAgent &) = delete;

    /// @brief	Hide Assignment operator.
    ApplicationAgent &operator=(const ApplicationAgent &) = delete;

    /// @brief	Hide Move constructor.
    ApplicationAgent(ApplicationAgent &&) = delete;

    /// @brief	Hide Move assignment operator.
    ApplicationAgent &operator=(ApplicationAgent &&) = delete;
};

} // namespace Applications