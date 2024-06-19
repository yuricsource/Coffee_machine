#pragma once

#include <stdio.h>
#include <stdint.h>
#include "Protocol/CommonTypes.h"

namespace Protocols
{
class MqttClient
{
public:
    MqttClient(MqttBrokerAddress brokerAddress, MqttConnectionName name, ConnectionPassword password, uint16_t connectionPort);

private:
    MqttConnectionName _connectionName;
    ConnectionPassword _connectionPassword;
    MqttBrokerAddress _brokerAddress;
    uint16_t _connectionPort;
};

} // namespace Protocol