#pragma once

#include "State.hpp"
#include "NVSManager/NVSManager.hpp"

class StateManager {
    public:
        State state;
        StateManager();
        void storeState();
    private:
        NVSManager& nvsManager;
};

