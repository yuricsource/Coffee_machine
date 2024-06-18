#include "ApplicationAgent.h"

namespace Applications
{

ApplicationAgent *ApplicationAgent::_applications;

ApplicationAgent::ApplicationAgent()
{
    if (_applications == nullptr)
    {
        _applications = this;
    }
    else
    {
        printf("Error!\n");
    }
}

void ApplicationAgent::Initialize()
{
    // Starting Wifi Service
    _wifiService = new WifiService();
    _wifiService->Start();

    // Starting Command Processor service
    _commandProcessor = new CommandProcessorService();
    _commandProcessor->Start();
}

} // namespace Applications
