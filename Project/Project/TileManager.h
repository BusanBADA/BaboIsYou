#pragma once
#include "GameState.h"
#include "LoadingState.h"
#include "TileObject.h"
#include "Core/Grid.h"
#include "Core/RuleManager.h"
#include "Core/Fix64.h"
#include "GameTypes.h"

const float TILE_INTERVAL = 30.f;
const glm::vec2 MAX_TILEMAP_SIZE = { 22,24 };

namespace TileState
{
    void AsyncLoad(const EngineContext& engineContext, LoadingState* loading);
}

class TileManager
{
public:
    void Load(const EngineContext& engineContext);

    void Init(const EngineContext& engineContext, ObjectManager& om);

    void LateInit(const EngineContext& engineContext);

    void Update(float dt, const EngineContext& engineContext);

    void LateUpdate(float dt, const EngineContext& engineContext);

    void Draw(const EngineContext& engineContext);

    void Free(const EngineContext& engineContext);

    void Unload(const EngineContext& engineContext);

    // Tile Functions
    TileObject* AddTileObject(const EngineContext& engineContext, const std::string& tag, TileObject::TileType tileType, std::vector<bool> rules, const glm::vec2& defPos = {0,0});

    void TileMove(TileObject& tileObj, ObjectiveType moveType);

    void AddTilePosition(TileObject& tileObj, const glm::vec2& pos);

    void SetTilePosition(const EngineContext& engineContext, TileObject& tileObj, const glm::vec2& cord);

    bool CheckValidPosition(const glm::vec2& cord);

    bool CheckBlankPosition(const glm::vec2& cord);

    bool CheckPushable(TileObject& tileObj, const glm::vec2& dir);

    void PushTiles(TileObject& tileObj, const glm::vec2& dir);

    // Evironment Functions

    void GravityFunc();

    static TileManager& instance() {
        static TileManager instance;
        return instance;
    }

    std::vector<TileObject*> GetTileObjects() { return tileObjects; }

    void SetTileTypeInTilemap(const glm::vec2& cord, TileObject::TileType type);

    TileObject::TileType GetTileTypeInTilemap(const glm::vec2& cord);

    std::vector<int> tilemap = std::vector<int>(MAX_TILEMAP_SIZE.x * MAX_TILEMAP_SIZE.y, 0);


    void SyncToLogicGrid(BABO::World::GridSystem& grid, ObjectManager& objectManager);


    void SaveCurrentLevel(const std::string& path, BABO::World::GridSystem& grid, ObjectManager& objectManager);


    void CreateDefaultLevel(const std::string& path);
    void LoadLevel(const EngineContext& engineContext, const std::string& path, BABO::World::GridSystem& grid);
    std::string GetTagByTileType(TileObject::TileType type);
private:
    ObjectManager* objectManager = nullptr;

    TileManager() = default;

    std::vector<TileObject*> tileObjects;
};

