#pragma once

#include <WiFi.h>
#include "string"
#include "StateManager/StateManager.hpp"

class WifiManager {
    public:
        WifiManager();
        void connect(const char* ssid, const char* password);
    private:
        StateManager& stateManager;
};