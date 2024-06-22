#include "DeviceClientService.h"
#include "Logger.h"
#include "MqttClient.h"
#include "Protocol/CommonTypes.h"
#include "Protocol/Mqtt/MqttClient.h"

namespace Applications
{
using Utilities::Logger;
using Protocols::MqttConnectionName;
using Protocols::ConnectionPassword;
using Protocols::MqttBrokerAddress;
using Protocols::MqttClient;

void DeviceClientService::Run()
{
    Logger::LogInfo(Logger::LogSource::Client, "DeviceClientService Started.");
    Delay(6000);
    MqttConnectionName connectionName = {"ESP32C3"};
    ConnectionPassword connectionPassword = {"yuriflash"};
    MqttBrokerAddress brokerAddress = {"192.168.1.133"};
    uint16_t connectionPort = 1883;

//(MqttBrokerAddress brokerAddress, MqttConnectionName name, ConnectionPassword password, uint16_t connectionPort)
    MqttClient device(brokerAddress, connectionName, connectionPassword, connectionPort);

    for(;;)
    {
      Delay(1000);
    }
}
}