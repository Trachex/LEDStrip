#include "LEDManager.hpp"
#include "DependencyManager/DependencyManager.hpp"
#include "modes.hpp"
#include "config.hpp"

LEDManager::LEDManager() : stateManager(dependencyManager.getStateManager()) {
    leds = new CRGB[stateManager.state.mode.ledCount];
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_MODE>(leds, stateManager.state.mode.ledCount);
}

void LEDManager::tick() {
    modes[stateManager.state.mode.currMode](leds, stateManager.state.mode.ledCount);
    FastLED.show();
    delay(stateManager.state.mode.delay);
}