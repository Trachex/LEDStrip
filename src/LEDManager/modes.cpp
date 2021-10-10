#include "modes.hpp"

void rainbow(CRGB* leds, int ledCount) {
    static int r = 255;
    static int g = 0;
    static int b = 0;

    if(r > 0 && b == 0) {
        r--;
        g++;
    }

    if(g > 0 && r == 0) {
        g--;
        b++;
    }

    if(b > 0 && g == 0){
        b--;
        r++;
    }

    for(int i = 0; i < ledCount; i++) {
        leds[i] = CRGB(r, g, b);
    }
}

modeArr modes[] = { rainbow };