#pragma once

#include "BaseEntry.h"

class StringEntry : public BaseEntry {
protected:
    // Pointer to the actual string
    // Has an allocation of maxLength+1 for the null terminator
    char* value;
    // Max length of the string
    int maxLength;

    // Holds a single callback that can be fired after the value changes
    void (*changeCallback)();
public:
    StringEntry(int offset, int maxLength, const char* mqttTopic, void (*onChange)());
    ~StringEntry();

    const char* get();
    void writeMessage(MqttClient* client);
    virtual void save(char* msg) override;
    void load() override;
};