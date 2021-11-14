#pragma once

#include <SPIFFS.h>
#include "LEDManager/LEDManager.hpp"
#include "StateManager/StateManager.hpp"
#include "WifiManager/WifiManager.hpp"

class DependencyManager {
    public:
        fs::SPIFFSFS& getSPIFFS();
        LEDManager& getLEDManager();
        StateManager& getStateManager();
        WifiManager& getWifiManager();
    
    private:
        fs::SPIFFSFS* spiffs = nullptr;
        LEDManager* ledManager = nullptr;
        StateManager* stateManager = nullptr;
        WifiManager* wifiManager = nullptr;
};

extern DependencyManager dependencyManager;