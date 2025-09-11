#include "MainMenu.h"
#include <iostream>
#include "Debug.h"
#include "LoadingState.h"
#include "Tutorial.h"

void MainMenu::Load(const EngineContext& engineContext)
{
    SNAKE_LOG("[MainMenu] load called");
}

void MainMenu::Init(const EngineContext& engineContext)
{
    SNAKE_LOG("[MainMenu] init called");
    mainText = static_cast<TextObject*>( objectManager.AddObject(std::make_unique<TextObject>(engineContext.renderManager->GetFontByTag("[Font]default"), "MainMenu", TextAlignH::Center, TextAlignV::Middle)));

}

void MainMenu::LateInit(const EngineContext& engineContext)
{
}

void MainMenu::Update(float dt, const EngineContext& engineContext)
{
    if (engineContext.inputManager->IsKeyReleased(KEY_N))
    {
        auto nextFactory = []() -> std::unique_ptr<GameState>
            {
                return std::make_unique<Tutorial>();
            };

        auto loading = std::make_unique<LoadingState>(nextFactory);

        TutorialState::AsyncLoad(engineContext, loading.get());

        engineContext.stateManager->ChangeState(std::move(loading));
    }
    objectManager.UpdateAll(dt, engineContext);

}

void MainMenu::LateUpdate(float dt, const EngineContext& engineContext)
{
}

void MainMenu::Draw(const EngineContext& engineContext)
{
    objectManager.DrawAll(engineContext);
}


void MainMenu::Free(const EngineContext& engineContext)
{
    SNAKE_LOG("[MainMenu] free called");
}

void MainMenu::Unload(const EngineContext& engineContext)
{
    SNAKE_LOG("[MainMenu] unload called");
}
