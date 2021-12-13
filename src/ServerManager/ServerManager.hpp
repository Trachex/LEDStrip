#pragma once

#include <ArduinoJson.h>
#include <AsyncJson.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include "StateManager/StateManager.hpp"
#include "WifiManager/WifiManager.hpp"
#include "config.hpp"

class ServerManager {
    public:
        ServerManager();
        void run();
    private:
        fs::SPIFFSFS& spiffs;
        StateManager& stateManager;
        AsyncWebServer webServer;
        WifiManager& wifiManager;
};