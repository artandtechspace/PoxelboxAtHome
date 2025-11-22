#pragma once

#include <FastLED.h>
#include "../globalconfig/GlobalConfig.h"

#define BOX_SIZE_X 3
#define BOX_SIZE_Y 4

#define MAX_BOX_AMT 25

#define LED_AMT BOX_SIZE_X * BOX_SIZE_Y * MAX_BOX_AMT

#define WIDTH GlobalConfig::poxelboxWidth->get() * BOX_SIZE_X
#define HEIGHT GlobalConfig::poxelboxHeight->get() * BOX_SIZE_Y

namespace Poxelbox {
    // Initializes the fast-led library and poxelbox connection
    void setup();

    // Sets a pixel by index on the poxelbox
    void setPixel(int index, const CRGB& clr);

    /**
     * Sets the x/y pixel of the box.
     * (Front view) Coordinate system works from the left bottom (0,0)
     * (Front view) Cables must run alternating from bottom->top, top->bottom,...
     *              and must start at (0,0)
     */
    void setPixel(int x, int y, const CRGB& clr);
}