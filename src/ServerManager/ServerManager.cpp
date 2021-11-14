#include "ServerManager.hpp"

ServerManager::ServerManager() : 
stateManager(dependencyManager.getStateManager()),
wifiManager(dependencyManager.getWifiManager()), 
webServer(80) {

}

void ServerManager::run() {
    webServer.begin();
}