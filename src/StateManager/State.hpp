#pragma once

#include "utils/string.hpp"

struct WifiState {
    string ssid, pass, workSsid, workPass, workIP;
};

struct ModeState {
    int currMode, modeAmount, delay, ledCount, brightness;
};

struct State {
    ModeState mode;
    WifiState wifi;
};