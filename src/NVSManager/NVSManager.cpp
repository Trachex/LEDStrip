#include "NVSManager.hpp"

// keys
#define CURR_MODE "currMode"
#define DELAY "delay"
#define LED_COUNT "ledCount"
#define BRIGHTNESS "brightness"

#define SSID "ssid"
#define PASS "pass"
#define WORK_SSID "workSsid"
#define WORK_PASS "workPass"
#define WORK_IP "workIP"


State NVSManager::readState() {
    State state;
    
    state.mode.currMode = NVS.getInt(CURR_MODE);
    state.mode.delay = NVS.getInt(DELAY);
    state.mode.ledCount = NVS.getInt(LED_COUNT);
    state.mode.brightness = NVS.getInt(BRIGHTNESS);

    state.wifi.ssid = NVS.getString(SSID);
    state.wifi.pass = NVS.getString(PASS);
    state.wifi.workSsid = NVS.getString(WORK_SSID);
    state.wifi.workPass = NVS.getString(WORK_PASS);
    state.wifi.workIP = NVS.getString(WORK_IP);

    currentState = state;

    return state;
}

void NVSManager::writeState(State state) {
    if (currentState.mode.currMode != state.mode.currMode) NVS.setInt(CURR_MODE, state.mode.currMode);
    if (currentState.mode.delay != state.mode.delay) NVS.setInt(DELAY, state.mode.delay);
    if (currentState.mode.ledCount != state.mode.ledCount) NVS.setInt(LED_COUNT, state.mode.ledCount);
    if (currentState.mode.brightness != state.mode.brightness) NVS.setInt(BRIGHTNESS, state.mode.brightness);

    if (currentState.wifi.ssid != state.wifi.ssid) NVS.setString(SSID, String(state.wifi.ssid.toArduinoString()));
    if (currentState.wifi.pass != state.wifi.pass) NVS.setString(PASS, String(state.wifi.pass.toArduinoString()));
    if (currentState.wifi.workSsid != state.wifi.workSsid) NVS.setString(WORK_SSID, String(state.wifi.workSsid.toArduinoString()));
    if (currentState.wifi.workPass != state.wifi.workPass) NVS.setString(WORK_PASS, String(state.wifi.workPass.toArduinoString()));
    if (currentState.wifi.workIP != state.wifi.workIP) NVS.setString(WORK_IP, String(state.wifi.workIP.toArduinoString()));

    currentState = state;
}

NVSManager::NVSManager() {
    NVS.begin();
    readState();
}