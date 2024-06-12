#include "Hardware.h"
#include <stdio.h>
#include "esp_idf_version.h"

namespace Hal
{

Hardware *Hardware::_pHardware;

Hardware::Hardware() :
	_wifiDriver()
{
    printf("SDK Version         		: %s\n", (char *)esp_get_idf_version());
	Dwt::DelayMicrosecond(10);
	Dwt::DelayMilliseconds(10);
    if (_pHardware == nullptr)
		_pHardware = this;
	else
		printf("!!! Error: Only one instance of System can be created !!!\n");
}

Hardware::~Hardware()
{
}


} // namespace Hal