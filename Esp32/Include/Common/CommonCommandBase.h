#pragma once

#include <cstdint>
#include <array>
#include "CommonCommandType.h"

namespace Common
{
using std::array;

static const uint8_t CommandSize = 22;

enum class CommandIdIndex : uint16_t
{
	Unknown = 0,
	// Configuration Index: 1 - 1000
	FirstConfig = 1,
	LastConfig = 1000,

	// Command Index: 1001 - 2000
	FirstCommand = 1001,
	LastCommand = 2000,

	// Response Index: 2001
	FirstCommandResponse = 2001,
	LastCommandResponse = 3000,
};

class CommandBase
{
	public:

	CommandIdIndex CommandId;
	union
	{
		std::array <uint8_t, CommandSize> CommandRaw;
		ServoMotorSettingsCommand MotorPosition;
	};
};
static_assert(sizeof(CommandBase) == 24, "CommandBase has invalid size.");

} // namespace Common