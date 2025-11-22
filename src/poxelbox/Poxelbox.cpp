#include "Poxelbox.h"
#include "../globalconfig/GlobalConfig.h"

namespace Poxelbox {

    // Which pin the box uses
    const int LED_PIN = 19;

    // LED-Api
    CRGB leds[LED_AMT];

    // Lookup table for the on-box pixel
    int lookUpTable[BOX_SIZE_Y][BOX_SIZE_X] = {
        { 4, 3, 2},
        { 5, 0, 1},
        { 6,11,10},
        { 7, 8, 9}
    };

    void setPixel(int index, const CRGB& clr){
        // Ensure no invalid reads
        if(index < 0 || index >= LED_AMT){
            # if 0
                Serial.println("Bad-Index detected: "+String(index));
            # endif
            return;
        }

        leds[index] = clr;
    };

    void setPixel(int x, int y, const CRGB& clr){
        const int height = GlobalConfig::poxelboxHeight->get();

        // Gets the box position
        const int boxX = x / BOX_SIZE_X;
        const int boxY = y / BOX_SIZE_Y;

        // Gets the local pixel position on the box
        const int pxlX = x - BOX_SIZE_X * boxX;
        const int pxlY = y - BOX_SIZE_Y * boxY;

        // Calculates the boxes before the current one
        int boxesBefore=0;

        // ... before on x axis
        boxesBefore += boxX * height;

        // ... before on the y axis (if poxel is in downward direction)
        if((boxX & 1) == 1)
            boxesBefore += (height - 1) - boxY;
        
        // ... before on the y axis (if poxel is upward direction)
        else
            boxesBefore += boxY;

        // Calculates the actual pixel
        int pxl = boxesBefore * (BOX_SIZE_X * BOX_SIZE_Y) + lookUpTable[BOX_SIZE_Y-1 - pxlY][pxlX];
        
        setPixel(pxl, clr);
    }

    void setup(){
        Serial.println("[Poxelbox::setup]: Starting FastLed");

        // Setups fastled-library
        FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, LED_AMT);
    }

}