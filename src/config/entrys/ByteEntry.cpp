#include "ByteEntry.h"
#include <MqttClient.h>
#include <EEPROM.h>

ByteEntry::ByteEntry(int offset, const char* mqttTopic, byte defaultValue, byte min, byte max, void (*onChange)(byte value)) {
    memoryOffset = offset;
    topic = mqttTopic;
    value = defaultValue;
    next = nullptr;
    minConstr = min;
    maxConstr = max;
    changeCallback = onChange;
};

byte ByteEntry::get(){
    return value;
}

void ByteEntry::load() {

    // Reads the value from eeprom
    value = EEPROM.readByte(memoryOffset);

    // Validates it
    if(value < minConstr)
        value = minConstr;
    else if(value > maxConstr)
        value = maxConstr;

    // Fires the change callback
    if(changeCallback != nullptr)
        changeCallback(value);
}

void ByteEntry::save(char* msg) {

    // Converts the value to a long
    long byteValue = strtol(msg, nullptr, 10);

    // Validates the constrains (Must be at least byte-constrains (0-255))
    if(byteValue < minConstr)
        byteValue = minConstr;
    else if(byteValue > maxConstr)
        byteValue = maxConstr;

    // Converts the value
    value = static_cast<byte>(byteValue);

    // Fires the callback (if required)
    if(changeCallback != nullptr)
        changeCallback(value);

    // Writes the new value to eeprom
    EEPROM.write(memoryOffset, value);
    EEPROM.commit();
}