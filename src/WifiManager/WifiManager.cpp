#include "WifiManager.hpp"
#include "DependencyManager/DependencyManager.hpp"
#include "utils/log.hpp"

Logger* logger = new Logger("WifiManager");

WifiManager::WifiManager() : stateManager(dependencyManager.getStateManager()) {
    WiFi.disconnect();
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(stateManager.state.wifi.ssid.c_str(), stateManager.state.wifi.pass.c_str());

    connect(stateManager.state.wifi.workSsid.c_str(), stateManager.state.wifi.workPass.c_str());
}

std::string WifiManager::connect(const char* ssid, const char* password) {
    if (strlen(ssid) == 0 || strlen(password) == 0 ) return "Error";

    logger->logln("Connecting");

    WiFi.begin(ssid, password);

    int timeout = 3;

    while (WiFi.status() != WL_CONNECTED && timeout > 0) {
        logger->logln(".");
        delay(100);
        timeout--;
    }

    if (WiFi.status() == WL_CONNECTED) {
        logger->logln("Connected!");
        string ip = WiFi.localIP().toString();
        stateManager.state.wifi.workIP = ip;

        logger->logln(ip);

        return ip;
    }

    logger->logln("Connection Failed");

    return "Error";
}

std::string WifiManager::getMac() {
    logger->logln(WiFi.macAddress());
    return std::string(WiFi.macAddress().c_str());
}