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


#define EEPROM_SIZE 20

// Used as a blob that holds the pointer to the animations setup and loop functions
struct Animation {
  void (*setup)();
  void (*loop)();
};

// Registered animations
Animation animations[] = {
  {nullptr, RainbowAnimation::loop},
  {PointsAnimation::setup, PointsAnimation::loop},
  {OffAnimation::setup, OffAnimation::loop},
  {nullptr, RandomAnimation::loop},
};

// How many animations are registered
byte animationAmount = sizeof(animations)/sizeof(Animation);

// Entry that holds the selected animation type
ByteEntry* selectedAnimation = ConfigSystem::mkByte(MEM_OFFSET_TYPE, "type", 0, 0, animationAmount-1, [](byte idx) -> void {
  if(animations[idx].setup != nullptr)
    animations[idx].setup();
});


void setup() {
  // Setups the EEPROM
  EEPROM.begin(EEPROM_SIZE);
  // Starts the serial interface
  Serial.begin(9600);

  delay(1000);

  ConfigSystem::initialize();

  MqttHandler::setup();

  Poxelbox::setup();
}

void loop() {

  // Maintains the mqtt-connection
  MqttHandler::loop();

  // Inserts a least a very minimal delay
  delay(10);

  // Runs the current animation
  animations[selectedAnimation->get()].loop();

}
