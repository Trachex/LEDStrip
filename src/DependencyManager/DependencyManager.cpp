#include "DependencyManager.hpp"

DependencyManager dependencyManager;

NVSManager& DependencyManager::getNVSManager() {
    if (nvsManager == nullptr) {
        nvsManager = new NVSManager();
    }
    return *nvsManager;
}

fs::SPIFFSFS& DependencyManager::getSPIFFS() {
    if (spiffs == nullptr) {
        SPIFFS.begin();
        spiffs = &SPIFFS;
    }
    return *spiffs;
}

WifiManager& DependencyManager::getWifiManager() {
    if (wifiManager == nullptr) {
        wifiManager = new WifiManager();
    }
    return *wifiManager;
}

StateManager& DependencyManager::getStateManager() {
    if (stateManager == nullptr) {
        stateManager = new StateManager();
    }
    return *stateManager;
}

LEDManager& DependencyManager::getLEDManager() {
    if (ledManager == nullptr) {
        ledManager = new LEDManager();
    }
    return *ledManager;
}

ServerManager& DependencyManager::getServerManager() {
    if (serverManager == nullptr) {
        serverManager = new ServerManager();
    }
    return *serverManager;
}