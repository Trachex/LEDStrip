#pragma once

#include <FastLED.h>

class LEDManager {
    public:
        LEDManager();
        void tick();
    private:
        CRGB* leds;
};

