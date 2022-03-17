#include "StateManager.hpp"
#include "config.hpp"
#include "DependencyManager/DependencyManager.hpp"

StateManager::StateManager() : nvsManager(dependencyManager.getNVSManager()) {
    state = nvsManager.readState();

    if (state.mode.ledCount == 0) state.mode.ledCount = LED_DEFAULT_COUNT;
    if (state.mode.delay == 0) state.mode.delay = DEFAULT_DELAY;
    if (state.mode.brightness == 0) state.mode.brightness = DEFAULT_BRIGHTNESS;
    
    if (state.wifi.ssid == "") state.wifi.ssid = DEFAULT_SSID;
    if (state.wifi.pass == "") state.wifi.pass = DEFAULT_PASS;

    storeState();
}

void StateManager::storeState() {
    nvsManager.writeState(state);
}

void StateManager::setAmount(int amount) {
    state.mode.ledCount = amount;
    storeState();
}

void StateManager::setDelay(int delay) {
    state.mode.delay = delay;
    storeState();
}

void StateManager::setBrightness(int brightness) {
    state.mode.brightness = brightness;
    storeState();
}

void StateManager::setMode(int mode) {
    state.mode.currMode = mode;
    storeState();
}

void StateManager::setModeAmount(int amount) {
    state.mode.modeAmount = amount;
    storeState();
}

void StateManager::setWorkStation(string workSsid, string workPass) {
    state.wifi.workSsid = workSsid;
    state.wifi.workPass = workPass;
    storeState();
}

void StateManager::setWorkIp(string ip) {
    state.wifi.workIP = ip;
    storeState();
}

int StateManager::getModeAmount() {
    return state.mode.modeAmount;
}

int StateManager::getLedCount() {
    return state.mode.ledCount;
}

int StateManager::getMode() {
    return state.mode.currMode;
}

int StateManager::getDelay() {
    return state.mode.delay;
}

int StateManager::getBrightness() {
    return state.mode.brightness;
}

string StateManager::getSSID() {
    return state.wifi.ssid;
}

string StateManager::getPass() {
    return state.wifi.pass;
}

string StateManager::getWorkSSID() {
    return state.wifi.workSsid;
}

string StateManager::getWorkPass() {
    return state.wifi.workPass;
}

ModeState StateManager::getModeState() {
    return state.mode;
}