#include "Button.h"
#include "EngineContext.h"
#include "GameState.h"
Button::Button(Font* font, const std::string& text) : TextObject(font, text, TextAlignH::Center, TextAlignV::Middle)
{
	
}
void Button::Init(const EngineContext& engineContext)
{
	TextObject::Init(engineContext);

	RenderManager* rm = engineContext.renderManager;
	if (rm)
	{
		if (rm->GetMaterialByTag("[Material]Button"))
		{
			rm->RegisterTexture("[Texture]Button", "Textures/button.png",TextureSettings{ TextureMinFilter::Linear, TextureMagFilter::Linear, TextureWrap::ClampToEdge, TextureWrap::ClampToEdge, true });
			rm->RegisterMaterial("[Material]Button", "[EngineShader]default_texture", { {"u_Texture","[Texture]Button"} });
		}
		SetRenderLayer("[Layer]UIText");
	}
	

	std::unique_ptr<Object> bgObj = std::make_unique<GameObject>(); 
	SetIgnoreCamera(true, engineContext.stateManager->GetCurrentState()->GetActiveCamera());
	
	background = static_cast<GameObject*>(bgObj.get());
	background->SetMesh(engineContext, "[EngineMesh]default");
	background->SetMaterial(engineContext, "[Material]Button");
	background->SetRenderLayer("[Layer]UI");
	background->GetTransform2D().SetDepth(GetTransform2D().GetDepth() + 0.1f);
	background->SetIgnoreCamera(true, engineContext.stateManager->GetCurrentState()->GetActiveCamera());
	engineContext.stateManager->GetCurrentState()->GetObjectManager().AddObject(std::move(bgObj));

}

void Button::LateInit(const EngineContext& engineContext)
{
	TextObject::LateInit(engineContext);
}

void Button::Update(float dt, const EngineContext& engineContext)
{
	hovered = IsMouseOver(engineContext);
	glm::vec2 size = GetWorldScale() + padding * 2.0f;

	background->GetTransform2D().SetPosition(GetTransform2D().GetPosition());
	background->GetTransform2D().SetScale(size);

	if (hovered)
	{
		background->SetColor(hoverColor);
	}
	else
	{
		background->SetColor(normalColor);
	}
	if (hovered)
	{
		if (engineContext.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (onClick)
				onClick();
		}
	}

	TextObject::Update(dt, engineContext);
}

void Button::Draw(const EngineContext& engineContext)
{
	TextObject::Draw(engineContext);
}

void Button::Free(const EngineContext& engineContext)
{
	TextObject::Free(engineContext);
}

void Button::LateFree(const EngineContext& engineContext)
{
	TextObject::LateFree(engineContext);
}

void Button::OnCollision(Object* other)
{
	TextObject::OnCollision(other);
}

void Button::SetOnClick(std::function<void()> callback)
{
	onClick = callback;
}

bool Button::IsMouseOver(const EngineContext& engineContext) const
{
	glm::vec2 mousePos = engineContext.inputManager->GetMousePos();
	glm::vec2 screenSize;
	screenSize.x = engineContext.windowManager->GetWidth();
	screenSize.y = engineContext.windowManager->GetHeight();

    mousePos.x -= screenSize.x * 0.5f;
    mousePos.y = screenSize.y * 0.5f - mousePos.y;

    glm::vec2 pos = GetWorldPosition();
    glm::vec2 size = GetWorldScale() + padding * 2.0f;
    glm::vec2 half = size * 0.5f;

    return mousePos.x >= pos.x - half.x &&
           mousePos.x <= pos.x + half.x &&
           mousePos.y >= pos.y - half.y &&
           mousePos.y <= pos.y + half.y;
}

void Button::SetBackgroundColor(const glm::vec4& normal, const glm::vec4& hover)
{
	normalColor = normal;
	hoverColor = hover;
}
