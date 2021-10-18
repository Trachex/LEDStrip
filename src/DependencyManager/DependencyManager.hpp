#pragma once

#include "LEDManager/LEDManager.hpp"
#include "StateManager/StateManager.hpp"

class DependencyManager {
    public:
        LEDManager& getLEDManager();
        StateManager& getStateManager();
    
    private:
        LEDManager* ledManager = nullptr;
        StateManager* stateManager = nullptr;
};

extern DependencyManager dependencyManager;