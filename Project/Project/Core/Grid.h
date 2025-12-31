#pragma once
#include <vector>
#include <cstdint>
#include "Constants.h"
#include "GameTypes.h" 
#include "Fix64.h"
namespace BABO::World {
    using namespace BABO::Math;
    using namespace BABO::Core;

    struct GridPoint {
        int32_t x, y;
        bool operator==(const GridPoint& o) const { return x == o.x && y == o.y; }
    };

    struct Cell {
        std::vector<uint32_t> entities;
        WordType wordType = (WordType)-1;
        bool isStaticWall = false;

        void Reset() {
            entities.clear();
            wordType = (WordType)-1;
            isStaticWall = false;
        }
    };

    class GridSystem {
        int32_t m_width = 0, m_height = 0;
        std::vector<Cell> m_cells;
        GridSystem() = default;
    public:
        void Resize(int w, int h) { m_width = w; m_height = h; m_cells.clear(); m_cells.resize(w * h); }

        BABO::World::GridPoint WorldToGrid(BABO::Math::Fix64 x, BABO::Math::Fix64 y) const {
            return { (int32_t)(x / 30.0f).ToInt(), (int32_t)(y / 30.0f).ToInt() };
        }
        bool IsInBounds(int x, int y) const { return x >= 0 && x < m_width && y >= 0 && y < m_height; }
        Cell* GetCell(int x, int y) { return IsInBounds(x, y) ? &m_cells[x + y * m_width] : nullptr; }
        const Cell* GetCell(int x, int y) const {
            return IsInBounds(x, y) ? &m_cells[x + y * m_width] : nullptr;
        }
        void Reset() { for (auto& c : m_cells) c.Reset(); }
        int GetWidth() const { return m_width; }
        int GetHeight() const { return m_height; }
        static GridSystem& instance() {
            static GridSystem instance;
            return instance;
        }
        GridSystem(const GridSystem&) = delete;
        GridSystem& operator=(const GridSystem&) = delete;
    };
}