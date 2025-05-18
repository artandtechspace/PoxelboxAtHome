#include "StringEntry.h"
#include <MqttClient.h>
#include <EEPROM.h>
#include "../../util/string/StringUtil.h"

StringEntry::StringEntry(int offset, int offsetEnd, const char* mqttTopic, void (*onChange)()) {
    if(offset >= offsetEnd){
        Serial.print("Invalid storage allocated for StringEntry from");
        Serial.print(offset);
        Serial.print(" to ");
        Serial.println(offsetEnd);
        while(true)delay(1000);
    }

    changeCallback = onChange;
    maxLength = offsetEnd - offset-1;
    memoryOffset = offset;
    topic = mqttTopic;
    next = nullptr;

    // Allocates the memory (With nullterminator)
    value = new char[maxLength +1];
};

StringEntry::~StringEntry(){
    delete[] value;
}

const char* StringEntry::get(){
    return value;
}

void StringEntry::load() {
    // Loads the data
    for(int i=0;i<maxLength;i++){
        if(i==0 || i == maxLength-1)
        value[i] = EEPROM.readChar(memoryOffset + i);
    }

    // Adds the null terminator
    value[maxLength] = '\0';
}

void StringEntry::save(char* msg) {

    // Removes any old data
    for(int i=0;i<=maxLength+1;i++)
        value[i]='\0';

    // Gets the length of the message
    int msgLen = StringUtil::length(msg);

    // Calculates the length
    int newLen = min(maxLength, msgLen);

    // Copies the value and writes it to eeprom
    for(int i=0;i<newLen;i++){
        value[i] = msg[i];
        EEPROM.writeChar(memoryOffset+i, value[i]);
    }
    // Adds nullterminiator
    value[newLen] = '\0'; 

    // Also inserts a null terminator into the storage if the length is less than full (To cut the string before final length)
    if(newLen < maxLength)
        EEPROM.writeChar(memoryOffset+newLen, '\0');

    EEPROM.commit();

    if(changeCallback != nullptr)
        changeCallback();
}

void StringEntry::writeMessage(MqttClient* client){
    int len = StringUtil::length(value);

    for(int i=0;i<len;i++){
        client->print(value[i]);
    }
}