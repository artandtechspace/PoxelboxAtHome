#include "ByteEntry.h"
#include <MqttClient.h>
#include <EEPROM.h>

ByteEntry::ByteEntry(int offset, const char* mqttTopic, byte min, byte max, void (*onChange)(byte from, byte to)) {
    memoryOffset = offset;
    topic = mqttTopic;
    value = 0;
    next = nullptr;
    minConstr = min;
    maxConstr = max;
    changeCallback = onChange;
};

void ByteEntry::setChangeListener(void (*onChange)(byte from, byte to)){
    changeCallback = onChange;
}

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
    byte newValue = static_cast<byte>(byteValue);

    // Fires the callback (if required)
    if(changeCallback != nullptr)
        changeCallback(value, newValue);

    value = newValue;

    // Writes the new value to eeprom
    EEPROM.writeByte(memoryOffset, value);
    EEPROM.commit();
}

void ByteEntry::writeMessage(MqttClient* client){
    client->print(value);
}