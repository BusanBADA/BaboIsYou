#include "TileObject.h"
#include "TileManager.h"

void TileObject::Init(const EngineContext& engineContext)
{
	SetRenderLayer("[Layer]Tile");
	SetMesh(engineContext, "[EngineMesh]default");

	// Default Tile Rules and Sprite
	switch (tileType)
	{
		case TileType::BABO :
			if(rules.empty())
				rules = { true, true, false, false, false, false };
			/*isYou = true;
			isPush = true;
			isStop = false;
			isFixed = false;
			isDefeat = false;
			isWin = false;*/
			SetMaterial(engineContext, "[Material]Babo00");

		break;
		case TileType::FLOOR :
			if (rules.empty())
				rules = { false, false, true, true, false, false };
			/*isYou = false;
			isPush = false;
			isStop = true;
			isFixed = true;
			isDefeat = false;
			isWin = false;*/

			break;
		case TileType::BOX:
			if (rules.empty())
				rules = { false, true, false, false, false, false };
			/*isYou = false;
			isPush = true;
			isStop = false;
			isFixed = false;
			isDefeat = false;
			isWin = false;*/

			break;
		case TileType::DEADZONE:
			if (rules.empty())
				rules = { false, true, false, true, true, false };
			/*isYou = false;
			isPush = true;
			isStop = false;
			isFixed = true;
			isDefeat = true;
			isWin = false;*/

			break;
		case TileType::WALL:
			if (rules.empty())
				rules = { false, false, true, true, false, false };
			/*isYou = false;
			isPush = false;
			isStop = true;
			isFixed = true;
			isDefeat = false;
			isWin = false;*/

			break;
		case TileType::STAR:
			if (rules.empty())
				rules = { false, false, false, true, false, true };
			/*isYou = false;
			isPush = false;
			isStop = false;
			isFixed = true;
			isDefeat = false;
			isWin = true;*/

		break;
	}

	// Collider
	auto collider = std::make_unique<AABBCollider>(this, glm::vec2(1.0, 1.0));
	collider->SetUseTransformScale(true);
	/*collider->SetSize({ 30, 30 });
	collider->SetOffset({ glm::vec2(0, 0) });*/
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
	std::vector<TileObject*> objs = TileManager::instance().GetTileObjects();
	objs.erase(std::remove(objs.begin(), objs.end(), this), objs.end());
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