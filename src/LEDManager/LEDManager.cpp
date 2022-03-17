#include "LEDManager.hpp"
#include "modes.hpp"
#include "config.hpp"
#include "DependencyManager/DependencyManager.hpp"

using namespace std;

LEDManager::LEDManager() : stateManager(dependencyManager.getStateManager()) {
    leds = new CRGB[stateManager.getLedCount()];
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_MODE>(leds, stateManager.getLedCount());
    stateManager.setModeAmount(modeAmount);
}

void LEDManager::tick() {
    modes[stateManager.getMode()](leds, stateManager.getModeState());
    FastLED.show();
    delay(stateManager.getDelay());
}