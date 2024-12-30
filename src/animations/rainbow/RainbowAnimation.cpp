#include <Arduino.h>
#include "../../config/ConfigSystem.h"
#include "./RainbowAnimation.h"
#include <FastLED.h>
#include "../../poxelbox/Poxelbox.h"

namespace RainbowAnimation
{

    ByteEntry *speed = ConfigSystem::mkByte(0, "cfg/rbow/speed", 100, 10);
    ByteEntry *offsetX = ConfigSystem::mkByte(2, "cfg/rbow/offsx", 20);
    ByteEntry *offsetY = ConfigSystem::mkByte(3, "cfg/rbow/offsy", 40);

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
