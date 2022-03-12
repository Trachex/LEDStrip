#pragma once

#include <FastLED.h>

typedef void (*modeArr) (CRGB* leds, int ledCount);

void rainbow(CRGB* leds, int ledCount);

extern modeArr modes[];

const int amount = 1;