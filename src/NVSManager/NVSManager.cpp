#include "NVSManager.hpp"

// keys
#define CURR_MODE "currMode"
#define DELAY "delay"
#define LED_COUNT "ledCount"

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

    state.wifi.ssid = std::string(NVS.getString(SSID).c_str());
    state.wifi.pass = std::string(NVS.getString(PASS).c_str());
    state.wifi.workSsid = std::string(NVS.getString(WORK_SSID).c_str());
    state.wifi.workPass = std::string(NVS.getString(WORK_PASS).c_str());
    state.wifi.workIP = std::string(NVS.getString(WORK_IP).c_str());

    currentState = state;

    return state;
}

void NVSManager::writeState(State state) {
    if (currentState.mode.currMode != state.mode.currMode) NVS.setInt(CURR_MODE, state.mode.currMode);
    if (currentState.mode.delay != state.mode.delay) NVS.setInt(DELAY, state.mode.delay);
    if (currentState.mode.ledCount != state.mode.ledCount) NVS.setInt(LED_COUNT, state.mode.ledCount);

    if (currentState.wifi.ssid != state.wifi.ssid) NVS.setString(SSID, String(state.wifi.ssid.c_str()));
    if (currentState.wifi.pass != state.wifi.pass) NVS.setString(PASS, String(state.wifi.pass.c_str()));
    if (currentState.wifi.workSsid != state.wifi.workSsid) NVS.setString(WORK_SSID, String(state.wifi.workSsid.c_str()));
    if (currentState.wifi.workPass != state.wifi.workPass) NVS.setString(WORK_PASS, String(state.wifi.workPass.c_str()));
    if (currentState.wifi.workIP != state.wifi.workIP) NVS.setString(WORK_IP, String(state.wifi.workIP.c_str()));

    currentState = state;
}

NVSManager::NVSManager() {
    NVS.begin();
    readState();
}