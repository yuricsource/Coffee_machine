#ifndef INCLUDE_HAL_HARDWARE_H_
#define INCLUDE_HAL_HARDWARE_H_

#include "Wifidriver.h"
#include "Dwt.h"

namespace Hal
{

class Hardware
{
public:
    Hardware();
    ~Hardware();
    uint32_t Milliseconds();

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
    WifiDriver _wifiDriver;

};
} // namespace Hal

#endif /* INCLUDE_HAL_HARDWARE_H_ */
