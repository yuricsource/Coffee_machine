
#ifndef HAL_HAL_COMMON_H_
#define HAL_HAL_COMMON_H_

#include <array>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif


namespace Hal
{

using std::array;
static constexpr uint8_t WifiSsidMaxLength = 32;
using WifiSsid = array<char, WifiSsidMaxLength>;
static_assert(sizeof(WifiSsid) == 32, "Array has invalid size.");

static constexpr uint8_t WifiPasswordMaxLength = 64;
using WifiPassword = array<char, WifiPasswordMaxLength>;
static_assert(sizeof(WifiPassword) == 64, "Array has invalid size.");

static constexpr uint8_t MacAddressMaxLength = 6;
using MacAddress = array<uint8_t, MacAddressMaxLength>;
static_assert(sizeof(MacAddress) == 6, "Array has invalid size.");

}

#ifdef __cplusplus
}
#endif

#endif // HAL_HAL_COMMON_H_