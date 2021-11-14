#pragma once

#include "LEDManager/LEDManager.hpp"
#include "StateManager/StateManager.hpp"
#include "WifiManager/WifiManager.hpp"

class DependencyManager {
    public:
        LEDManager& getLEDManager();
        StateManager& getStateManager();
        WifiManager& getWifiManager();
    
    private:
        LEDManager* ledManager = nullptr;
        StateManager* stateManager = nullptr;
        WifiManager* wifiManager = nullptr;
};

extern DependencyManager dependencyManager;