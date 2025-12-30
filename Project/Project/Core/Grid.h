#pragma once
#include <vector>
#include <cassert>
#include "Fixed64.h"
#include "Constants.h"
//////////////////////////////
//  //
//////////////////////////////
namespace BABO::World {
    using namespace BABO::Math;
    using namespace BABO::Core;

    struct GridPoint {
        int32_t x, y;
        bool operator==(const GridPoint& o) const { return x == o.x && y == o.y; }
    };

    struct Cell {
        std::vector<uint32_t> entities; 
        bool isStaticWall = false;     
    };

    class GridSystem {
    private:
        int32_t m_width;
        int32_t m_height;
        std::vector<Cell> m_cells;

    public:
        GridSystem() : m_width(0), m_height(0) {}


        void Resize(int32_t width, int32_t height) {
            m_width = width;
            m_height = height;
            m_cells.clear();
            m_cells.resize(width * height);
        }

  
        GridPoint WorldToGrid(Fix64 x, Fix64 y) const {
            int32_t gx = (x / TILE_SIZE_F).ToInt();
            int32_t gy = (y / TILE_SIZE_F).ToInt();
            return { gx, gy };
        }

        Vector2Fixed GridToWorldCenter(int32_t gx, int32_t gy) const {
            return {
                (Fix64(gx) * TILE_SIZE_F) + TILE_HALF_F,
                (Fix64(gy) * TILE_SIZE_F) + TILE_HALF_F
            };
        }

        bool IsInBounds(int32_t x, int32_t y) const {
            return x >= 0 && x < m_width && y >= 0 && y < m_height;
        }


        Cell* GetCell(int32_t x, int32_t y) {
            if (!IsInBounds(x, y)) return nullptr;
            return &m_cells[x + y * m_width];
        }


        const Cell* GetCell(int32_t x, int32_t y) const {
            if (!IsInBounds(x, y)) return nullptr;
            return &m_cells[x + y * m_width];
        }

        void Reset() {
            for (auto& cell : m_cells) {
                cell.entities.clear();
                cell.isStaticWall = false;
            }
        }

        int32_t GetWidth() const { return m_width; }
        int32_t GetHeight() const { return m_height; }
    };
}