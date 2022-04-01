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
        void cleanupWs();
    private:
        fs::SPIFFSFS& spiffs;
        StateManager& stateManager;
        AsyncWebServer webServer;
        AsyncWebSocket ws;
        WifiManager& wifiManager;
        void wsHandler(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len);
        void wsDelay(int delay);
        void wsBrightness(int brightness);
};