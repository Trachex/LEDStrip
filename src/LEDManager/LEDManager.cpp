#include "LEDManager.hpp"
#include "modes.hpp"
#include "config.hpp"

LEDManager::LEDManager() {
    leds = new CRGB[LED_COUNT];
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_MODE>(leds, LED_COUNT);
}

void LEDManager::tick() {
    modes[0](leds, LED_COUNT);
    FastLED.show();
    delay(INTERFRAME_DELAY);
}