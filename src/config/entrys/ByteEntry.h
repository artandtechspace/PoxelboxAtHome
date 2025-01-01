#pragma once

#include "BaseEntry.h"

class ByteEntry : public BaseEntry {
protected:
    // The config value and the min/max size constrains
    // These shall be no less than byte-size constrains. Meaning between 0 and 255 inclusive
    byte value, minConstr, maxConstr;

    // Holds a single callback that can be fired when the value changes
    void (*changeCallback)(byte from, byte to);

public:
    ByteEntry(int offset, const char* mqttTopic, byte min, byte max, void (*onChange)(byte from, byte to));

    byte get();
    void writeMessage(MqttClient* client);
    virtual void save(char* msg) override;
    void load() override;

    // Sets a change listener that fires when an update is retreived
    void setChangeListener(void (*onChange)(byte from, byte to));
};