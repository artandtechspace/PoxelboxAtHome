
#include "../../poxelbox/Poxelbox.h"
#include <FastLED.h>
#include <Arduino.h>
#include "../../config/ConfigSystem.h"
#include "../../config/MemoryOffsets.h"
#include "../../config/entrys/ByteEntry.h"


namespace RandomAnimation {

    ByteEntry* slow = ConfigSystem::mkByte(MEM_OFFSET_CFG_RANDOM_SLOW, "cfg/rdm/slow", 30);

    void loop() {
        static long next = 0;

        if(millis() < next) return;
            next = millis() + slow->get();

        #if 0
            Serial.println("Random slow: "+String(slow->get()));
        #endif
        
        for(int i=0;i<30;i++){

            Poxelbox::leds[random(0,LED_AMT)] = CHSV(
                random(0,255),
                255,
                255
            );
        }
        FastLED.show();
    }

}
