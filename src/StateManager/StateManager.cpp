#include "StateManager.hpp"
#include "config.hpp"

StateManager::StateManager() : nvsManager(dependencyManager.getNVSManager()) {
    state = nvsManager.readState();

    if (state.mode.ledCount == 0) state.mode.ledCount = LED_DEFAULT_COUNT;
    if (state.mode.delay == 0) state.mode.delay = DEFAULT_DELAY;
    
    if (state.wifi.ssid == "") state.wifi.ssid = DEFAULT_SSID;
    if (state.wifi.pass == "") state.wifi.pass = DEFAULT_PASS;

    storeState();
}

void StateManager::storeState() {
    nvsManager.writeState(state);
}