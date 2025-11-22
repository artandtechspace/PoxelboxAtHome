
#include "../../poxelbox/Poxelbox.h"
#include <FastLED.h>
#include <Arduino.h>
#include "../../config/ConfigSystem.h"
#include "../../config/entrys/ByteEntry.h"
#include "../../config/MemoryOffsets.h"
#include "../../globalconfig/GlobalConfig.h"
#include "./PointsAnimation.h"

#define PT_AMT 20

namespace PointsAnimation {

    ByteEntry* slow = ConfigSystem::mkByte(MEM_OFFSET_CFG_POINTS_SLOW, "cfg/pts/slow");

    // List of points
    Point points[PT_AMT];

    void resetPoint(Point* p) {
        p->perc = (float)random(20,100) / 100.0;
        p->x = random(0,WIDTH);
        p->y = random(0,HEIGHT);
        p->clr = random(0,255);
    }

    void setup() {
        for(int i=0;i<PT_AMT; i++)
            resetPoint(&points[i]);
    }

    void loop() {
        static long next = 0;

        if(millis() < next) return;
        next = millis() + slow->get();

        // Iterates over each point
        for(int i=0;i<PT_AMT;i++){

            Point* p = &points[i];

            p->perc += 0.01;

            #if 0
                Serial.println("[Points]: i="+String(i)+" perc="+String(p->perc)+" brigh="+GlobalConfig::globalBrightness->get());
            #endif

            if(p->perc >= 1){
                Poxelbox::setPixel(p->x, p->y, CRGB::Black);
                resetPoint(p);
            }

            Poxelbox::setPixel(p->x, p->y, CHSV(
                p->clr,
                255,
                p->perc * GlobalConfig::globalBrightness->get()
            ));
        }

        FastLED.show();
    }

}
