#include "ServerManager.hpp"
#include "DependencyManager/DependencyManager.hpp"

ServerManager::ServerManager() : 
    spiffs(dependencyManager.getSPIFFS()),
    stateManager(dependencyManager.getStateManager()),
    webServer(80),
    wifiManager(dependencyManager.getWifiManager()) {

    webServer.on("/static/*", HTTP_GET, [this](AsyncWebServerRequest* request) {
        Serial.println(request->url());

        request->send(spiffs, request->url());
    });

    AsyncCallbackJsonWebHandler* wifiConnect = new AsyncCallbackJsonWebHandler("/wifi/connect", [this](AsyncWebServerRequest *request, JsonVariant &json) {

        std::string workSsid = json["workSsid"];
        std::string workPass = json["workPass"];

        Serial.println(workSsid.c_str());
        Serial.println(workPass.c_str());

        stateManager.state.wifi.workSsid = workSsid;
        stateManager.state.wifi.workPass = workPass;

        stateManager.storeState();

        std::string ip = wifiManager.connect(workSsid.c_str(), workPass.c_str());

        AsyncResponseStream *response = request->beginResponseStream("application/json");
        DynamicJsonDocument resp(1024);
        resp["ip"] = ip;
        resp["mac"] = wifiManager.getMac();
        serializeJson(resp, *response);
        request->send(response);
    });

    webServer.addHandler(wifiConnect);
}

void ServerManager::run() {
    webServer.begin();
}