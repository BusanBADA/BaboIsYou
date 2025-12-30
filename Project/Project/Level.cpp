#include "Level.h"
#include "MainMenu.h"

namespace LevelState
{
    void AsyncLoad(const EngineContext& engineContext, LoadingState* loading)
    {
        TextureSettings ts = { TextureMinFilter::Nearest,TextureMagFilter::Nearest,TextureWrap::ClampToBorder,TextureWrap::ClampToBorder };

        // BG
        loading->QueueTexture(engineContext, "[Texture]Flag", "Textures/flag.png");
        loading->QueueTexture(engineContext, "[Texture]Background00", "Textures/Background/_09_background.png");
        loading->QueueTexture(engineContext, "[Texture]Background01", "Textures/Background/_08_distant_clouds.png");
        loading->QueueTexture(engineContext, "[Texture]Background02", "Textures/Background/_07_clouds.png");
        loading->QueueTexture(engineContext, "[Texture]Background03", "Textures/Background/_06_hill2.png");
        loading->QueueTexture(engineContext, "[Texture]Background04", "Textures/Background/_05_hill1.png");
        loading->QueueTexture(engineContext, "[Texture]Background05", "Textures/Background/_04_bushes.png");
        loading->QueueTexture(engineContext, "[Texture]Background06", "Textures/Background/_03_distant_trees.png");
        loading->QueueTexture(engineContext, "[Texture]Background07", "Textures/Background/_02_trees and bushes.png");
        loading->QueueTexture(engineContext, "[Texture]Background08", "Textures/Background/_01_ground.png");

        // Tiles
        TileState::AsyncLoad(engineContext, loading);

        // Shader
        loading->QueueShader(engineContext, "[Shader]ColorOnly", { {ShaderStage::Vertex, "Shaders/ColorOnly.vert" },{ShaderStage::Fragment,"Shaders/ColorOnly.frag"} });
        loading->QueueShader(engineContext, "[Shader]Instancing", { {ShaderStage::Vertex, "Shaders/Instancing.vert" },{ShaderStage::Fragment,"Shaders/Instancing.frag"} });

        for (int i = 0; i < 10; i++)
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

    }
}

void Level::Load(const EngineContext& engineContext)
{
    JIN_LOG("[Level] load called");
    RenderManager* rm = engineContext.renderManager;

    rm->RegisterSpriteSheet("[SpriteSheet]Flag", "[Texture]Flag", 60, 60);

    rm->RegisterMaterial("[Material]default", "[EngineShader]default_texture", { {"u_Texture","[EngineTexture]RenderTexture"} });

    rm->RegisterMaterial("[Material]ColorOnly", "[Shader]ColorOnly", {});

    rm->RegisterMaterial("[Material]Instancing", "[Shader]Instancing", { {"u_Texture","[Texture]Leaf"} });

    // BG
    rm->RegisterMaterial("[Material]Background00", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background00"} });
    rm->RegisterMaterial("[Material]Background01", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background01"} });
    rm->RegisterMaterial("[Material]Background02", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background02"} });
    rm->RegisterMaterial("[Material]Background03", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background03"} });
    rm->RegisterMaterial("[Material]Background04", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background04"} });
    rm->RegisterMaterial("[Material]Background05", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background05"} });
    rm->RegisterMaterial("[Material]Background06", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background06"} });
    rm->RegisterMaterial("[Material]Background07", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background07"} });
    rm->RegisterMaterial("[Material]Background08", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background08"} });

    // Tiles
    tileManager.Load(engineContext);
}

void Level::Init(const EngineContext& engineContext)
{
    //Background Obj
    bgObj00 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg00"));
    bgObj00->SetMaterial(engineContext, "[Material]Background00");
    bgObj00->SetRenderLayer("[Layer]Background");
    bgObj00->SetFactor(1.0f);

    bgObj01 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg01"));
    bgObj01->SetMaterial(engineContext, "[Material]Background01");
    bgObj01->SetRenderLayer("[Layer]Background");
    bgObj01->SetFactor(0.9f);

    bgObj02 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg02"));
    bgObj02->SetMaterial(engineContext, "[Material]Background02");
    bgObj02->SetRenderLayer("[Layer]Background");
    bgObj02->SetFactor(0.8f);

    bgObj03 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg03"));
    bgObj03->SetMaterial(engineContext, "[Material]Background03");
    bgObj03->SetRenderLayer("[Layer]Background");
    bgObj03->SetFactor(0.7f);

    bgObj04 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg04"));
    bgObj04->SetMaterial(engineContext, "[Material]Background04");
    bgObj04->SetRenderLayer("[Layer]Background");
    bgObj04->SetFactor(0.5f);

    bgObj05 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg05"));
    bgObj05->SetMaterial(engineContext, "[Material]Background05");
    bgObj05->SetRenderLayer("[Layer]Background");
    bgObj05->SetFactor(0.4f);

    bgObj06 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg06"));
    bgObj06->SetMaterial(engineContext, "[Material]Background06");
    bgObj06->SetRenderLayer("[Layer]Background");
    bgObj06->SetFactor(0.3f);

    bgObj07 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg07"));
    bgObj07->SetMaterial(engineContext, "[Material]Background07");
    bgObj07->SetRenderLayer("[Layer]Background");
    bgObj07->SetFactor(0.2f);

    bgObj08 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg08"));
    bgObj08->SetMaterial(engineContext, "[Material]Background08");
    bgObj08->SetRenderLayer("[Layer]Background");
    bgObj08->SetFactor(0.0);

    bgObj00Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg00"));
    bgObj00Sub->SetMaterial(engineContext, "[Material]Background00");
    bgObj00Sub->SetRenderLayer("[Layer]Background");
    bgObj00Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj00Sub->SetFactor(1.0f);

    bgObj01Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg01"));
    bgObj01Sub->SetMaterial(engineContext, "[Material]Background01");
    bgObj01Sub->SetRenderLayer("[Layer]Background");
    bgObj01Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj01Sub->SetFactor(0.9f);

    bgObj02Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg02"));
    bgObj02Sub->SetMaterial(engineContext, "[Material]Background02");
    bgObj02Sub->SetRenderLayer("[Layer]Background");
    bgObj02Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj02Sub->SetFactor(0.8f);

    bgObj03Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg03"));
    bgObj03Sub->SetMaterial(engineContext, "[Material]Background03");
    bgObj03Sub->SetRenderLayer("[Layer]Background");
    bgObj03Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj03Sub->SetFactor(0.7f);

    bgObj04Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg04"));
    bgObj04Sub->SetMaterial(engineContext, "[Material]Background04");
    bgObj04Sub->SetRenderLayer("[Layer]Background");
    bgObj04Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj04Sub->SetFactor(0.5f);
    bgObj04Sub->SetFlipUV_X(true);

    bgObj05Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg05"));
    bgObj05Sub->SetMaterial(engineContext, "[Material]Background05");
    bgObj05Sub->SetRenderLayer("[Layer]Background");
    bgObj05Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj05Sub->SetFactor(0.4f);

    bgObj06Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg06"));
    bgObj06Sub->SetMaterial(engineContext, "[Material]Background06");
    bgObj06Sub->SetRenderLayer("[Layer]Background");
    bgObj06Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj06Sub->SetFactor(0.3f);

    bgObj07Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg07"));
    bgObj07Sub->SetMaterial(engineContext, "[Material]Background07");
    bgObj07Sub->SetRenderLayer("[Layer]Background");
    bgObj07Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj07Sub->SetFactor(0.2f);

    bgObj08Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg08"));
    bgObj08Sub->SetMaterial(engineContext, "[Material]Background08");
    bgObj08Sub->SetRenderLayer("[Layer]Background");
    bgObj08Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj08Sub->SetFactor(0.0f);

    bgObj00->SetNextBackground(bgObj00Sub);
    bgObj01->SetNextBackground(bgObj01Sub);
    bgObj02->SetNextBackground(bgObj02Sub);
    bgObj03->SetNextBackground(bgObj03Sub);
    bgObj04->SetNextBackground(bgObj04Sub);
    bgObj05->SetNextBackground(bgObj05Sub);
    bgObj06->SetNextBackground(bgObj06Sub);
    bgObj07->SetNextBackground(bgObj07Sub);
    bgObj08->SetNextBackground(bgObj08Sub);

    bgObj00Sub->SetNextBackground(bgObj00);
    bgObj01Sub->SetNextBackground(bgObj01);
    bgObj02Sub->SetNextBackground(bgObj02);
    bgObj03Sub->SetNextBackground(bgObj03);
    bgObj04Sub->SetNextBackground(bgObj04);
    bgObj05Sub->SetNextBackground(bgObj05);
    bgObj06Sub->SetNextBackground(bgObj06);
    bgObj07Sub->SetNextBackground(bgObj07);
    bgObj08Sub->SetNextBackground(bgObj08);

    //Flag Obj
    flag00 = static_cast<FlagObject*>(objectManager.AddObject(std::make_unique<FlagObject>(), "[Object]flag"));
    flag00->SetRenderLayer("[Layer]Flag");
    flag00->GetTransform2D().SetPosition(glm::vec2(-600, -170));
    flag00->GetTransform2D().SetScale(glm::vec2(100.f));
    flag00->SetGuide("These leaves are rendered using instancing.\nCheck InstancedObject.cpp for more Info.");

    flag01 = static_cast<FlagObject*>(objectManager.AddObject(std::make_unique<FlagObject>(), "[Object]flag"));
    flag01->SetRenderLayer("[Layer]Flag");
    flag01->GetTransform2D().SetPosition(glm::vec2(200, -170));
    flag01->GetTransform2D().SetScale(glm::vec2(100.f));
    flag01->SetGuide("Move Left & Right with A,D key.\nInput can be handled via Inputmanager\nand can be accessed from engineContext");

    flag02 = static_cast<FlagObject*>(objectManager.AddObject(std::make_unique<FlagObject>(), "[Object]flag"));
    flag02->SetRenderLayer("[Layer]Flag");
    flag02->GetTransform2D().SetPosition(glm::vec2(800, -170));
    flag02->GetTransform2D().SetScale(glm::vec2(100.f));
    flag02->SetGuide("Objects are managed via ObjectManager.\n Each State has its own ObjectManager.");

    flag03 = static_cast<FlagObject*>(objectManager.AddObject(std::make_unique<FlagObject>(), "[Object]flag"));
    flag03->SetRenderLayer("[Layer]Flag");
    flag03->GetTransform2D().SetPosition(glm::vec2(1400, -170));
    flag03->GetTransform2D().SetScale(glm::vec2(100.f));
    flag03->SetGuide("Engine supports async loading.\nUse loading state for large files(texture, audio..etc).");

    flag04 = static_cast<FlagObject*>(objectManager.AddObject(std::make_unique<FlagObject>(), "[Object]flag"));
    flag04->SetRenderLayer("[Layer]Flag");
    flag04->GetTransform2D().SetPosition(glm::vec2(2000, -170));
    flag04->GetTransform2D().SetScale(glm::vec2(100.f));
    flag04->SetGuide("Objects are rendered to the \"[EngineTexture]RenderTexture\". \nUse this texture to do postprocessing with compute shader.\nPress \'c\' to enable glitch.\nPress \'v\' to disable glitch.");

    //BG Depth
    bgObj00->GetTransform2D().SetDepth(0);
    bgObj01->GetTransform2D().SetDepth(10);
    bgObj02->GetTransform2D().SetDepth(20);
    bgObj03->GetTransform2D().SetDepth(30);
    bgObj04->GetTransform2D().SetDepth(40);
    bgObj05->GetTransform2D().SetDepth(50);
    bgObj06->GetTransform2D().SetDepth(60);
    bgObj07->GetTransform2D().SetDepth(70);
    bgObj08->GetTransform2D().SetDepth(80);
    bgObj00Sub->GetTransform2D().SetDepth(0);
    bgObj01Sub->GetTransform2D().SetDepth(10);
    bgObj02Sub->GetTransform2D().SetDepth(20);
    bgObj03Sub->GetTransform2D().SetDepth(30);
    bgObj04Sub->GetTransform2D().SetDepth(40);
    bgObj05Sub->GetTransform2D().SetDepth(50);
    bgObj06Sub->GetTransform2D().SetDepth(60);
    bgObj07Sub->GetTransform2D().SetDepth(70);
    bgObj08Sub->GetTransform2D().SetDepth(80);

    //Cursor
    cursor = static_cast<GameObject*>(objectManager.AddObject(std::make_unique<GameObject>(), "[Object]cursor"));
    cursor->SetMaterial(engineContext, "[Material]cursor");
    cursor->SetMesh(engineContext, "[EngineMesh]default");
    cursor->GetTransform2D().SetScale({ 30,30 });
    cursor->SetRenderLayer("[Layer]Cursor");
    cursor->SetIgnoreCamera(true, cameraManager.GetActiveCamera());

    //BGM
    engineContext.soundManager->Play("BGM_Main", 1, 0);

    //Resolution
    int w = engineContext.windowManager->GetWidth();
    int h = engineContext.windowManager->GetHeight();
    int newH = w * 720.f / 1280.f;

    //BG Scale
    bgObj00->GetTransform2D().SetScale({ w, newH });
    bgObj01->GetTransform2D().SetScale({ w, newH });
    bgObj02->GetTransform2D().SetScale({ w, newH });
    bgObj03->GetTransform2D().SetScale({ w, newH });
    bgObj04->GetTransform2D().SetScale({ w, newH });
    bgObj05->GetTransform2D().SetScale({ w, newH });
    bgObj06->GetTransform2D().SetScale({ w, newH });
    bgObj07->GetTransform2D().SetScale({ w, newH });
    bgObj08->GetTransform2D().SetScale({ w, newH });
    bgObj00Sub->GetTransform2D().SetScale({ w, w * 720.f / 1280.f });
    bgObj01Sub->GetTransform2D().SetScale({ w, newH });
    bgObj02Sub->GetTransform2D().SetScale({ w, newH });
    bgObj03Sub->GetTransform2D().SetScale({ w, newH });
    bgObj04Sub->GetTransform2D().SetScale({ w, newH });
    bgObj05Sub->GetTransform2D().SetScale({ w, newH });
    bgObj06Sub->GetTransform2D().SetScale({ w, newH });
    bgObj07Sub->GetTransform2D().SetScale({ w, newH });
    bgObj08Sub->GetTransform2D().SetScale({ w, newH });

    // Tiles
    tileManager.Init(engineContext);
}

void Level::LateInit(const EngineContext& engineContext)
{
    // Tiles
    tileManager.LateInit(engineContext);
}

void Level::Update(float dt, const EngineContext& engineContext)
{
    //Cursor
    cursor->GetTransform2D().SetPosition(glm::vec2(engineContext.inputManager->GetMousePos().x - engineContext.windowManager->GetWidth() / 2.f, engineContext.windowManager->GetHeight() / 2.f - engineContext.inputManager->GetMousePos().y) + glm::vec2(11, -11));
    if (engineContext.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || engineContext.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) || engineContext.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        cursor->SetColor({ 0.7f, 0.7f, 0.7f, 1.0f });
    }
    if (engineContext.inputManager->IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || engineContext.inputManager->IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE) || engineContext.inputManager->IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
    {
        cursor->SetColor({ 1.0f, 1.0f,1.0f,1.0f });
    }

    timer += dt;

    if (engineContext.inputManager->IsKeyDown(KEY_LEFT))
    {
        cameraManager.GetActiveCamera()->AddPosition({ -500 * dt,0 });
    }
    if (engineContext.inputManager->IsKeyDown(KEY_RIGHT))
    {
        cameraManager.GetActiveCamera()->AddPosition({ 500 * dt,0 });
    }
    if (engineContext.inputManager->IsKeyDown(KEY_DOWN))
    {
        cameraManager.GetActiveCamera()->SetZoom({ cameraManager.GetActiveCamera()->GetZoom() - 5 * dt });
    }
    if (engineContext.inputManager->IsKeyDown(KEY_UP))
    {
        cameraManager.GetActiveCamera()->SetZoom({ cameraManager.GetActiveCamera()->GetZoom() + 5 * dt });
    }
    if (engineContext.inputManager->IsKeyDown(KEY_ESCAPE))
    {
        engineContext.engine->RequestQuit();
    }
    if (engineContext.inputManager->IsKeyReleased(KEY_N))
    {
        engineContext.stateManager->ChangeState(std::make_unique<MainMenu>());
    }
    if (engineContext.inputManager->IsKeyReleased(KEY_O))
    {
        engineContext.engine->RenderDebugDraws(true);
    }
    if (engineContext.inputManager->IsKeyReleased(KEY_P))
    {
        engineContext.engine->RenderDebugDraws(false);
    }
    if (engineContext.inputManager->IsKeyReleased(KEY_F))
    {
        engineContext.windowManager->SetFullScreen(true);
    }
    if (engineContext.inputManager->IsKeyReleased(KEY_G))
    {
        engineContext.windowManager->SetFullScreen(false);
    }

    // Tiles
    tileManager.Update(dt, engineContext);

    objectManager.UpdateAll(dt, engineContext);
}

void Level::LateUpdate(float dt, const EngineContext& engineContext)
{
    // Tiles
    tileManager.LateUpdate(dt, engineContext);
}

void Level::Draw(const EngineContext& engineContext)
{
    cursor->SetVisibility(false);

    // Tiles
    tileManager.Draw(engineContext);

    objectManager.DrawAll(engineContext);
}

void Level::Free(const EngineContext& engineContext)
{
    // Tiles
    tileManager.Free(engineContext);

    JIN_LOG("[Level] free called");
}

void Level::Unload(const EngineContext& engineContext)
{
    for (int i = 0; i < 10; i++)
    {
        engineContext.renderManager->UnregisterTexture("test" + std::to_string(i), engineContext);
    }

    // Tiles
    tileManager.Unload(engineContext);

    JIN_LOG("[Level] unload called");
}
