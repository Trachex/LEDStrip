#pragma once

#include "NVSManager/NVSManager.hpp"
#include <SPIFFS.h>
#include "StateManager/StateManager.hpp"
#include "LEDManager/LEDManager.hpp"
#include "WifiManager/WifiManager.hpp"
#include "ServerManager/ServerManager.hpp"

class DependencyManager {
    public:
        NVSManager& getNVSManager();
        fs::SPIFFSFS& getSPIFFS();
        WifiManager& getWifiManager();
        StateManager& getStateManager();
        LEDManager& getLEDManager();
        ServerManager& getServerManager();
    private:
        NVSManager* nvsManager = nullptr;
        fs::SPIFFSFS* spiffs = nullptr;
        WifiManager* wifiManager = nullptr;
        StateManager* stateManager = nullptr;
        LEDManager* ledManager = nullptr;
        ServerManager* serverManager = nullptr;
};

extern DependencyManager dependencyManager;