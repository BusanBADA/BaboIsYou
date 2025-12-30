#include "GameObject.h"

class TileObject : public GameObject
{
public:
	void Init(const EngineContext& engineContext) override;
	void LateInit(const EngineContext& engineContext) override;

	void Update(float dt, const EngineContext& engineContext) override;
	void Draw(const EngineContext& engineContext) override;

	void Free(const EngineContext& engineContext) override;
	void LateFree(const EngineContext& engineContext) override;

	void OnCollision(Object* other) override;

	void SetBasePos(glm::vec2 pos);
private:
	enum TileType { BABO, FLOOR, BOX, DEADZONE, WALL, STAR };
	TileType tileType;
	const std::vector<std::string> tileColTags = { "[CollisionTag]Babo", "[CollisionTag]Floor",
	"[CollisionTag]Box", "[CollisionTag]DeadZone", "[CollisionTag]Wall", "[CollisionTag]Star" };
	//Tile Rules
	bool isYou;
	bool isPush;
	bool isStop;
	bool isFixed;
	bool isDefeat;
	bool isWin;
	glm::vec2 basePosition;
	TileObject* next;
};

