#include "TileObject.h"

void TileObject::Init(const EngineContext& engineContext)
{
	SetRenderLayer("[Layer]Tile");
	SetMesh(engineContext, "[EngineMesh]default");

	// Default Tile Rules and Sprite
	switch (tileType)
	{
		case TileType::BABO :
			isYou = true;
			isPush = true;
			isStop = false;
			isFixed = false;
			isDefeat = false;
			isWin = false;
			SetMaterial(engineContext, "[Material]Background08");

		break;
		case TileType::FLOOR :
			isYou = false;
			isPush = false;
			isStop = true;
			isFixed = true;
			isDefeat = false;
			isWin = false;

		break;
		case TileType::BOX :
			isYou = false;
			isPush = true;
			isStop = false;
			isFixed = false;
			isDefeat = false;
			isWin = false;

		break;
		case TileType::DEADZONE :
			isYou = false;
			isPush = true;
			isStop = false;
			isFixed = true;
			isDefeat = true;
			isWin = false;

		break;
		case TileType::WALL :
			isYou = false;
			isPush = false;
			isStop = true;
			isFixed = true;
			isDefeat = false;
			isWin = false;

		break;
		case TileType::STAR :
			isYou = false;
			isPush = false;
			isStop = false;
			isFixed = true;
			isDefeat = false;
			isWin = true;

		break;
	}

	// Collider
	auto collider = std::make_unique<AABBCollider>(this, glm::vec2(1.0, 1.0));
	collider->SetUseTransformScale(false);
	collider->SetSize({ 30, 30 });
	collider->SetOffset({ glm::vec2(0, 0) });
	SetCollider(std::move(collider));
	SetCollision(engineContext.stateManager->GetCurrentState()->GetObjectManager(), tileColTags[tileType], tileColTags );

	GameObject::Init(engineContext);
}

void TileObject::LateInit(const EngineContext& engineContext)
{
	GameObject::LateInit(engineContext);
}

void TileObject::Update(float dt, const EngineContext& engineContext)
{
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

}

void TileObject::SetBasePos(glm::vec2 pos)
{
	basePosition = pos;
}