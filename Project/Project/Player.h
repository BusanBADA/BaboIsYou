#pragma once
#include "ObjectManager.h"
#include "Engine.h"

class Player : public GameObject
{
public:
    void Init(const EngineContext& engineContext) override;
    void LateInit(const EngineContext& engineContext) override;
    void Update(float dt, const EngineContext& engineContext) override;
    void Draw(const EngineContext& engineContext) override;
    void Free(const EngineContext& engineContext) override;
    void LateFree(const EngineContext& engineContext) override;
    void OnCollision(Object* other) override;
    bool CheckIdle();
    enum PlayerMoveType { LEFT, RIGHT, UP };
    void PlayerMove(PlayerMoveType moveType, const EngineContext& engineContext);
private:
    bool checkIdle = true;
    bool checkIdle_prevFrame = false;
};

