#include <Arduino.h>
#include "./config/ConfigSystem.h"
#include "mqtt/MqttHandler.h"
#include <EEPROM.h>
#include "poxelbox/Poxelbox.h"
#include "config/MemoryOffsets.h"

#include "animations/AnimationSystem.h"

#define EEPROM_SIZE 250

void setup() {
  // Starts the serial interface
  Serial.begin(9600);

  delay(1000);

  // Setups the EEPROM
  Serial.println("\t\t[EEPROM] EEPROM.begin()");
  EEPROM.begin(EEPROM_SIZE);

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
