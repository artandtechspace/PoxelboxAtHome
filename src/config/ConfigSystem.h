#pragma once

#include "./entrys/BaseEntry.h"
#include "./entrys/ByteEntry.h"
#include "./entrys/StringEntry.h"

namespace ConfigSystem {

    // Used to register a given entry as a note
    void onNewEntry(BaseEntry* ptr);

    // Returns a new instance of a byte entry
    ByteEntry* mkByte(int offset, const char* mqttTopic, byte min = 0, byte max = 255, void (*onChange)(byte from, byte to) = nullptr);

    // Returns a new instance of a string entry
    StringEntry* mkString(int offset, int offsetEnd, const char* mqttTopic, void (*changeCallback)() = nullptr);

    // Initializes the config system
    void initialize();

    // Returns the first linked list entry
    BaseEntry* getFirstLLEntry();

}