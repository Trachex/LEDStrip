#include "LEDManager.hpp"
#include "modes.hpp"
#include "config.hpp"
#include "DependencyManager/DependencyManager.hpp"

using namespace std;

LEDManager::LEDManager() : stateManager(dependencyManager.getStateManager()) {
    leds = new CRGB[stateManager.state.mode.ledCount];
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_MODE>(leds, stateManager.state.mode.ledCount);
    stateManager.state.mode.modeAmount = amount;
}

void LEDManager::tick() {
    modes[stateManager.state.mode.currMode](leds, stateManager.state.mode.ledCount);
    FastLED.show();
    delay(stateManager.state.mode.delay);
}