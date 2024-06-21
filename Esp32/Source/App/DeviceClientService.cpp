#include "DeviceClientService.h"
#include "Logger.h"

namespace Applications
{
using Utilities::Logger;

void DeviceClientService::Run()
{
    Logger::LogInfo(Logger::LogSource::Client, "DeviceClientService Started.");

   
    for(;;)
    {
      Delay(1000);
    }
}

}