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
}

void Tape::tick() {
	ledManager.tick();
}

Tape* api;

void setup() {
	api = new Tape();
}

void loop() {
	api->tick();
}