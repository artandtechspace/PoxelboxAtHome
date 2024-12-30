#include "Poxelbox.h"

namespace Poxelbox {

    const int LED_PIN = 19;

    CRGB leds[LED_AMT];

    // Lookup table for the on-box pixel
    int lookUpTable[BOX_SIZE_Y][BOX_SIZE_X] = {
        { 4, 3, 2},
        { 5, 0, 1},
        { 6,11,10},
        { 7, 8, 9}
    };

    int getPBId(int x, int y){
        // Pre current box
        int boxX = x/BOX_SIZE_X;
        int onBoxX = x % BOX_SIZE_X;
        int lookupId = lookUpTable[y][onBoxX];

        int id = boxX * BOX_SIZE_X * BOX_SIZE_Y + lookupId;

        //Serial.println("X:"+String(x)+" / "+String(y)+" = "+String(id)+" (LookupId="+String(lookupId)+") (BoxX = "+String(boxX)+") (onBoxX = "+onBoxX+")");

        return id;
    }

    void setup(){
        Serial.println("[Poxelbox::setup]: Starting FastLed");

        // Setups fastled-library
        FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_AMT);
    }

}