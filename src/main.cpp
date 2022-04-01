#include <Arduino.h>
#include "DependencyManager/DependencyManager.hpp"

class Tape {
	public:
		Tape();
		void tick();
	private:
		LEDManager& ledManager;
		ServerManager& serverManager;
};

Tape::Tape() : ledManager(dependencyManager.getLEDManager()), serverManager(dependencyManager.getServerManager()) {
	serverManager.run();
}

void Tape::tick() {
	ledManager.tick();
	serverManager.cleanupWs();
}

Tape* api;

void setup() {
	Serial.begin(9600);
	api = new Tape();
}

void loop() {
	api->tick();
}