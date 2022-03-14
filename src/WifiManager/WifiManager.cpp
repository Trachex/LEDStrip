#include "WifiManager.hpp"
#include "DependencyManager/DependencyManager.hpp"

WifiManager::WifiManager() : stateManager(dependencyManager.getStateManager()) {
    WiFi.disconnect();
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(stateManager.state.wifi.ssid.c_str(), stateManager.state.wifi.pass.c_str());

    connect(stateManager.state.wifi.workSsid.c_str(), stateManager.state.wifi.workPass.c_str());
}

std::string WifiManager::connect(const char* ssid, const char* password) {
    if (strlen(ssid) == 0 || strlen(password) == 0 ) return "Error";

    Serial.println("Connecting");

    WiFi.begin(ssid, password);

    int retries = 3;

    while (WiFi.status() != WL_CONNECTED && retries > 0) {
        delay(100);
        retries--;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Connected!");
        string ip = WiFi.localIP().toString();
        stateManager.state.wifi.workIP = ip;

        Serial.println(ip.c_str());

        return ip;
    }

    Serial.println("Connection Failed");

    return "Error";
}

std::string WifiManager::getMac() {
    Serial.println(WiFi.macAddress());
    return std::string(WiFi.macAddress().c_str());
}