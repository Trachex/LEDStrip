#include "StateManager.hpp"
#include "config.hpp"

StateManager::StateManager() {
    state.mode.currMode = 0;
    state.mode.ledCount = LED_DEFAULT_COUNT;
    state.mode.delay = DEFAULT_DELAY;

    state.wifi.ssid = SSID;
    state.wifi.pass = PASS;
    state.wifi.workSsid = "";
    state.wifi.workPass = "";
    state.wifi.workIP = "";
}