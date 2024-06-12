#include <stdio.h>
#include "esp_system.h"
#include "esp_sleep.h"
#include "freertos/FreeRTOS.h"
#include <stdio.h>
#include "esp_err.h"
#include "Hardware.h"

using namespace Hal;

extern "C" void app_main(void)
{
    Hardware *hardware = Hardware::Instance();
    Dwt::DelayMicrosecond(10);
	Dwt::DelayMilliseconds(10);
    for(;;)
    {
        printf("Delaying for 1 sec\n");
        Dwt::DelayMilliseconds(1000);
        vTaskDelay(1);
    }
}
