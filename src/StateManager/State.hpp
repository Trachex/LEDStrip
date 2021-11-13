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
    int delay;
    int ledCount;
};

struct State {
    ModeState mode;
    WifiState wifi;
};