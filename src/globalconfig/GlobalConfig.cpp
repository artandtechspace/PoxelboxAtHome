
#include "../config/ConfigSystem.h"
#include "../config/MemoryOffsets.h"
#include "./GlobalConfig.h"

namespace GlobalConfig {

    // Setting for the global brightness
    ByteEntry* globalBrightness = ConfigSystem::mkByte(MEM_OFFSET_CFG_ALL_BRIGHTNESS, "cfg/all/brightness");

};