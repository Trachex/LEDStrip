#include <Arduino.h>
#include "LEDManager/LEDManager.hpp"

class Tape {
	public:
		Tape();
		void tick();
	private:
		LEDManager* ledManager;
};

Tape::Tape() {
	ledManager = new LEDManager();
}

void Tape::tick() {
	ledManager->tick();
}

Tape* api;

void setup() {
	api = new Tape();
}

void loop() {
	api->tick();
}