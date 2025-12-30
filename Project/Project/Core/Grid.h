#pragma once
#include <vector>
#include "Fix64.h"
#include "Constants.h"
namespace BABO::Logic {
   
    enum class WordType {
        None = 0,
        PLAYER, WALL, ROCK,
        IS,                 
        YOU, PUSH, STOP     
    };
}
namespace BABO::World {
    using namespace BABO::Math;
    using namespace BABO::Core;

    struct GridPoint {
        int32_t x, y;
        bool operator==(const GridPoint& o) const { return x == o.x && y == o.y; }
    };

    struct Cell {
        std::vector<uint32_t> entities;
        BABO::Logic::WordType word = BABO::Logic::WordType::None; 
        bool isStaticWall = false;
    };

    class GridSystem {
        int32_t m_width = 0, m_height = 0;
        std::vector<Cell> m_cells;
    public:
        void Resize(int w, int h) { m_width = w; m_height = h; m_cells.clear(); m_cells.resize(w * h); }
        GridPoint WorldToGrid(Fix64 x, Fix64 y) const {
            return { (int32_t)(x / TILE_SIZE_F).ToInt(), (int32_t)(y / TILE_SIZE_F).ToInt() };
        }
        bool IsInBounds(int x, int y) const { return x >= 0 && x < m_width && y >= 0 && y < m_height; }
        Cell* GetCell(int x, int y) { return IsInBounds(x, y) ? &m_cells[x + y * m_width] : nullptr; }
        const Cell* GetCell(int x, int y) const { return IsInBounds(x, y) ? &m_cells[x + y * m_width] : nullptr; }
        int GetWidth() const { return m_width; }
        int GetHeight() const { return m_height; }
        void Reset() { for (auto& c : m_cells) { c.entities.clear(); c.isStaticWall = false; c.word = BABO::Logic::WordType::None; } }
    };
}