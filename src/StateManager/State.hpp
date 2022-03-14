#pragma once

#include "utils/string.hpp"

struct WifiState {
    string ssid, pass, workSsid, workPass, workIP;
};

struct ModeState {
    int currMode;
    int modeAmount;
    int delay;
    int ledCount;
    int brightness;
};

struct State {
    ModeState mode;
    WifiState wifi;
};