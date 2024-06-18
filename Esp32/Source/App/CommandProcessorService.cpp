#include "CommandProcessorService.h"
#include "Logger.h"

namespace Applications
{

using Utilities::Logger;
using Common::CommandBase;

void CommandProcessorService::Run()
{
    Logger::LogInfo(Logger::LogSource::Command, "CommandProcessorService Started.");

    CommandBase cmd;
    for(;;)
    {
        if (_cmdQueue.Dequeue(&cmd)) 
        {
            Logger::LogInfo(Logger::LogSource::Command,"Received value: %d\n", static_cast<uint16_t>(cmd.CommandId));
        }
    }
}


void CommandProcessorService::EnqueueCommand(CommandBase& command)
{
    _cmdQueue.Enqueue(&command);
}

}