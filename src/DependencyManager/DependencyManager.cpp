#include "DependencyManager.hpp"

DependencyManager dependencyManager;

NVSManager& DependencyManager::getNVSManager() {
    if (nvsManager == nullptr) {
        nvsManager = new NVSManager();
    }
    Serial.println("Init NVSManager");
    return *nvsManager;
}

fs::SPIFFSFS& DependencyManager::getSPIFFS() {
    if (spiffs == nullptr) {
        SPIFFS.begin();
        spiffs = &SPIFFS;
    }
    Serial.println("Init SPIFFS");
    return *spiffs;
}

WifiManager& DependencyManager::getWifiManager() {
    if (wifiManager == nullptr) {
        wifiManager = new WifiManager();
    }
    Serial.println("Init WifiManager");
    return *wifiManager;
}

StateManager& DependencyManager::getStateManager() {
    if (stateManager == nullptr) {
        stateManager = new StateManager();
    }
    Serial.println("Init StateManager");
    return *stateManager;
}

LEDManager& DependencyManager::getLEDManager() {
    if (ledManager == nullptr) {
        ledManager = new LEDManager();
    }
    Serial.println("Init LEDManager");
    return *ledManager;
}

ServerManager& DependencyManager::getServerManager() {
    if (serverManager == nullptr) {
        serverManager = new ServerManager();
    }
    Serial.println("Init ServerManager");
    return *serverManager;
}