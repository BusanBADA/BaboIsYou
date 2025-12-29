#pragma once
#include "Fixed64.h"

namespace BABO::Core {
	constexpr int TILE_SIZE_INT = 30;
	const Fixed64 TILE_SIZE_F = Fixed64(TILE_SIZE_INT);
	const Fixed64 TILE_HALF_F = TILE_SIZE_F / Fixed64(2);
}