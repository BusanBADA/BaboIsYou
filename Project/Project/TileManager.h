#pragma once
#include "GameState.h"
#include "LoadingState.h"
#include "TileObject.h"

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

private:

    std::vector<TileObject*> tileObjects;
};

