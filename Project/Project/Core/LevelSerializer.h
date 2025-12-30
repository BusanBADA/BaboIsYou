#pragma once
#include <fstream>
#include <vector>
#include <functional>
#include "Grid.h"
#include "Physics.h"

namespace BABO::IO {
    using namespace BABO::World;
    using namespace BABO::Physics;

    struct EntitySaveData {
        uint32_t id;
        int type;
        int wordId;
        int64_t x, y; //  Raw Value
    };

    class LevelSerializer {
    public:
        static bool SaveLevel(const std::string& filename,
            const GridSystem& grid,
            const std::vector<EntitySaveData>& entities) {
            std::ofstream out(filename);
            if (!out.is_open()) return false;

            out << "AXIOM_LEVEL_V1\n";
            out << grid.GetWidth() << " " << grid.GetHeight() << " " << TILE_SIZE_INT << "\n";

            out << "STATIC_WALLS\n";
            for (int y = 0; y < grid.GetHeight(); ++y) {
                for (int x = 0; x < grid.GetWidth(); ++x) {
                    out << (grid.GetCell(x, y)->isStaticWall ? 1 : 0) << " ";
                }
                out << "\n";
            }

            out << "ENTITIES " << entities.size() << "\n";
            for (const auto& e : entities) {
                out << e.id << " " << e.type << " " << e.wordId << " " << e.x << " " << e.y << "\n";
            }
            return true;
        }

        static bool LoadLevel(const std::string& filename,
            GridSystem& grid,
            PhysicsSolver& physics,
            std::function<void(uint32_t, int, int, Fix64, Fix64)> createFn) {
            std::ifstream in(filename);
            if (!in.is_open()) return false;

            std::string header;
            int w, h, ts;
            in >> header >> w >> h >> ts;

            if (header != "AXIOM_LEVEL_V1" || ts != TILE_SIZE_INT) {
                std::cerr << "Invalid map format or tile size mismatch.\n";
                return false;
            }

            grid.Resize(w, h);
            grid.Reset();
            physics.Clear();

            std::string tag;
            in >> tag; // STATIC_WALLS
            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w; ++x) {
                    int val;
                    in >> val;
                    if (val == 1) grid.GetCell(x, y)->isStaticWall = true;
                }
            }

            int count;
            in >> tag >> count; // ENTITIES
            for (int i = 0; i < count; ++i) {
                uint32_t id;
                int type, wordId;
                int64_t rawX, rawY;
                in >> id >> type >> wordId >> rawX >> rawY;

                createFn(id, type, wordId, Fix64(rawX, Fix64::RawTag{}), Fix64(rawY, Fix64::RawTag{}));
            }
            return true;
        }
    };
}