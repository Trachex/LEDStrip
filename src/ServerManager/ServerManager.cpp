#include "ServerManager.hpp"

ServerManager::ServerManager() : 
    stateManager(dependencyManager.getStateManager()),
    wifiManager(dependencyManager.getWifiManager()),
    spiffs(dependencyManager.getSPIFFS()),
    webServer(80) {

    webServer.on("/static/*", HTTP_GET, [this](AsyncWebServerRequest* request) {
        request->send(spiffs, request->url());
    });
}

void ServerManager::run() {
    webServer.begin();
}