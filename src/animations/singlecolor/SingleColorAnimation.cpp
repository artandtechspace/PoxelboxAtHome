
#include "../../poxelbox/Poxelbox.h"
#include <FastLED.h>
#include <Arduino.h>
#include "../../config/ConfigSystem.h"
#include "../../config/entrys/ByteEntry.h"
#include "../../config/MemoryOffsets.h"
#include "./SingleColorAnimation.h"
#include "../../main.h"


namespace SingleColorAnimation {

    ByteEntry* hue = ConfigSystem::mkByte(MEM_OFFSET_CFG_SINGLE_COLOR_HUE, "cfg/sclr/hue", 0, 255, &onChange);
    ByteEntry* saturation = ConfigSystem::mkByte(MEM_OFFSET_CFG_SINGLE_COLOR_SATURATION, "cfg/sclr/sat", 0, 255, &onChange);
    ByteEntry* value = ConfigSystem::mkByte(MEM_OFFSET_CFG_SINGLE_COLOR_VALUE, "cfg/sclr/val", 0, 255, &onChange);

    void onChange(byte _){
        if(selectedAnimation->get() != 4) return;

        auto clr = CHSV(hue->get(), saturation->get(), value->get());

        for(int i=0;i<LED_AMT;i++)
            Poxelbox::leds[i] = clr;

        FastLED.show();
    }

    void setup() {
        onChange(0);
    }

    void loop() {
        delay(500);
    }

}
