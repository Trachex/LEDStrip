#pragma once

#include "LEDManager/LEDManager.hpp"

class DependencyManager {
    public:
        LEDManager& getLEDManager();
    
    private:
        LEDManager* ledManager = nullptr;
};

extern DependencyManager dependencyManager;