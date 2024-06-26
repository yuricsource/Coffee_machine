
#ifndef INCLUDE_HAL_SERVO_MOTOR_H_
#define INCLUDE_HAL_SERVO_MOTOR_H_

#include "HalCommon.h"
#include "driver/ledc.h"

namespace Hal
{

class ServoMotor
{
public:

	ServoMotor(gpio_num_t pin, ledc_channel_t channel);
	~ServoMotor();
	void Init();
	void Refresh();
	void SetPositon(uint8_t percentage);

private:
	static const uint16_t MaxResolution = 8192;
	static const uint16_t Time1ms = 8192 / 20;
	static const uint16_t Time19ms = Time1ms * 19;
	gpio_num_t _pin;
	ledc_channel_config_t ledc_channel = {};
	ledc_timer_config_t ledc_timer = {};
	ledc_channel_t _channel;
};
} // namespace Hal

#endif /* INCLUDE_HAL_LEDS_H_ */
