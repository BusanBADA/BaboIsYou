#pragma once
#include <vector>
#include <cassert>
#include "Fixed64.h"
#include "Constants.h"

namespace BABO::World {
	using namespace BABO::Core;
    struct GridPoint {
        int32_t x, y;
        bool operator==(const GridPoint& o) const { return x == o.x && y == o.y; }
    };

    struct Cell {
        std::vector<uint32_t> entities;
        bool isStaticWall = false; 
    };
}