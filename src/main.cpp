#include <Arduino.h>
#include "./config/ConfigSystem.h"
#include "mqtt/MqttHandler.h"
#include <EEPROM.h>
#include "poxelbox/Poxelbox.h"
#include "config/MemoryOffsets.h"

#include "animations/AnimationSystem.h"

#define EEPROM_SIZE 20

void setup() {
  // Setups the EEPROM
  EEPROM.begin(EEPROM_SIZE);
  // Starts the serial interface
  Serial.begin(9600);

  delay(1000);

  ConfigSystem::initialize();

  MqttHandler::setup();

  Poxelbox::setup();

  AnimationSystem::setup();
}

void loop() {

  // Maintains the mqtt-connection
  MqttHandler::loop();

  // Inserts a least a very minimal delay
  delay(10);

  AnimationSystem::loop();
}
