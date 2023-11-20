#pragma once

#include <array>
#include <driver/gpio.h>

namespace Platform {

static constexpr bool LedPowerOnLevel = 1;

namespace Pins {

static constexpr gpio_num_t Display = GPIO_NUM_13;
static constexpr gpio_num_t Status = GPIO_NUM_12;

} // namespace Pins

} // namespace Platform
