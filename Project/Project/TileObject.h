#pragma once
#include "GameObject.h"
#include "GameState.h"

class TileObject : public GameObject
{
public:
	enum TileType { BLANK, BABO, FLOOR, BOX, DEADZONE, WALL, STAR };
	enum RuleType { IS_YOU, IS_PUSH, IS_STOP, IS_FIXED, IS_DEFEAT, IS_WIN };

	void Init(const EngineContext& engineContext) override;
	void LateInit(const EngineContext& engineContext) override;

	void Update(float dt, const EngineContext& engineContext) override;
	void Draw(const EngineContext& engineContext) override;

	void Free(const EngineContext& engineContext) override;
	void LateFree(const EngineContext& engineContext) override;

	void OnCollision(Object* other) override;

	TileObject::TileType GetTileType() { return tileType; }
	void SetTileType(TileObject::TileType type) { tileType = type; }

	void SetTileRules(std::vector<bool> _rules)	{ rules = _rules; }
	void SetTileRule(RuleType ruletype, bool value) { rules[ruletype] = value; }
	std::vector<bool> GetTileRules() { return rules; }
	bool GetTileRule(RuleType ruletype) { return rules[ruletype]; }

	void SetCellPos(const glm::vec2& pos) { cellPosition = pos; }

	const glm::vec2& GetCellPos() { return cellPosition; }

	void SetBasePos(glm::vec2 pos);
private:
	TileType tileType;
	const std::vector<std::string> tileColTags = { "[CollisionTag]Blank", "[CollisionTag]Babo", "[CollisionTag]Floor",
	"[CollisionTag]Box", "[CollisionTag]DeadZone", "[CollisionTag]Wall", "[CollisionTag]Star" };
	//Tile Rules
	std::vector<bool> rules;
	glm::vec2 cellPosition;
	glm::vec2 basePosition;
};

