#pragma once

#include <WiFi.h>
#include "string"
#include "StateManager/StateManager.hpp"

class WifiManager {
    public:
        WifiManager();
        std::string getMac();
        std::string connect(const char* ssid, const char* password);
    private:
        StateManager& stateManager;
};