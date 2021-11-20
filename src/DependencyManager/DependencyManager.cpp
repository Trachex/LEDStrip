#include "DependencyManager.hpp"

DependencyManager dependencyManager;

fs::SPIFFSFS& DependencyManager::getSPIFFS() {
    if (spiffs == nullptr) {
        SPIFFS.begin();
        spiffs = &SPIFFS;
    }
    return *spiffs;
}

NVSManager& DependencyManager::getNVSManager() {
    if (nvsManager == nullptr) {
        nvsManager = new NVSManager();
    }
    return *nvsManager;
}

LEDManager& DependencyManager::getLEDManager() {
    if (ledManager == nullptr) {
        ledManager = new LEDManager();
    }
    return *ledManager;
}

StateManager& DependencyManager::getStateManager() {
    if (stateManager == nullptr) {
        stateManager = new StateManager();
    }
    return *stateManager;
}

WifiManager& DependencyManager::getWifiManager() {
    if (wifiManager == nullptr) {
        wifiManager = new WifiManager();
    }
    return *wifiManager;
}