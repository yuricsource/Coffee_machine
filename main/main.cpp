#include <stdio.h>
#include "esp_system.h"
#include "esp_sleep.h"
#include "freertos/FreeRTOS.h"
#include <stdio.h>
#include "esp_err.h"
#include "Logger.h"
#include "Hardware.h"
#include "DebugAssert.h"
#include "ApplicationAgent.h"

using namespace Hal;
using namespace Utilities;
using namespace Applications;

// #define EXAMPLE_ESP_WIFI_SSID      "Yuri_R_Up"
// #define EXAMPLE_ESP_WIFI_PASS      "Australia4us"

extern "C" void app_main(void)
{
    Hardware *hardware = Hardware::Instance();
    ApplicationAgent::Instance();

    for(;;)
    {
        Logger::LogInfo("Crashing in 5 sec");
        Dwt::DelayMilliseconds(5000);
        vTaskDelay(1);
        DebugAssertFail("This is an example of DebugAssertFail");
    }
}
