#pragma once
#include "Hardware.h"
#include <array>

namespace Applications
{

class DeviceClientService : public cpp_freertos::Thread
{
public:

    DeviceClientService() : 
        cpp_freertos::Thread("CLNTSVC", configCLIENT_STACK_DEPTH, 3)
    {
    }

private:
protected:
    void Run() override;

private:
private:
    /// @brief	Hide Copy constructor.
    DeviceClientService(const DeviceClientService &) = delete;

    /// @brief	Hide Assignment operator.
    DeviceClientService &operator=(const DeviceClientService &) = delete;

    /// @brief	Hide Move constructor.
    DeviceClientService(DeviceClientService &&) = delete;

    /// @brief	Hide Move assignment operator.
    DeviceClientService &operator=(DeviceClientService &&) = delete;
};

} // namespace Applications