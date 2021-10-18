#include "LEDManager.hpp"
#include "DependencyManager/DependencyManager.hpp"
#include "modes.hpp"
#include "config.hpp"

LEDManager::LEDManager() : stateManager(dependencyManager.getStateManager()) {
    leds = new CRGB[stateManager.state.ledCount];
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_MODE>(leds, stateManager.state.ledCount);
}

void LEDManager::tick() {
    modes[stateManager.state.mode](leds, stateManager.state.ledCount);
    FastLED.show();
    delay(stateManager.state.delay);
}