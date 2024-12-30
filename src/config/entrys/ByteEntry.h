#pragma once

#include "BaseEntry.h"

class ByteEntry : public BaseEntry {
protected:
    // The config value and the min/max size constrains
    // These shall be no less than byte-size constrains. Meaning between 0 and 255 inclusive
    byte value, minConstr, maxConstr;
    void (*changeCallback)(byte value);

public:
    ByteEntry(int offset, const char* mqttTopic, byte defaultValue, byte min, byte max, void (*onChange)(byte value));

    byte get();
    virtual void save(char* msg) override;
    void load() override;
};