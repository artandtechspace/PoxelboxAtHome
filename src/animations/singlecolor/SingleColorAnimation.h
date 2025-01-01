#pragma once

#include <Arduino.h>

namespace SingleColorAnimation {

    void setup();
    void loop();
    void cleanup();

    // Handler that fires when any value changes and the color shall be updated
    void onChange(byte from, byte to);

}