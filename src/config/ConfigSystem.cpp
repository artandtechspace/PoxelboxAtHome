#include "ConfigSystem.h"

namespace ConfigSystem {

    // First note of the linked-list that holds all registered config entrys
    BaseEntry* first = nullptr;

    void initialize(){
        Serial.println("[CfgSys::initialize]: Loading Config-Entrys");

        // Iterates over each known config entry and initializes it
        auto current = first;
        while(current != nullptr){
            current->load();
            current = current->next;
        }
    }


    StringEntry* mkString(int offset, int offsetEnd, const char* mqttTopic, void (*changeCallback)()) {
        auto obj = new StringEntry(offset, offsetEnd, mqttTopic, changeCallback);

        onNewEntry(obj);

        return obj;
    }

    ByteEntry* mkByte(int offset, const char* mqttTopic, byte min, byte max, void (*onChange)(byte from, byte to)) {

        auto obj = new ByteEntry(offset, mqttTopic, min, max, onChange);

        onNewEntry(obj);

        return obj;
    }

    void onNewEntry(BaseEntry* ptr){
        if(first == nullptr){
            first = ptr;
            return;
        }

        auto current = first;

        while(current->next != nullptr)
            current = current->next;

        current->next = ptr;
    }


    BaseEntry* getFirstLLEntry() {
        return first;
    }
}

