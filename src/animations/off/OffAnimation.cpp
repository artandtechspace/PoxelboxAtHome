
#include "../../poxelbox/Poxelbox.h"
#include <FastLED.h>
#include <Arduino.h>
#include "../../config/ConfigSystem.h"
#include "../../config/entrys/ByteEntry.h"


namespace OffAnimation {

    void setup() {
        for(int i=0;i<LED_AMT;i++)
            Poxelbox::leds[i] = 0;

        FastLED.show();
    }

    void loop() {
        delay(500);
    }

}
