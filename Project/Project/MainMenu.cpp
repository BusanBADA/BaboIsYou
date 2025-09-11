#include "MainMenu.h"
#include <iostream>
#include "Button.h"
#include "Debug.h"
#include "Level1.h"
#include "LoadingState.h"
#include "Tutorial.h"

void MainMenu::Load(const EngineContext& engineContext)
{
    SNAKE_LOG("[MainMenu] load called");
}

void MainMenu::Init(const EngineContext& engineContext)
{
    SNAKE_LOG("[MainMenu] init called");

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

        TextureSettings ts = { TextureMinFilter::Nearest,TextureMagFilter::Nearest,TextureWrap::ClampToBorder,TextureWrap::ClampToBorder };
        loading->QueueTexture( engineContext, "[Texture]MainCharacter", "Textures/MainCharacter/player.png", ts);
        loading->QueueTexture(engineContext, "[Texture]Flag", "Textures/flag.png");
        loading->QueueTexture(engineContext, "[Texture]Leaf", "Textures/leaf.png");
        loading->QueueTexture(engineContext, "[Texture]Background00", "Textures/Background/_09_background.png");
        loading->QueueTexture(engineContext, "[Texture]Background01", "Textures/Background/_08_distant_clouds.png");
        loading->QueueTexture(engineContext, "[Texture]Background02", "Textures/Background/_07_clouds.png");
        loading->QueueTexture(engineContext, "[Texture]Background03", "Textures/Background/_06_hill2.png");
        loading->QueueTexture(engineContext, "[Texture]Background04", "Textures/Background/_05_hill1.png");
        loading->QueueTexture(engineContext, "[Texture]Background05", "Textures/Background/_04_bushes.png");
        loading->QueueTexture(engineContext, "[Texture]Background06", "Textures/Background/_03_distant_trees.png");
        loading->QueueTexture(engineContext, "[Texture]Background07", "Textures/Background/_02_trees and bushes.png");
        loading->QueueTexture(engineContext, "[Texture]Background08", "Textures/Background/_01_ground.png");

        loading->QueueShader(engineContext, "[Shader]ColorOnly", { {ShaderStage::Vertex, "Shaders/ColorOnly.vert" },{ShaderStage::Fragment,"Shaders/ColorOnly.frag"} });
        loading->QueueShader(engineContext, "[Shader]Instancing", { {ShaderStage::Vertex, "Shaders/Instancing.vert" },{ShaderStage::Fragment,"Shaders/Instancing.frag"} });

        for (int i = 0; i < 100; i++)
        {
            loading->QueueTexture(engineContext, "test" + std::to_string(i), "Textures/test.jpg",
                TextureSettings{ TextureMinFilter::Linear, TextureMagFilter::Linear, TextureWrap::ClampToEdge, TextureWrap::ClampToEdge, /*generateMipmap*/true });
        }

        loading->QueueShader(engineContext, "S_Sprite",
            {
                { ShaderStage::Vertex,   "Shaders/default.vert" },
                { ShaderStage::Fragment, "Shaders/default.frag" }
            });


        loading->QueueFont(engineContext, "F_UI", "Fonts/font1.ttf", 32);

        loading->QueueSound("BGM_Main", "Sounds/test.mp3", true);

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
