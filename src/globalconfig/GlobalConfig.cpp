
#include "../config/ConfigSystem.h"
#include "../config/MemoryOffsets.h"
#include "./GlobalConfig.h"

namespace GlobalConfig {

    // Setting for the global brightness
    ByteEntry* globalBrightness = ConfigSystem::mkByte(MEM_OFFSET_CFG_ALL_BRIGHTNESS, "cfg/all/brightness");

    // Settings for how many boxes are are next to each other (before stacking up)
    ByteEntry* poxelboxWidth = ConfigSystem::mkByte(MEM_OFFSET_CFG_POXELBOX_SIZE_WIDTH, "cfg/all/width", 1);
    ByteEntry* poxelboxHeight = ConfigSystem::mkByte(MEM_OFFSET_CFG_POXELBOX_SIZE_HEIGHT, "cfg/all/height", 1);
};