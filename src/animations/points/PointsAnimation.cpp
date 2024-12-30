
#include "../../poxelbox/Poxelbox.h"
#include <FastLED.h>
#include <Arduino.h>
#include "../../config/ConfigSystem.h"
#include "../../config/entrys/ByteEntry.h"

#define PT_AMT 20

namespace PointsAnimation {

    ByteEntry* slow = ConfigSystem::mkByte(4, "cfg/pts/slow", 30);

    typedef struct {
        int perc;
        int x;
        int y;
        int clr;
    } Point;

    // List of points
    Point points[PT_AMT];

    void setup() {
        for(int i=0;i<PT_AMT; i++){
            Point* p = &points[i];
            p->perc = random(60,255);
            p->x = random(0,BOX_SIZE_X * BOX_AMT_X);
            p->y = random(0,4);
            p->clr = random(0,255);
        }
    }

    void loop() {
        static long next = 0;

        if(millis() < next) return;
        next = millis() + slow->get();

        // Iterates over each point
        for(int i=0;i<PT_AMT;i++){

            Point* p = &points[i];

            p->perc++;

            #if 0
                Serial.println("[Points]: i="+String(i)+" perc="+String(p->perc));
            #endif

            if(p->perc >= 255){
                Poxelbox::leds[Poxelbox::getPBId(p->x,p->y)] = 0;
                
                p->perc = random(60,255);
                p->x = random(0,BOX_SIZE_X * BOX_AMT_X);
                p->y = random(0,4);
                p->clr = random(0,255);
            }

            Poxelbox::leds[Poxelbox::getPBId(p->x,p->y)] = CHSV(
                p->clr,
                255,
                p->perc
            );
        }

        FastLED.show();
    }

}
