#pragma once

#include <SPIFFS.h>
#include "LEDManager/LEDManager.hpp"
#include "StateManager/StateManager.hpp"
#include "WifiManager/WifiManager.hpp"
#include "NVSManager/NVSManager.hpp"
#include "ServerManager/ServerManager.hpp"

class DependencyManager {
    public:
        fs::SPIFFSFS& getSPIFFS();
        LEDManager& getLEDManager();
        StateManager& getStateManager();
        WifiManager& getWifiManager();
        NVSManager& getNVSManager();
        ServerManager& getServerManager();
    private:
        fs::SPIFFSFS* spiffs = nullptr;
        LEDManager* ledManager = nullptr;
        StateManager* stateManager = nullptr;
        WifiManager* wifiManager = nullptr;
        NVSManager* nvsManager = nullptr;
        ServerManager* serverManager = nullptr;
};

extern DependencyManager dependencyManager;