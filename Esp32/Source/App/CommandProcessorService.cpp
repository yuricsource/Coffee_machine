#include "CommandProcessorService.h"
#include "Logger.h"

namespace Applications
{

using Utilities::Logger;
using Common::CommandBase;
using Common::CommandId;

void CommandProcessorService::Run()
{
    Logger::LogInfo(Logger::LogSource::Command, "CommandProcessorService Started.");

    CommandBase cmd;
    for(;;)
    {
        if (_cmdQueue.Dequeue(&cmd)) 
        {
            Logger::LogInfo(Logger::LogSource::Command,"Received value: %d\n", static_cast<uint16_t>(cmd.Command));
            switch (cmd.Command)
            {
            case CommandId::SetMotorPosition:
                Logger::LogInfo(Logger::LogSource::Command,"SetMotorPosition Command Received: Angle = %d\n", static_cast<uint8_t>(cmd.MotorPosition.Angle));
                break;
            case CommandId::PrepareCoffeeMachine:
                Logger::LogInfo(Logger::LogSource::Command,"Prepare the coffee machine command received\n");
                	Delay(1000);
                    Hal::Hardware::Instance()->GetServoMotor().SetPositon(10);
                    Delay(1000);
                    Hal::Hardware::Instance()->GetServoMotor().SetPositon(100);
                    Delay(20000);
                    Hal::Hardware::Instance()->GetServoMotor().SetPositon(10);
                    Delay(1000);
                    Hal::Hardware::Instance()->GetServoMotor().SetPositon(100);
                break;

            default:
                Logger::LogInfo(Logger::LogSource::Command,"Unkown Command ID Received: %d\n", static_cast<uint16_t>(cmd.Command));
                break;
            }
        }
    }
}

void CommandProcessorService::SetMotorPositionCommand(uint8_t angle)
{
    CommandBase cmd;
    cmd.Command = Common::CommandId::SetMotorPosition;
    cmd.MotorPosition.Angle = angle;
    enqueueCommand(cmd);
}

void CommandProcessorService::SetPrepareCoffeeMachineCommand()
{
    CommandBase cmd;
    cmd.Command = Common::CommandId::PrepareCoffeeMachine;
    enqueueCommand(cmd);
}

void CommandProcessorService::enqueueCommand(CommandBase& command)
{
    _cmdQueue.Enqueue(&command);
}

}