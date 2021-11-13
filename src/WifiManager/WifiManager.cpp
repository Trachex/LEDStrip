#include "WifiManager.hpp"
#include "DependencyManager/DependencyManager.hpp"

WifiManager::WifiManager() : stateManager(dependencyManager.getStateManager()) {
    WiFi.disconnect();
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(stateManager.state.wifi.ssid.c_str(), stateManager.state.wifi.pass.c_str());

    connect(stateManager.state.wifi.workSsid.c_str(), stateManager.state.wifi.workPass.c_str());
}

void WifiManager::connect(const char* ssid, const char* password) {
    if (strlen(ssid) == 0 || strlen(password) == 0 ) return;

    WiFi.begin(ssid, password);

    int retries = 3;

    while (WiFi.status() != WL_CONNECTED && retries > 0) {
        delay(100);
        retries--;
    }

    if (WiFi.status() == WL_CONNECTED) {
        std::string ip = std::string(WiFi.localIP().toString().c_str());
        stateManager.state.wifi.workIP = ip;
    } 
}