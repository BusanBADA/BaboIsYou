#pragma once
#include "GameState.h"
#include "BackgroundObject.h"
#include "TextObject.h"
#include "InstancedObject.h"

#include "Core/Grid.h"
#include "Core/RuleManager.h"
#include "Core/Physics.h"

namespace LevelState
{
    void AsyncLoad(const EngineContext& engineContext, LoadingState* loading);
}

class Level : public GameState
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
    BackgroundObject* bgObj00;
    //void CreateDefaultLevel(const std::string& path);
    //void SyncToLogicGrid();
    //void SaveCurrentLevel(); 
    BABO::World::GridSystem* m_gridSystem;
    BABO::Logic::RuleManager m_ruleManager;
    std::string m_levelPath = "level1.babo";

    GameObject* cursor = nullptr;
	class WordManager* wordManager;
    float timer = 0;
};

