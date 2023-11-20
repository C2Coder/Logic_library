#pragma once

#include "ArduinoLikeUtils.hpp"
#include "Display.hpp"
#include "Nvs.hpp"
#include "Platform.hpp"
#include "StatusBar.hpp"
#include <bitset>
#include <eventpp/callbacklist.h>
#include <functional>

class Logic {
    friend class Buttons;
    friend void trampoline(void*);

private:
    const char* m_tag = "Logic";

    Display m_display;
    StatusBar m_statusBar;

    Logic();

public:
    Logic(Logic&) = delete;
    Logic(Logic&&) = delete;
    Logic& operator=(Logic&) = delete;
    Logic& operator=(Logic&&) = delete;

    static Logic& IRAM_ATTR singleton();

    void init();

    ~Logic() = default;

    Display& display();
    StatusBar& statusBar();
    Nvs& nvs();
};

void logicMain();

extern Logic& logic;
extern Display& display;
extern StatusBar& statusBar;
