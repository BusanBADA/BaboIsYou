#pragma once
#include "TextObject.h"
#include "GameObject.h"
#include <string>

class Button : public TextObject
{
public:
	Button(Font* font, const std::string& text);
	void Init(const EngineContext& engineContext) override;
	void LateInit(const EngineContext& engineContext) override;

	void Update(float dt, const EngineContext& engineContext) override;
	void Draw(const EngineContext& engineContext) override;

	void Free(const EngineContext& engineContext) override;
	void LateFree(const EngineContext& engineContext) override;

	void OnCollision(Object* other) override;

	void SetOnClick(std::function<void()> callback);

	bool IsMouseOver(const EngineContext& engineContext) const;

	void SetBackgroundColor(const  glm::vec4& normal, const  glm::vec4& hover);
protected:
private:
	std::function<void()> onClick;
	GameObject* background;
	glm::vec2 padding = glm::vec2(10.0f, 6.0f);
	glm::vec4 normalColor = glm::vec4(0.2f, 0.2f, 0.2f,1.f);
	glm::vec4 hoverColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	bool hovered = false;
};
