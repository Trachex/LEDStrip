#include "modes.hpp"

void rainbow(CRGB* leds, ModeState state) {
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

    for(int i = 0; i < state.ledCount; i++) {
        CHSV tmp = rgb2hsv_approximate(CRGB(r, g, b));
        tmp.v = state.brightness;
        leds[i] = tmp; 
    }
}

modeArr modes[] = { rainbow };
int modeAmount = sizeof(modes) / sizeof(modes[0]);