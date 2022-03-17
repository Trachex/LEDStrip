#pragma once

#include "State.hpp"
#include "NVSManager/NVSManager.hpp"

class StateManager {
    public:
        StateManager();
        void setAmount(int amount);
        void setDelay(int delay);
        void setBrightness(int brightness);
        void setMode(int mode);
        void setModeAmount(int amount);
        void setWorkStation(string workSsid, string workPass);
        void setWorkIp(string ip);
        int getModeAmount();
        int getLedCount();
        int getMode();
        int getDelay();
        string getSSID();
        string getPass();
        string getWorkSSID();
        string getWorkPass();
    private:
        State state;
        void storeState();
        NVSManager& nvsManager;
};

