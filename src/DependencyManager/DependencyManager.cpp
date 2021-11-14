#include "DependencyManager.hpp"

DependencyManager dependencyManager;

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