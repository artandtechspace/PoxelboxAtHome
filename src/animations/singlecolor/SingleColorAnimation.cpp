
#include "../../poxelbox/Poxelbox.h"
#include <FastLED.h>
#include <Arduino.h>
#include "../../config/ConfigSystem.h"
#include "../../config/entrys/ByteEntry.h"
#include "../../config/MemoryOffsets.h"
#include "./SingleColorAnimation.h"
#include "../../globalconfig/GlobalConfig.h"

namespace SingleColorAnimation {

    ByteEntry* hue = ConfigSystem::mkByte(MEM_OFFSET_CFG_SINGLE_COLOR_HUE, "cfg/sclr/hue", 0, 255);
    ByteEntry* saturation = ConfigSystem::mkByte(MEM_OFFSET_CFG_SINGLE_COLOR_SATURATION, "cfg/sclr/sat", 0, 255);

    void onChange(byte from, byte to){
        auto clr = CHSV(hue->get(), saturation->get(), GlobalConfig::globalBrightness->get());

        for(int i=0;i<LED_AMT;i++)
            Poxelbox::setPixel(i, clr);

        FastLED.show();
    }

    void setup() {
        hue->setChangeListener(&onChange);
        saturation->setChangeListener(&onChange);
        GlobalConfig::globalBrightness->setChangeListener(&onChange);
        onChange(0,0);
    }

    void loop() {
        delay(500);
    }

    void cleanup(){
        hue->setChangeListener(nullptr);
        saturation->setChangeListener(nullptr);
        GlobalConfig::globalBrightness->setChangeListener(nullptr);
    }

}
