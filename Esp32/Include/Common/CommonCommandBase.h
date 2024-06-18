#pragma once

#include <cstdint>
#include <array>
#include "CommonCommandType.h"

namespace Common
{
using std::array;

static const uint8_t CommandSize = 22;

enum class CommandId : uint16_t
{
	Unknown = 0,
	SetMotorPosition,
	MaxIndexCount
};

class CommandBase
{
public:
	CommandId Command;
	union
	{
		std::array <uint8_t, CommandSize> CommandRaw;
		ServoMotorSettingsCommand MotorPosition;
	};
};
static_assert(sizeof(CommandBase) == 24, "CommandBase has invalid size.");

} // namespace Common