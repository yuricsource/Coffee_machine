#pragma once
#include <stdint.h>
#include <array>

namespace Protocols
{

static constexpr uint8_t MqttNameMaxLength = 20;
using MqttConnectionName = std::array<uint8_t, MqttNameMaxLength>;
static_assert(sizeof(MqttConnectionName) == 20, "MqttConnectionName has invalid size.");

static constexpr uint8_t MqttBrokerAddressMaxLength = 128;
using MqttBrokerAddress = std::array<uint8_t, MqttBrokerAddressMaxLength>;
static_assert(sizeof(MqttBrokerAddress) == 128, "MqttBrokerAddress has invalid size.");

static constexpr uint8_t ConnectionPasswordMaxLength = 20;
using ConnectionPassword = std::array<uint8_t, ConnectionPasswordMaxLength>;
static_assert(sizeof(ConnectionPassword) == 20, "ConnectionPassword has invalid size.");

}