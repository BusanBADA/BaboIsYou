#include "TileObject.h"
#include "EngineContext.h"
#include "GameState.h"

void TileObject::Init(const EngineContext& engineContext)
{
	SetMesh(engineContext, "[EngineMesh]default");

	GameObject::Init(engineContext);
}

void TileObject::LateInit(const EngineContext& engineContext)
{
	GameObject::LateInit(engineContext);
}

void TileObject::Update(float dt, const EngineContext& engineContext)
{
	Camera2D* cam = engineContext.stateManager->GetCurrentState()->GetActiveCamera();
	transform2D.SetPosition(basePosition + cam->GetPosition() * factor);


	GameObject::Update(dt, engineContext);
}

void TileObject::Draw(const EngineContext& engineContext)
{
	GameObject::Draw(engineContext);
}

void TileObject::Free(const EngineContext& engineContext)
{
	GameObject::Free(engineContext);
}

void TileObject::LateFree(const EngineContext& engineContext)
{
	GameObject::LateFree(engineContext);
}

void TileObject::OnCollision(Object* other)
{
	GameObject::OnCollision(other);
}

void TileObject::SetFactor(float ftr)
{
	factor = ftr;
}

void TileObject::SetBasePos(glm::vec2 pos)
{
	basePosition = pos;
}