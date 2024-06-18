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
#include "queue.hpp" 
#include "CommonCommandBase.h"

namespace Applications
{
using cpp_freertos::Queue;
using Common::CommandBase;
class CommandProcessorService : public cpp_freertos::Thread
{
public:

    static const uint8_t MaxCommandCount = 10;

    CommandProcessorService() : 
        cpp_freertos::Thread("CMDSVC", configWIFISVC_STACK_DEPTH, 3),
        _cmdQueue(MaxCommandCount, sizeof(CommandBase))
    {
    }

    void SetMotorPositionCommand(uint8_t angle);

private:
    void enqueueCommand(CommandBase& command);

protected:
    void Run() override;

private:
    Queue _cmdQueue; // Command List Queue 
    
private:
    /// @brief	Hide Copy constructor.
    CommandProcessorService(const CommandProcessorService &) = delete;

    /// @brief	Hide Assignment operator.
    CommandProcessorService &operator=(const CommandProcessorService &) = delete;

    /// @brief	Hide Move constructor.
    CommandProcessorService(CommandProcessorService &&) = delete;

    /// @brief	Hide Move assignment operator.
    CommandProcessorService &operator=(CommandProcessorService &&) = delete;
};

} // namespace Applications