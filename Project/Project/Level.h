#pragma once
#include"GameState.h"
#include "BackgroundObject.h"
#include "FlagObject.h"
#include "TextObject.h"
#include "Player.h"
#include "InstancedObject.h"
#include "TileObject.h"

namespace LevelState
{
    void AsyncLoad(const EngineContext& engineContext, LoadingState* loading);
}

class Level :public GameState
{
public:
    void Load(const EngineContext& engineContext) override;

    void Init(const EngineContext& engineContext) override;

    void LateInit(const EngineContext& engineContext) override;

    void Update(float dt, const EngineContext& engineContext) override;

    void LateUpdate(float dt, const EngineContext& engineContext) override;

    void Draw(const EngineContext& engineContext) override;

    void Free(const EngineContext& engineContext) override;

    void Unload(const EngineContext& engineContext) override;

private:
    Player* player;
    BackgroundObject* bgObj00, * bgObj01, * bgObj02, * bgObj03, * bgObj04, * bgObj05, * bgObj06, * bgObj07, * bgObj08;
    BackgroundObject* bgObj00Sub, * bgObj01Sub, * bgObj02Sub, * bgObj03Sub, * bgObj04Sub, * bgObj05Sub, * bgObj06Sub, * bgObj07Sub, * bgObj08Sub;
    FlagObject* flag00, * flag01, * flag02, * flag03, * flag04;
    TileObject* frObj00;
    GameObject* cursor;
    float timer = 0;
};

