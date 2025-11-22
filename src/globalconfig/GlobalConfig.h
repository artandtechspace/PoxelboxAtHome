#pragma once

#include "../config/ConfigSystem.h"


// #######################
// #      Important      #
// #######################
//
// Even tho there is a setting of width/height for the boxes,
// this device is still limited by its RAM.
// So a hard limit of at max X Boxes can be configured
// The limit is set inside the Poxelbox.h file

namespace GlobalConfig {

    // Setting for the global brightness
    extern ByteEntry* globalBrightness;

    // Settings for how many boxes are are next to each other (before stacking up)
    extern ByteEntry* poxelboxWidth;
    extern ByteEntry* poxelboxHeight;

};