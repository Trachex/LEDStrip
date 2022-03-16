#include "ServerManager.hpp"
#include "DependencyManager/DependencyManager.hpp"
#include "utils/log.hpp"

Logger* logger = new Logger("ServerManager");

ServerManager::ServerManager() : 
    spiffs(dependencyManager.getSPIFFS()),
    stateManager(dependencyManager.getStateManager()),
    webServer(80),
    wifiManager(dependencyManager.getWifiManager()) {

    webServer.on("/static/*", HTTP_GET, [this](AsyncWebServerRequest* request) {
        Serial.println(request->url());

        request->send(spiffs, request->url());
    });

    AsyncCallbackJsonWebHandler* ledAmount = new AsyncCallbackJsonWebHandler("/led/amount", [this](AsyncWebServerRequest *request, JsonVariant &json) {

        int amount = json["amount"];

        logger->logln(amount);

        stateManager.state.mode.ledCount = amount;

        stateManager.storeState();

        AsyncResponseStream *response = request->beginResponseStream("application/json");
        DynamicJsonDocument resp(1024);
        resp["status"] = "ok";
        serializeJson(resp, *response);
        request->send(response);
    });

    AsyncCallbackJsonWebHandler* ledDelay = new AsyncCallbackJsonWebHandler("/led/delay", [this](AsyncWebServerRequest *request, JsonVariant &json) {

        int delay = json["delay"];

        logger->logln(delay);

        if(delay < 1 || delay > 60) {
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            DynamicJsonDocument resp(1024);
            resp["status"] = "error";
            resp["description"] = "Invaid delay, must be within range 1 to 60";
            serializeJson(resp, *response);
            request->send(response);
            return;
        }

        stateManager.state.mode.delay = delay;

        stateManager.storeState();

        AsyncResponseStream *response = request->beginResponseStream("application/json");
        DynamicJsonDocument resp(1024);
        resp["status"] = "ok";
        serializeJson(resp, *response);
        request->send(response);
    });

    AsyncCallbackJsonWebHandler* ledBrightness = new AsyncCallbackJsonWebHandler("/led/brightness", [this](AsyncWebServerRequest *request, JsonVariant &json) {

        int brightness = json["brightness"];

        logger->logln(brightness);

        if(brightness < 1 || brightness > 100) {
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            DynamicJsonDocument resp(1024);
            resp["status"] = "error";
            resp["description"] = "Invaid brightness, must be within range 1 to 100";
            serializeJson(resp, *response);
            request->send(response);
            return;
        }

        stateManager.state.mode.brightness = brightness;

        stateManager.storeState();

        AsyncResponseStream *response = request->beginResponseStream("application/json");
        DynamicJsonDocument resp(1024);
        resp["status"] = "ok";
        serializeJson(resp, *response);
        request->send(response);
    });

    AsyncCallbackJsonWebHandler* ledMode = new AsyncCallbackJsonWebHandler("/led/mode", [this](AsyncWebServerRequest *request, JsonVariant &json) {

        int mode = json["mode"];

        logger->logln(mode);

        if(mode < 0 || mode > stateManager.state.mode.modeAmount -1) {
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            DynamicJsonDocument resp(1024);
            resp["status"] = "error";
            resp["description"] = "Invaid brightness, must be within range 0 to " + stateManager.state.mode.modeAmount -1;
            serializeJson(resp, *response);
            request->send(response);
            return;
        }

        stateManager.state.mode.currMode = mode;

        stateManager.storeState();

        AsyncResponseStream *response = request->beginResponseStream("application/json");
        DynamicJsonDocument resp(1024);
        resp["status"] = "ok";
        serializeJson(resp, *response);
        request->send(response);
    });

    AsyncCallbackJsonWebHandler* wifiConnect = new AsyncCallbackJsonWebHandler("/wifi/connect", [this](AsyncWebServerRequest *request, JsonVariant &json) {

        std::string workSsid = json["workSsid"];
        std::string workPass = json["workPass"];

        logger->logln(workSsid);
        logger->logln(workPass);

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

    webServer.addHandler(ledAmount);
    webServer.addHandler(wifiConnect);
    webServer.addHandler(ledDelay);
    webServer.addHandler(ledBrightness);
    webServer.addHandler(ledMode);
}

void ServerManager::run() {
    webServer.begin();
    logger->logln("Server started");
}