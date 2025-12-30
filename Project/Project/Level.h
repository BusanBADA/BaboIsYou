#pragma once
#include "GameState.h"
#include "BackgroundObject.h"
#include "FlagObject.h"
#include "TextObject.h"
#include "Player.h"
#include "InstancedObject.h"
#include "TileObject.h"

// BABO 핵심 시스템 포함
#include "Core/Grid.h"
#include "Core/RuleManager.h"
#include "Core/Physics.h"

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
    void CreateDefaultLevel(const std::string& path);
    void SyncToLogicGrid();
    void SaveCurrentLevel(); // 라벨 포함 저장 로직

    // 핵심 시스템 멤버
    BABO::World::GridSystem m_gridSystem;
    BABO::Logic::RuleManager m_ruleManager;
    std::string m_levelPath = "level1.babo";

    // 객체 포인터
    Player* player = nullptr;
    GameObject* cursor = nullptr;
    TileObject* frObj00 = nullptr;

    // 배경 및 플래그 객체 (Init에서 초기화)
    BackgroundObject* bgObj00, * bgObj01, * bgObj02, * bgObj03, * bgObj04, * bgObj05, * bgObj06, * bgObj07, * bgObj08;
    BackgroundObject* bgObj00Sub, * bgObj01Sub, * bgObj02Sub, * bgObj03Sub, * bgObj04Sub, * bgObj05Sub, * bgObj06Sub, * bgObj07Sub, * bgObj08Sub;
    FlagObject* flag00, * flag01, * flag02, * flag03, * flag04;

    float timer = 0.0f;
};