#include "DependencyManager.hpp"
#include "utils/log.hpp"

Logger* logger = new Logger("DependencyManager");

DependencyManager dependencyManager;

NVSManager& DependencyManager::getNVSManager() {
    if (nvsManager == nullptr) {
        nvsManager = new NVSManager();
    }
    logger->logln("Init NVSManager");
    return *nvsManager;
}

fs::SPIFFSFS& DependencyManager::getSPIFFS() {
    if (spiffs == nullptr) {
        SPIFFS.begin();
        spiffs = &SPIFFS;
    }
    logger->logln("Init SPIFFS");
    return *spiffs;
}

WifiManager& DependencyManager::getWifiManager() {
    if (wifiManager == nullptr) {
        wifiManager = new WifiManager();
    }
    logger->logln("Init WifiManager");
    return *wifiManager;
}

StateManager& DependencyManager::getStateManager() {
    if (stateManager == nullptr) {
        stateManager = new StateManager();
    }
    logger->logln("Init StateManager");
    return *stateManager;
}

LEDManager& DependencyManager::getLEDManager() {
    if (ledManager == nullptr) {
        ledManager = new LEDManager();
    }
    logger->logln("Init LEDManager");
    return *ledManager;
}

ServerManager& DependencyManager::getServerManager() {
    if (serverManager == nullptr) {
        serverManager = new ServerManager();
    }
    logger->logln("Init ServerManager");
    return *serverManager;
}