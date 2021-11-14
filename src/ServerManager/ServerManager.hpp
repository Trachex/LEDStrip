#pragma once

#include <ESPAsyncWebServer.h>
#include "StateManager/StateManager.hpp"
#include "DependencyManager/DependencyManager.hpp"
#include "WifiManager/WifiManager.hpp"
#include "config.hpp"

class ServerManager {
    public:
        ServerManager();
        void run();
    private:
        StateManager& stateManager;
        AsyncWebServer webServer;
        WifiManager& wifiManager;
};