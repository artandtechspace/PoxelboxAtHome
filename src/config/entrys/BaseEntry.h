#pragma once

#include <Arduino.h>
#include <MqttClient.h>

class BaseEntry {
protected:
    // Holds the memory offset to write the given config entry into eeprom
    int memoryOffset;
    // Which mqtt topic will be used to handle this entry
    const char* topic;

public:
    // Called once when the microcontroller starts up
    // Loads the config value from eeprom
    virtual void load() = 0;
    // Called when a message is retreived
    // Validates it, save the new value to eeprom
    virtual void save(char* msg) = 0;

    // Used to write
    virtual void writeMessage(MqttClient* client);

    // Next entry in the linked-list structure
    // This is implemented into the entry's directly
    // because of this convinience
    BaseEntry* next;
    // Returns the mqtt-topic of this entry
    const char* getTopic();
};