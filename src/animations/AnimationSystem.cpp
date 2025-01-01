#include "AnimationSystem.h"
#include <Arduino.h>
#include "./config/ConfigSystem.h"
#include "mqtt/MqttHandler.h"
#include <EEPROM.h>
#include "poxelbox/Poxelbox.h"
#include "config/MemoryOffsets.h"

#include "animations/rainbow/RainbowAnimation.h"
#include "animations/points/PointsAnimation.h"
#include "animations/off/OffAnimation.h"
#include "animations/random/RandomAnimation.h"
#include "animations/singlecolor/SingleColorAnimation.h"

namespace AnimationSystem {

// Registered animations
Animation animations[] = {
  {nullptr,                     RainbowAnimation::loop,     nullptr},
  {PointsAnimation::setup,      PointsAnimation::loop,      nullptr},
  {OffAnimation::setup,         OffAnimation::loop,         nullptr},
  {nullptr,                     RandomAnimation::loop,      nullptr},
  {SingleColorAnimation::setup, SingleColorAnimation::loop, SingleColorAnimation::cleanup},
};

// How many animations are registered
byte animationAmount = sizeof(animations)/sizeof(Animation);


// Entry that holds the selected animation type
ByteEntry* selectedAnimation = ConfigSystem::mkByte(MEM_OFFSET_TYPE, "type", 0, animationAmount-1, &onAnimationChange);

void setup(){
    #if 0
        Serial.println("Setup animation. Starting with: "+String(selectedAnimation->get()));
    #endif

    // Runs the setup for the current animation
    if(animations[selectedAnimation->get()].setup != nullptr)
        animations[selectedAnimation->get()].setup();
}

void loop(){
    // Updates the current animation
    if(animations[selectedAnimation->get()].loop != nullptr)
        animations[selectedAnimation->get()].loop();
}

void onAnimationChange(byte idxFrom, byte idxTo){
    // Runs the cleanup for the previous animation
    if(animations[idxFrom].cleanup != nullptr)
        animations[idxFrom].cleanup();

    if(animations[idxTo].setup != nullptr)
        animations[idxTo].setup();
}



}