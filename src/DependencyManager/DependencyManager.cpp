#include "DependencyManager.hpp"

DependencyManager dependencyManager;

LEDManager& DependencyManager::getLEDManager() {
    if (ledManager == nullptr) {
        ledManager = new LEDManager();
    }
    return *ledManager;
}