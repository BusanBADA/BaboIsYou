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

	void SetFactor(float ftr);

	void SetBasePos(glm::vec2 pos);
private:
	enum TileType { BABO, FLOOR, WALL, STAR };
	TileType tileType;
	glm::vec2 basePosition;
	float factor = 0.0f;
	TileObject* next;
};

