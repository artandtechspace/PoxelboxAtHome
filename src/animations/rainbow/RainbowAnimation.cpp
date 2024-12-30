#include <Arduino.h>
#include "../../config/ConfigSystem.h"
#include "./RainbowAnimation.h"
#include <FastLED.h>
#include "../../poxelbox/Poxelbox.h"
#include "../../config/MemoryOffsets.h"

namespace RainbowAnimation
{

    ByteEntry *speed = ConfigSystem::mkByte(MEM_OFFSET_CFG_RAINBOW_SPEED, "cfg/rbow/speed", 10);
    ByteEntry *offsetX = ConfigSystem::mkByte(MEM_OFFSET_CFG_RAINBOW_OFFSET_X, "cfg/rbow/offsx");
    ByteEntry *offsetY = ConfigSystem::mkByte(MEM_OFFSET_CFG_RAINBOW_OFFSET_Y, "cfg/rbow/offsy");

    void loop()
    {
        static long next = 0;
        if (millis() < next)
            return;
        next = millis() + 50;

        for (int y = 0; y < BOX_SIZE_Y; y++)
        {
            for (int x = 0; x < BOX_SIZE_X * BOX_AMT_X; x++)
            {

                float perc = (float)((millis() + (offsetX->get() * 10) * x + (offsetY->get() * 10) * y) % (speed->get() * 100)) / (float)(speed->get() * 100);

                Poxelbox::leds[Poxelbox::getPBId(x, y)] = CHSV(
                    255 * perc,
                    255,
                    255);
            }
        }
        FastLED.show();
    }

}
