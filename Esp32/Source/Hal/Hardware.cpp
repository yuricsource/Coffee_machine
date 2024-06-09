#include "Hardware.h"
#include "stdio.h"
#include "esp_idf_version.h"

namespace Hal
{

Hardware *Hardware::_pHardware;

Hardware::Hardware()
{
    printf("SDK Version         		: %s\n", (char *)esp_get_idf_version());

    if (_pHardware == nullptr)
		_pHardware = this;
	else
		printf("!!! Error: Only one instance of System can be created !!!\n");
}

Hardware::~Hardware()
{
}


} // namespace Hal