#pragma once
#include "GameState.h"
#include "LoadingState.h"
#include "TileObject.h"
#include "Core/Grid.h"
#include "Core/RuleManager.h"
#include "Core/Fix64.h"
namespace TileState
{
    void AsyncLoad(const EngineContext& engineContext, LoadingState* loading);
}

class TileManager
{
public:
    void Load(const EngineContext& engineContext);

    void Init(const EngineContext& engineContext);

    void LateInit(const EngineContext& engineContext);

    void Update(float dt, const EngineContext& engineContext);

    void LateUpdate(float dt, const EngineContext& engineContext);

    void Draw(const EngineContext& engineContext);

    void Free(const EngineContext& engineContext);

    void Unload(const EngineContext& engineContext);


    void SyncToLogicGrid(BABO::World::GridSystem& grid, ObjectManager& objectManager);


    void SaveCurrentLevel(const std::string& path, BABO::World::GridSystem& grid, ObjectManager& objectManager);


    void CreateDefaultLevel(const std::string& path);
private:

    std::vector<TileObject*> tileObjects;
};

