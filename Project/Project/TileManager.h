#pragma once
#include "GameState.h"
#include "LoadingState.h"
#include "TileObject.h"
#include "GameTypes.h"

const float TILE_INTERVAL = 30.f;

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
    TileObject* AddTileObject(const EngineContext& engineContext, const std::string& tag, TileObject::TileType tileType, std::vector<bool> rules);

    void TileMove(TileObject& tileObj, ObjectiveType moveType);

    void AddTilePosition(TileObject& tileObj, const glm::vec2& pos);

    void SetTilePosition(const EngineContext& engineContext, TileObject& tileObj, const glm::vec2& cord);

    static TileManager& instance() {
        static TileManager instance;
        return instance;
    }

    std::vector<TileObject*> GetTileObjects() { return tileObjects; }
private:
    ObjectManager* objectManager = nullptr;

    TileManager() = default;

    std::vector<TileObject*> tileObjects;
};

