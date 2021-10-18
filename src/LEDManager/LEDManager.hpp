#pragma once

#include <FastLED.h>
#include "StateManager/StateManager.hpp"

class LEDManager {
    public:
        LEDManager();
        void tick();
    private:
        CRGB* leds;
        StateManager& stateManager;
};

