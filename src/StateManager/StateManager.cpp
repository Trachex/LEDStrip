#include "StateManager.hpp"
#include "config.hpp"

StateManager::StateManager() {
    state.mode = 0;
    state.ledCount = LED_DEFAULT_COUNT;
    state.delay = DEFAULT_DELAY;
}