#include "WifiManager.hpp"
#include "DependencyManager/DependencyManager.hpp"
#include "utils/log.hpp"

Logger* wifiLogger = new Logger("WifiManager");

WifiManager::WifiManager() : stateManager(dependencyManager.getStateManager()) {
    WiFi.disconnect();
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(stateManager.getSSID().c_str(), stateManager.getPass().c_str());

    connect(stateManager.getWorkSSID().c_str(), stateManager.getWorkPass().c_str());
}

std::string WifiManager::connect(const char* ssid, const char* password) {
    if (strlen(ssid) == 0 || strlen(password) == 0 ) return "Error";
    WiFi.disconnect();
    wifiLogger->logln("Connecting");

    WiFi.begin(ssid, password);

    int timeout = 3;

    while (WiFi.status() != WL_CONNECTED && timeout > 0) {
        wifiLogger->logln(".");
        delay(1000);
        timeout--;
    }

    if (WiFi.status() == WL_CONNECTED) {
        wifiLogger->logln("Connected!");
        string ip = WiFi.localIP().toString();
        stateManager.setWorkIp(ip);

        wifiLogger->logln(ip);

        return ip;
    }

    wifiLogger->logln("Connection Failed");

    return "Error";
}

std::string WifiManager::getMac() {
    wifiLogger->logln(WiFi.macAddress());
    return std::string(WiFi.macAddress().c_str());
}