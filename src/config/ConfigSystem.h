#pragma once

#include "./entrys/BaseEntry.h"
#include "./entrys/ByteEntry.h"

namespace ConfigSystem {

    // Used to register a given entry as a note
    void onNewEntry(BaseEntry* ptr);

    // Returns a new instance of a byte entry
    ByteEntry* mkByte(int offset, const char* mqttTopic, byte min = 0, byte max = 255, void (*onChange)(byte from, byte to) = nullptr);

    // Initializes the config system
    void initialize();

    // Returns the first linked list entry
    BaseEntry* getFirstLLEntry();

}