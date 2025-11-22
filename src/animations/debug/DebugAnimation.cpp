#include "../../poxelbox/Poxelbox.h"
#include <FastLED.h>
#include <Arduino.h>
#include "../../config/ConfigSystem.h"
#include "../../config/entrys/ByteEntry.h"
#include "../../config/MemoryOffsets.h"
#include "./DebugAnimation.h"
#include "../../globalconfig/GlobalConfig.h"

namespace DebugAnimation {

    // Position data
    int x,y;
    // 0=>Red, 1=>Green, 2=>Blue, 3=>White, 4=>Black
    byte index;

    void setup() {
        x=y=index=0;
    }

    void loop() {

        // Ensures that this goes:
        // first x: 0-> end
        // then  y: 0-> end
        // then  index 0-> 4
        if(x >= WIDTH){
            x=0;
            ++y;
            if(y >= HEIGHT){
                y=0;
                ++index;
                if(index > 4)
                    index = 0;
            }
        }

        // Sets the next one
        Poxelbox::setPixel(
            x, y,
            index == 0 ? CRGB::Red :
            index == 1 ? CRGB::Green :
            index == 2 ? CRGB::Blue :
            index == 3 ? CRGB::White :
            0
        );
        FastLED.show();

        delay(100);

        ++x;
    }
}
