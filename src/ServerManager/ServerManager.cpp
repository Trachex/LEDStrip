#include "ServerManager.hpp"
#include "DependencyManager/DependencyManager.hpp"
#include "utils/log.hpp"

#define CONTENT_TYPE_JSON "application/json"
Logger* serverLogger = new Logger("ServerManager");

ServerManager::ServerManager() : 
    spiffs(dependencyManager.getSPIFFS()),
    stateManager(dependencyManager.getStateManager()),
    webServer(80),
    wifiManager(dependencyManager.getWifiManager()) {

    webServer.on("/*", HTTP_OPTIONS, [this](AsyncWebServerRequest* request) {
        AsyncWebServerResponse *response = request->beginResponse(204);
        request->send(response);
    });

    webServer.on("/static/*", HTTP_GET, [this](AsyncWebServerRequest* request) {
        serverLogger->logln(request->url());
        request->send(spiffs, request->url());
    });

    webServer.on("/", HTTP_GET, [this](AsyncWebServerRequest* request) {
        serverLogger->logln("index.html route");
        request->send(spiffs, "/static/index.html");
    });

    webServer.on("/index.css", HTTP_GET, [this](AsyncWebServerRequest* request) {
        serverLogger->logln("index.css route");
        request->send(spiffs, "/static/index.css");
    });

    webServer.on("/index.js", HTTP_GET, [this](AsyncWebServerRequest* request) {
        serverLogger->logln("index.js route");
        request->send(spiffs, "/static/index.js");
    });

    webServer.on("/led/state", HTTP_GET, [this](AsyncWebServerRequest* request) {
        StaticJsonDocument<256> json;
        ModeState state = stateManager.getModeState();

        json["mode"] = state.currMode;
        json["brightness"] = state.brightness;
        json["delay"] = state.delay;
        json["ledCount"] = state.ledCount;

        string jsonString;

        serializeJson(json, (std::string&) jsonString);

        request->send(200, "application/json", jsonString.c_str());
    });

    AsyncCallbackJsonWebHandler* ledAmount = new AsyncCallbackJsonWebHandler("/led/amount", [this](AsyncWebServerRequest *request, JsonVariant &json) {
        int amount = json["amount"];

        serverLogger->logln(amount);

        stateManager.setAmount(amount);

        AsyncResponseStream *response = request->beginResponseStream("application/json");
        DynamicJsonDocument resp(1024);
        resp["status"] = "ok";
        serializeJson(resp, *response);
        request->send(response);
    });

    AsyncCallbackJsonWebHandler* ledDelay = new AsyncCallbackJsonWebHandler("/led/delay", [this](AsyncWebServerRequest *request, JsonVariant &json) {
        int delay = json["delay"];

        serverLogger->logln(delay);

        if(delay < 1 || delay > 60) {
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            DynamicJsonDocument resp(1024);
            resp["status"] = "error";
            resp["description"] = "Invaid delay, must be within range 1 to 60";
            serializeJson(resp, *response);
            request->send(response);
            return;
        }

        stateManager.setDelay(delay);

        AsyncResponseStream *response = request->beginResponseStream("application/json");
        DynamicJsonDocument resp(1024);
        resp["status"] = "ok";
        serializeJson(resp, *response);
        request->send(response);
    });

    AsyncCallbackJsonWebHandler* ledBrightness = new AsyncCallbackJsonWebHandler("/led/brightness", [this](AsyncWebServerRequest *request, JsonVariant &json) {
        int brightness = json["brightness"];

        serverLogger->logln(brightness);

        if(brightness < 1 || brightness > 255) {
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            DynamicJsonDocument resp(1024);
            resp["status"] = "error";
            resp["description"] = "Invaid brightness, must be within range 1 to 255";
            serializeJson(resp, *response);
            request->send(response);
            return;
        }

        stateManager.setBrightness(brightness);

        AsyncResponseStream *response = request->beginResponseStream("application/json");
        DynamicJsonDocument resp(1024);
        resp["status"] = "ok";
        serializeJson(resp, *response);
        request->send(response);
    });

    AsyncCallbackJsonWebHandler* ledMode = new AsyncCallbackJsonWebHandler("/led/mode", [this](AsyncWebServerRequest *request, JsonVariant &json) {
        int mode = json["mode"];

        serverLogger->logln(mode);

        int modeAmount = stateManager.getModeAmount();

        if(mode < 0 || mode > modeAmount -1) {
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            DynamicJsonDocument resp(1024);
            resp["status"] = "error";
            resp["description"] = "Invaid brightness, must be within range 0 to " + modeAmount -1;
            serializeJson(resp, *response);
            request->send(response);
            return;
        }

        stateManager.setMode(mode);

        AsyncResponseStream *response = request->beginResponseStream("application/json");
        DynamicJsonDocument resp(1024);
        resp["status"] = "ok";
        serializeJson(resp, *response);
        request->send(response);
    });

    AsyncCallbackJsonWebHandler* wifiConnect = new AsyncCallbackJsonWebHandler("/wifi/connect", [this](AsyncWebServerRequest *request, JsonVariant &json) {
        std::string workSsid = json["workSsid"];
        std::string workPass = json["workPass"];

        serverLogger->logln(workSsid);
        serverLogger->logln(workPass);

        stateManager.setWorkStation(workSsid, workPass);

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
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "*");
    webServer.begin();
    serverLogger->logln("Server started");
}