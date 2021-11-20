#pragma once

#include <ArduinoNvs.h>
#include "StateManager/State.hpp"

class NVSManager {
    public:
        NVSManager();
        State readState();
        void writeState(State state);
    private:
        State currentState;
};