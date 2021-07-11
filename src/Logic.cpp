#include "Logic.hpp"
#include "Pinout.hpp"

#include <bitset>
#include <eventpp/callbacklist.h>
#include <eventpp/utilities/conditionalfunctor.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include <functional>
#include <thread>

Logic::Logic() {
}

Logic& IRAM_ATTR Logic::singleton() {
    static Logic DRAM_ATTR instance;
    return instance;
}

void Logic::init() {
    gpio_config_t configData = {
        .pin_bit_mask = 1ULL << Pins::LedPower,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&configData);
    m_buttons.init();
}

void Logic::turnOnLeds() {
    gpio_set_level(Pins::LedPower, 1);
}

void Logic::turnOffLeds() {
    gpio_set_level(Pins::LedPower, 0);
}

StatusBar& Logic::statusBar() {
    return m_statusBar;
}

Display& Logic::display() {
    return m_display;
}

Buttons& Logic::buttons() {
    return m_buttons;
}

Logic& logic = Logic::singleton();
Display& display = logic.display();
StatusBar& statusBar = logic.statusBar();
Buttons& buttons = logic.buttons();

extern void logicMain();

extern "C" {
[[gnu::weak]] void app_main() {
    logic.init();
    logic.turnOnLeds();

    std::thread logicMainThread(logicMain);

    logicMainThread.join();

    while (true)
        vTaskDelay(1000 / portTICK_PERIOD_MS);
}
}