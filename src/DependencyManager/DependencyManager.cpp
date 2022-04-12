#include "DependencyManager.hpp"
#include "utils/log.hpp"

Logger* dependencyLogger = new Logger("DependencyManager");

DependencyManager dependencyManager;

NVSManager& DependencyManager::getNVSManager() {
    if (nvsManager == nullptr) {
        nvsManager = new NVSManager();
    }
    dependencyLogger->logln("Init NVSManager");
    return *nvsManager;
}

fs::SPIFFSFS& DependencyManager::getSPIFFS() {
    if (spiffs == nullptr) {
        SPIFFS.begin();
        spiffs = &SPIFFS;
    }
    dependencyLogger->logln("Init SPIFFS");
    return *spiffs;
}

WifiManager& DependencyManager::getWifiManager() {
    if (wifiManager == nullptr) {
        wifiManager = new WifiManager();
    }
    dependencyLogger->logln("Init WifiManager");
    return *wifiManager;
}

StateManager& DependencyManager::getStateManager() {
    if (stateManager == nullptr) {
        stateManager = new StateManager();
    }
    dependencyLogger->logln("Init StateManager");
    return *stateManager;
}

LEDManager& DependencyManager::getLEDManager() {
    if (ledManager == nullptr) {
        ledManager = new LEDManager();
    }
    dependencyLogger->logln("Init LEDManager");
    return *ledManager;
}

ServerManager& DependencyManager::getServerManager() {
    if (serverManager == nullptr) {
        serverManager = new ServerManager();
    }
    dependencyLogger->logln("Init ServerManager");
    return *serverManager;
}