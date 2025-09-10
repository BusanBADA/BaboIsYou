#include <iostream>

#include "Debug.h"
#include "MainMenu.h"
#include "Engine.h"
#include "Tutorial.h"
#ifdef _DEBUG
//#include<vld.h>//TODO: remove this and directories before release (VC++ Directories -> Include Directories & Library Directories)
#endif
int main(int argc, char* argv[])
{
    SNAKE_Engine snakeEngine;
    DebugLogger::SetLogLevel(LogLevel::Warning);
    float multiplier = 1.5f;
    int width = 800 * multiplier;
    int height = 480 * multiplier;

    try
    {
        if (argc == 3)
        {
            width = std::stoi(argv[1]);
            height = std::stoi(argv[2]);
        }
        else if (argc != 1)
        {
            SNAKE_ERR("Usage: ./MyGame [width height]");
            return -1;
        }
    }
    catch (const std::exception& e)
    {
        SNAKE_ERR("Invalid arguments. Width and height must be integers.");
        return -1;
    }

    if (!snakeEngine.Init(width, height))
    {
        SNAKE_ERR("Engine initialization failed.");
        return -1;
    }
    snakeEngine.RenderDebugDraws(false);
    snakeEngine.GetEngineContext().windowManager->RestrictResizing(true);


    snakeEngine.GetEngineContext().renderManager->RegisterMesh(
        "[Mesh]octagon",
        std::vector<Vertex>{
            {{  0.5f, 0.0f, 0.f }, { 1.0f,       0.5f }}, // 0 (0°)
            { {  0.353553f,     0.353553f,     0.f }, { 0.853553f,  0.853553f  } }, // 1 (45°)
            { {  0.0f,          0.5f,          0.f }, { 0.5f,       1.0f       } }, // 2 (90°)
            { { -0.353553f,     0.353553f,     0.f }, { 0.146447f,  0.853553f  } }, // 3 (135°)
            { { -0.5f,          0.0f,          0.f }, { 0.0f,       0.5f       } }, // 4 (180°)
            { { -0.353553f,    -0.353553f,     0.f }, { 0.146447f,  0.146447f  } }, // 5 (225°)
            { {  0.0f,         -0.5f,          0.f }, { 0.5f,       0.0f       } }, // 6 (270°)
            { {  0.353553f,    -0.353553f,     0.f }, { 0.853553f,  0.146447f  } }, // 7 (315°)
            { {  0.0f,          0.0f,          0.f }, { 0.5f,       0.5f       } }, // 8 (center)
    },
        std::vector<unsigned int>{
        8, 0, 1, 8, 1, 2, 8, 2, 3, 8, 3, 4,
            8, 4, 5, 8, 5, 6, 8, 6, 7, 8, 7, 0
    }
    );

    snakeEngine.GetEngineContext().renderManager->RegisterShader("s_instancing", { {ShaderStage::Vertex,"Shaders/instancing.vert"},{ShaderStage::Fragment,"Shaders/instancing.frag"} });
    snakeEngine.GetEngineContext().renderManager->RegisterShader("[Shader]Animation", { {ShaderStage::Vertex,"Shaders/Animation.vert"},{ShaderStage::Fragment,"Shaders/Animation.frag"} });
    snakeEngine.GetEngineContext().renderManager->RegisterMaterial("[Material]Animation", "[Shader]Animation", { });

    //snakeEngine.GetEngineContext().renderManager->RegisterMaterial("m_instancing", "s_instancing", { std::pair<std::string, std::string>("u_Texture","default") });
    //snakeEngine.GetEngineContext().renderManager->RegisterMaterial("m_instancing1", "s_instancing", { std::pair<std::string, std::string>("u_Texture","default") });
    //snakeEngine.GetEngineContext().renderManager->RegisterMaterial("m_blueMButton", "s_default1", { std::pair<std::string, std::string>("u_Texture","blueMButton") });


    snakeEngine.GetEngineContext().renderManager->RegisterRenderLayer("[Layer]Background", 0);
    snakeEngine.GetEngineContext().renderManager->RegisterRenderLayer("[Layer]Flag", 9);
    snakeEngine.GetEngineContext().renderManager->RegisterRenderLayer("[Layer]Player", 10);
    snakeEngine.GetEngineContext().renderManager->RegisterRenderLayer("[Layer]UI", 11);
    snakeEngine.GetEngineContext().renderManager->RegisterRenderLayer("[Layer]UIText", 12);

    snakeEngine.GetEngineContext().renderManager->RegisterFont("[Font]default", "Fonts/NotoSans-VariableFont_wdth,wght.ttf", 50);
  
    snakeEngine.GetEngineContext().windowManager->SetBackgroundColor({ 0.2,0.2,0.4,1 });
    snakeEngine.GetEngineContext().stateManager->ChangeState(std::make_unique<MainMenu>());

    snakeEngine.Run();

    return 0;
}