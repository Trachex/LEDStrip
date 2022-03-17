#pragma once

#include <FastLED.h>
#include "StateManager/State.hpp"

typedef void (*modeArr) (CRGB* leds, ModeState state);

void rainbow(CRGB* leds, ModeState state);

extern modeArr modes[];
extern int modeAmount;