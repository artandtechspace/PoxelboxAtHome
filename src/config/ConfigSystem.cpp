#include "ConfigSystem.h"

namespace ConfigSystem {

    // First note of the linked-list that holds all registered config entrys
    BaseEntry* first = nullptr;

    void initialize(){
        first = nullptr;

        Serial.println("[CfgSys::initialize]: Loading Config-Entrys");

        // Iterates over each known config entry and initializes it
        auto current = first;
        while(current != nullptr){
            current->load();
            Serial.print("\tLoaded ");
            Serial.println(current->getTopic());
            current = current->next;
        }
    }

    ByteEntry* mkByte(int offset, const char* mqttTopic, byte value, byte min, byte max, void (*onChange)(byte value)) {

        auto obj = new ByteEntry(offset, mqttTopic, value, min, max, onChange);

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
