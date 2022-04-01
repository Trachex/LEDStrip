#include "ServerManager.hpp"
#include "DependencyManager/DependencyManager.hpp"
#include "utils/log.hpp"

Logger* logger = new Logger("ServerManager");

ServerManager::ServerManager() : 
    spiffs(dependencyManager.getSPIFFS()),
    stateManager(dependencyManager.getStateManager()),
    webServer(80),
    ws("/ws"),
    wifiManager(dependencyManager.getWifiManager()) {

    webServer.on("/static/*", HTTP_GET, [this](AsyncWebServerRequest* request) {
        logger->logln(request->url());
        request->send(spiffs, request->url());
    });

    webServer.on("/", HTTP_GET, [this](AsyncWebServerRequest* request) {
        logger->logln("index.html route");
        request->send(spiffs, "/static/index.html");
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

        logger->logln(amount);

        stateManager.setAmount(amount);

        AsyncResponseStream *response = request->beginResponseStream("application/json");
        DynamicJsonDocument resp(1024);
        resp["status"] = "ok";
        serializeJson(resp, *response);
        request->send(response);
    });

    AsyncCallbackJsonWebHandler* ledMode = new AsyncCallbackJsonWebHandler("/led/mode", [this](AsyncWebServerRequest *request, JsonVariant &json) {
        int mode = json["mode"];

        logger->logln(mode);

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

        logger->logln(workSsid);
        logger->logln(workPass);

        stateManager.setWorkStation(workSsid, workPass);

        std::string ip = wifiManager.connect(workSsid.c_str(), workPass.c_str());

        AsyncResponseStream *response = request->beginResponseStream("application/json");
        DynamicJsonDocument resp(1024);
        resp["ip"] = ip;
        resp["mac"] = wifiManager.getMac();
        serializeJson(resp, *response);
        request->send(response);
    });

    ws.onEvent([this] (AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len) {
        this->wsHandler(server, client, type, arg, data, len);
    });
    webServer.addHandler(ledAmount);
    webServer.addHandler(wifiConnect);
    webServer.addHandler(ledMode);
    webServer.addHandler(&ws);
}

void ServerManager::run() {
    webServer.begin();
    logger->logln("Server started");
}

void ServerManager::cleanupWs() {
    ws.cleanupClients();
}

void ServerManager::wsHandler(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len) {
    if(type == WS_EVT_CONNECT) {
        logger->logln("WS Client connected");
    } else if(type == WS_EVT_DISCONNECT) {
        logger->logln("WS Client disconnected");
    } else if(type == WS_EVT_DATA) {
        AwsFrameInfo *info = (AwsFrameInfo*)arg;
        if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {

            const uint8_t size = JSON_OBJECT_SIZE(2);
            StaticJsonDocument<size> json;
            DeserializationError err = deserializeJson(json, data);
            if (err) {
                logger->logln("deserializeJson() failed with code ");
                logger->logln(err.c_str());
                return;
            }

            char *event = json["event"];
            std::string value = json["value"];
            logger->logln(event);
            logger->logln(value);
            if (strcmp(event, "delay") == 0) {
                wsDelay(atoi(value.c_str()));
            } else if (strcmp(event, "brightness") == 0) {
                wsBrightness(atoi(value.c_str()));
            }
        }
    }
}

void ServerManager::wsDelay(int delay) {
    if(delay < 1 || delay > 60) return;
    stateManager.setDelay(delay);
}

void ServerManager::wsBrightness(int brightness) {
    if(brightness < 1 || brightness > 255) return;
    stateManager.setBrightness(brightness);
}