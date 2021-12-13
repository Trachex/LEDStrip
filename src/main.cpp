#include <Arduino.h>
#include "DependencyManager/DependencyManager.hpp"

class Tape {
	public:
		Tape();
		void tick();
	private:
		LEDManager& ledManager;
};

Tape::Tape() : ledManager(dependencyManager.getLEDManager()) {
	dependencyManager.getServerManager().run();
	Serial.println("Server Started");
}

void Tape::tick() {
	ledManager.tick();
}

Tape* api;

void setup() {
	Serial.begin(9600);
	api = new Tape();
}

void loop() {
	api->tick();
}