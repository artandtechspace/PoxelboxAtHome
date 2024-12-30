#pragma once

#include <FastLED.h>

#define BOX_SIZE_X 3
#define BOX_SIZE_Y 4

#define BOX_AMT_X 25

#define LED_AMT BOX_SIZE_X * BOX_SIZE_Y*BOX_AMT_X


namespace Poxelbox {
    extern const int LED_PIN;

    extern CRGB leds[LED_AMT];

    // Initializes the fast-led library and poxelbox connection
    void setup();

    // Returns the actual id from poxel-box-coordinates
    int getPBId(int x, int y);
}