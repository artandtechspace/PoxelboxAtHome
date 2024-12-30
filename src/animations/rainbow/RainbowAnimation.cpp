#include <Arduino.h>
#include "../../config/ConfigSystem.h"
#include "./RainbowAnimation.h"

namespace RainbowAnimation {
    
    ByteEntry* speed = ConfigSystem::mkByte(0,"cfg/rbow/speed",10);

    void setup(){
        Serial.print("[Rainbow-Setup] ");
        Serial.println(speed->get());
    }

    void loop() {
        static long next = 0;

        if(millis() < next) return;
        next = millis() + 500;

        Serial.println("[RAINBOW-Loop]");
        Serial.println(speed->get());

    }

}
