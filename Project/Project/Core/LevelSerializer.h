#pragma once
#include <fstream>
#include <vector>
#include <functional>
#include "Grid.h"
#include "Physics.h"

namespace BABO::IO {
    using namespace BABO::World;
    using namespace BABO::Physics;
    using namespace BABO::Math;
    using namespace BABO::Core;

    struct EntityData { uint32_t id; int type; int64_t x, y; };

    class LevelSerializer {
    public:

        static void Save(const std::string& file, const World::GridSystem& grid, const std::vector<EntityData>& entities, const std::vector<std::string>& tags) {
            std::ofstream ofs(file);
            if (!ofs.is_open()) return;


            ofs << "BABO " << 30 << " " << grid.GetWidth() << " " << grid.GetHeight() << "\n";


            for (int y = 0; y < grid.GetHeight(); ++y) {
                for (int x = 0; x < grid.GetWidth(); ++x) {
                    ofs << (grid.GetCell(x, y)->isStaticWall ? 1 : 0) << " ";
                }
                ofs << "\n";
            }


            ofs << entities.size() << "\n";
            for (size_t i = 0; i < entities.size(); ++i) {
                ofs << entities[i].id << " "
                    << entities[i].type << " "
                    << entities[i].x << " "
                    << entities[i].y << " "
                    << tags[i] << "\n";
            }
        }


        static bool Load(const std::string& file, World::GridSystem& grid,
            std::function<void(uint32_t, int, int64_t, int64_t, std::string)> spawner)
        {
            std::ifstream in(file);
            if (!in.is_open()) return false;

            std::string headerTag; int ts, w, h;
            in >> headerTag >> ts >> w >> h;

            if (headerTag != "BABO" || ts != 30) return false;

            grid.Resize(w, h);
            grid.Reset();

            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w; ++x) {
                    int val; in >> val;
                    if (val) grid.GetCell(x, y)->isStaticWall = true;
                }
            }

            int count;
            in >> count;
            for (int i = 0; i < count; ++i) {
                uint32_t id; int type; int64_t x, y;
                std::string entTag;

                in >> id >> type >> x >> y >> entTag;


                spawner(id, type, x, y, entTag);
            }
            return true;
        }
    };
}