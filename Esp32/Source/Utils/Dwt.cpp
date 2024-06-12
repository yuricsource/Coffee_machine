
#include "Dwt.h"
#include "Hardware.h"
#include <sys/time.h>
#include "esp_timer.h"

namespace Hal
{

Dwt::Dwt()
{
}

void Dwt::DelayMicrosecond(uint32_t us)
{
	esp_rom_delay_us(us);
}

void Dwt::DelayMilliseconds(uint32_t ms)
{
	for (uint16_t i = 0; i < 1000; i++)
		Dwt::DelayMicrosecond(ms);
}

} // namespace Hal
