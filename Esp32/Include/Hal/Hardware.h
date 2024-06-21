#ifndef INCLUDE_HAL_HARDWARE_H_
#define INCLUDE_HAL_HARDWARE_H_

#include "Wifidriver.h"
#include "Dwt.h"
#include "esp_chip_info.h"
#include "RTOSExtra.h"
#include "Hardware.h"
#include "freertos/FreeRTOS.h"
#include "RTOSExtra.h"
#include "freertos/task.h"
#include "thread.hpp"
#include "esp_err.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_wifi.h"
#include "WifiDriver.h"
#include "lwip/ip_addr.h"

namespace Hal
{

class Hardware
{
public:
    Hardware();
    ~Hardware();
    WifiDriver &GetWifi() { return _wifiDriver; }
    uint32_t Milliseconds();
    void SoftwareReset();

static inline Hardware *Instance()
{
    if (_pHardware == nullptr)
    {
        _pHardware = new Hardware();
    }
    return _pHardware;
}

private:
    static Hardware *_pHardware;
    WifiDriver _wifiDriver = {};
    esp_chip_info_t _mcuInfo = {};
	MacAddress _macAdrress = {};
    uint32_t _clockSpeed = 0;
};
} // namespace Hal

#endif /* INCLUDE_HAL_HARDWARE_H_ */
