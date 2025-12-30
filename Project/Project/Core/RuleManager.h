#pragma once
#include "Grid.h"

namespace BABO::Logic {
    struct Rule { WordType subject; WordType property; };

    class RuleManager {
    public:
        std::vector<Rule> activeRules;

        void Parse(const BABO::World::GridSystem& grid) {
            activeRules.clear();
            for (int y = 0; y < grid.GetHeight(); ++y) {
                for (int x = 0; x < grid.GetWidth(); ++x) {
                    CheckAndAdd(grid, x, y, 1, 0); 
                    CheckAndAdd(grid, x, y, 0, 1); 
                }
            }
        }
    private:
        void CheckAndAdd(const BABO::World::GridSystem& grid, int x, int y, int dx, int dy) {
            auto w1 = GetWord(grid, x, y);
            auto w2 = GetWord(grid, x + dx, y + dy);
            auto w3 = GetWord(grid, x + 2 * dx, y + 2 * dy);
            if (IsNoun(w1) && w2 == WordType::IS && IsProperty(w3))
                activeRules.push_back({ w1, w3 });
        }
        WordType GetWord(const BABO::World::GridSystem& grid, int x, int y) {
            auto* c = grid.GetCell(x, y); return c ? c->word : WordType::None;
        }
        bool IsNoun(WordType w) { return w >= WordType::PLAYER && w <= WordType::ROCK; }
        bool IsProperty(WordType w) { return w >= WordType::YOU; }
    };
}