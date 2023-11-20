#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_random.h>
#include <stdint.h>
#include <string>

/**
 * @brief Wait for specified amount of milliseconds
 *
 * @param ms number of milliseconds to wait
 */
inline void delay(uint32_t ms) {
    vTaskDelay(pdMS_TO_TICKS(ms));
}

/**
 * @brief Wait for specified amount of seconds
 *
 * @param seconds number of seconds to wait
 */
inline void waitSeconds(float seconds) {
    delay(uint32_t(seconds * 1000.f));
}

/**
 * @brief Returns time since boot in milliseconds
 *
 * @return uint32_t number of milliseconds since boot
 */
inline uint32_t millis() {
    return pdTICKS_TO_MS(xTaskGetTickCount());
}

/**
 * @brief Returns time since boot in seconds
 *
 * @return float number of seconds since boot
 */
inline float seconds() {
    return float(millis()) / 1000.f;
}

/**
 * @brief Get random number from 0 to max
 *
 * @param max Uper limit of random number
 * @return long Random number
 */
inline long random(long max) {
    uint32_t x = esp_random();
    uint64_t m = uint64_t(x) * uint64_t(max);
    uint32_t l = uint32_t(m);
    if (l < max) {
        uint32_t t = -max;
        if (t >= max) {
            t -= max;
            if (t >= max)
                t %= max;
        }
        while (l < t) {
            x = esp_random();
            m = uint64_t(x) * uint64_t(max);
            l = uint32_t(m);
        }
    }
    return m >> 32;
}

/**
 * @brief Get random number from min to max
 *
 * @param min Lower limit of random number
 * @param max Uper limit of random number
 * @return long Random number
 */
inline long random(long min, long max) {
    if (min >= max) {
        return min;
    }
    long diff = max - min;
    return random(diff) + min;
}

/**
 * @brief Saves an integer into the persisent NVS storage.
 *
 * @param name name of the value
 * @param value
 */
void saveInt(const std::string& name, int value);

/**
 * @brief Loads an integer from the persistent NVS storage.
 *
 * @param name name of the value
 * @param defaultVal default value returned when the name does not exist
 * @return int
 */
int loadInt(const std::string& name, int defaultVal = 0);
