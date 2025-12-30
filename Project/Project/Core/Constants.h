#pragma once
#include "Fix64.h"

namespace BABO::Core {
    using namespace BABO::Math;

    constexpr int TILE_SIZE_INT = 30; 
    const Fix64 TILE_SIZE_F = Fix64(TILE_SIZE_INT);
    const Fix64 TILE_HALF_F = TILE_SIZE_F / Fix64(2); 
    const double MS_PER_UPDATE = 1.0 / 60.0;
}