#pragma once

#include "string"

struct WifiState {
    std::string ssid;
    std::string pass;
    std::string workSsid;
    std::string workPass;
    std::string workIP;
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