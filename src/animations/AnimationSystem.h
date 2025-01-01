#pragma once
#include <Arduino.h>

namespace AnimationSystem {

// Holds all functions to call for an animation
// All are nullable
struct Animation {
    // Called when the animation starts
    void (*setup)();
    // Called to continue the animation
    void (*loop)();
    // Called when the animation ends
    void (*cleanup)();
};

void setup();
void loop();
void onAnimationChange(byte from, byte to);

}