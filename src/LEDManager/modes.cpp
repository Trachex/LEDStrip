#include <FastLED.h>

typedef void (*modeArr) (CRGB* leds, int ledCount);

void rainbow(CRGB* leds, int ledCount) {
    int r = 255;
    int g = 0;
    int b = 0;

    do {
        if(r > 0 && b == 0) {
            r--;
            g++;
        }

        if(g > 0 && r == 0) {
            g--;
            b++;
        }

        if(b > 0 && g == 0){
            r++;
            b--;
        }

        for(int i = 0; i < ledCount; i++) {
            leds[i] = CRGB(r, g, b);
        }
        FastLED.show();

    } while(r != 255);
}

modeArr modes[] = { rainbow };