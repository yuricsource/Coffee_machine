#pragma once

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_log.h"

#include "Protocol/CommonTypes.h"

namespace Protocols
{
class MqttClient
{
public:
    MqttClient();
private:

    MqttConnectionName _connectionName;
    ConnectionPassword _connectionPassword;
    MqttBrokerAddress _brokerAddress;
    uint16_t _connectionPort;
};

} // namespace Protocol