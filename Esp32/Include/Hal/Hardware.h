#ifndef INCLUDE_HAL_HARDWARE_H_
#define INCLUDE_HAL_HARDWARE_H_

namespace Hal
{

class Hardware
{
public:
    Hardware();
    ~Hardware();

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

};
} // namespace Hal

#endif /* INCLUDE_HAL_HARDWARE_H_ */
