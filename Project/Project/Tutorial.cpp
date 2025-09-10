#include "Tutorial.h"

#include <random>

#include "LoadingState.h"
#include "MainMenu.h"

void Tutorial::Load(const EngineContext& engineContext)
{
    SNAKE_LOG("[Tutorial] load called");
    RenderManager* rm = engineContext.renderManager;


    //rm->RegisterSpriteSheet("[SpriteSheet]MainCharacter", "[Texture]MainCharacter", 32, 32);
    //rm->RegisterSpriteSheet("[SpriteSheet]Flag", "[Texture]Flag", 60, 60);

    rm->RegisterMaterial("[Material]ColorOnly", "[Shader]ColorOnly", {});

    rm->RegisterMaterial("[Material]Instancing", "[Shader]Instancing", { {"u_Texture","[Texture]Leaf"} });


    rm->RegisterMaterial("[Material]Background00", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background00"} });
    rm->RegisterMaterial("[Material]Background01", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background01"} });
    rm->RegisterMaterial("[Material]Background02", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background02"} });
    rm->RegisterMaterial("[Material]Background03", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background03"} });
    rm->RegisterMaterial("[Material]Background04", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background04"} });
    rm->RegisterMaterial("[Material]Background05", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background05"} });
    rm->RegisterMaterial("[Material]Background06", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background06"} });
    rm->RegisterMaterial("[Material]Background07", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background07"} });
    rm->RegisterMaterial("[Material]Background08", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background08"} });

    text = static_cast<TextObject*>(engineContext.stateManager->GetCurrentState()->GetObjectManager().AddObject(
        std::make_unique<TextObject>(engineContext.renderManager->GetFontByTag("[Font]default"), "test", TextAlignH::Center, TextAlignV::Middle),
        "[Object]Text"));
    text->SetRenderLayer("[Layer]UIText");
    text->GetTransform2D().SetScale({ 0.3f,0.3f });


    bgObj00 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg00"));
    bgObj00->SetMaterial(engineContext, "[Material]Background00");
    bgObj00->SetRenderLayer("[Layer]Background");
    bgObj00->SetFactor(1.0);
 

    bgObj01 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg01"));
    bgObj01->SetMaterial(engineContext, "[Material]Background01");
    bgObj01->SetRenderLayer("[Layer]Background");
    bgObj01->SetFactor(0.9);

    bgObj02 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg02"));
    bgObj02->SetMaterial(engineContext, "[Material]Background02");
    bgObj02->SetRenderLayer("[Layer]Background");
    bgObj02->SetFactor(0.8);

    bgObj03 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg03"));
    bgObj03->SetMaterial(engineContext, "[Material]Background03");
    bgObj03->SetRenderLayer("[Layer]Background");
    bgObj03->SetFactor(0.7);

    bgObj04 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg04"));
    bgObj04->SetMaterial(engineContext, "[Material]Background04");
    bgObj04->SetRenderLayer("[Layer]Background");
    bgObj04->SetFactor(0.5);

    bgObj05 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg05"));
    bgObj05->SetMaterial(engineContext, "[Material]Background05");
    bgObj05->SetRenderLayer("[Layer]Background");
    bgObj05->SetFactor(0.4);

    bgObj06 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg06"));
    bgObj06->SetMaterial(engineContext, "[Material]Background06");
    bgObj06->SetRenderLayer("[Layer]Background");
    bgObj06->SetFactor(0.3);

    bgObj07 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg07"));
    bgObj07->SetMaterial(engineContext, "[Material]Background07");
    bgObj07->SetRenderLayer("[Layer]Background");
    bgObj07->SetFactor(0.2);

    bgObj08 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg08"));
    bgObj08->SetMaterial(engineContext, "[Material]Background08");
    bgObj08->SetRenderLayer("[Layer]Background");
    bgObj08->SetFactor(0.0);

    bgObj00Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg00"));
    bgObj00Sub->SetMaterial(engineContext, "[Material]Background00");
    bgObj00Sub->SetRenderLayer("[Layer]Background");
    bgObj00Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj00Sub->SetFactor(1.0);

    bgObj01Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg01"));
    bgObj01Sub->SetMaterial(engineContext, "[Material]Background01");
    bgObj01Sub->SetRenderLayer("[Layer]Background");
    bgObj01Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj01Sub->SetFactor(0.9);

    bgObj02Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg02"));
    bgObj02Sub->SetMaterial(engineContext, "[Material]Background02");
    bgObj02Sub->SetRenderLayer("[Layer]Background");
    bgObj02Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj02Sub->SetFactor(0.8);

    bgObj03Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg03"));
    bgObj03Sub->SetMaterial(engineContext, "[Material]Background03");
    bgObj03Sub->SetRenderLayer("[Layer]Background");
    bgObj03Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj03Sub->SetFactor(0.7);

    bgObj04Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg04"));
    bgObj04Sub->SetMaterial(engineContext, "[Material]Background04");
    bgObj04Sub->SetRenderLayer("[Layer]Background");
    bgObj04Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj04Sub->SetFactor(0.5);
    bgObj04Sub->SetFlipUV_X(true);

    bgObj05Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg05"));
    bgObj05Sub->SetMaterial(engineContext, "[Material]Background05");
    bgObj05Sub->SetRenderLayer("[Layer]Background");
    bgObj05Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj05Sub->SetFactor(0.4);

    bgObj06Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg06"));
    bgObj06Sub->SetMaterial(engineContext, "[Material]Background06");
    bgObj06Sub->SetRenderLayer("[Layer]Background");
    bgObj06Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj06Sub->SetFactor(0.3);

    bgObj07Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg07"));
    bgObj07Sub->SetMaterial(engineContext, "[Material]Background07");
    bgObj07Sub->SetRenderLayer("[Layer]Background");
    bgObj07Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj07Sub->SetFactor(0.2);

    bgObj08Sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg08"));
    bgObj08Sub->SetMaterial(engineContext, "[Material]Background08");
    bgObj08Sub->SetRenderLayer("[Layer]Background");
    bgObj08Sub->SetBasePos({ engineContext.windowManager->GetWidth() ,0 });
    bgObj08Sub->SetFactor(0.0);

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


    flag00 = static_cast<FlagObject*>(objectManager.AddObject(std::make_unique<FlagObject>(), "[Object]flag"));
    flag00->SetRenderLayer("[Layer]Flag");
    flag00->GetTransform2D().SetPosition(glm::vec2(-600, -170));
    flag00->SetGuide("These leaves are rendered using instancing.\nCheck InstancedObject.cpp for more Info.");

    flag01 = static_cast<FlagObject*>(objectManager.AddObject(std::make_unique<FlagObject>(), "[Object]flag"));
    flag01->SetRenderLayer("[Layer]Flag");
    flag01->GetTransform2D().SetPosition(glm::vec2(200, -170));
    flag01->SetGuide("Move Left & Right with A,D key.\nInput can be handled via Inputmanager\nand can be accessed from engineContext");

    flag02 = static_cast<FlagObject*>(objectManager.AddObject(std::make_unique<FlagObject>(), "[Object]flag"));
    flag02->SetRenderLayer("[Layer]Flag");
    flag02->GetTransform2D().SetPosition(glm::vec2(800, -170));
    flag02->SetGuide("Objects are managed via ObjectManager.\n Each State has its own ObjectManager.");

    player = static_cast<Player*>(objectManager.AddObject(std::make_unique<Player>(), "[Object]player"));
    player->SetRenderLayer("[Layer]Player");


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

    player->GetTransform2D().SetDepth(00.0f);
}

void Tutorial::Init(const EngineContext& engineContext)
{
    SNAKE_LOG("[Tutorial] init called");
    engineContext.soundManager->Play("BGM_Main", 1, 0);
  //  engineContext.engine->RenderDebugDraws(true);
}

void Tutorial::LateInit(const EngineContext& engineContext)
{
}

void Tutorial::Update(float dt, const EngineContext& engineContext)
{
    text->SetText(std::to_string(objectManager.GetAllRawPtrObjects().size()));
    if (leafSpawnTimer >=0.01f)
    {
        float cnt = objectManager.GetAllRawPtrObjects().size() / 10.f;
        objectManager.AddObject(std::make_unique<InstancedObject>())->GetTransform2D().SetDepth(cnt);
        objectManager.AddObject(std::make_unique<InstancedObject>())->GetTransform2D().SetDepth(cnt);
        objectManager.AddObject(std::make_unique<InstancedObject>())->GetTransform2D().SetDepth(cnt);

        leafSpawnTimer = 0.0f;
    }
    if (engineContext.inputManager->IsKeyDown(KEY_LEFT))
    {
        cameraManager.GetActiveCamera()->AddPosition({ -500 * dt,0 });
    }
    if (engineContext.inputManager->IsKeyDown(KEY_RIGHT))
    {
        cameraManager.GetActiveCamera()->AddPosition({ 500 * dt,0 });
    }
    if (engineContext.inputManager->IsKeyDown(KEY_ESCAPE))
    {
        engineContext.engine->RequestQuit();
    }
    if (engineContext.inputManager->IsKeyReleased(KEY_N))
    {
        engineContext.stateManager->ChangeState(std::make_unique<MainMenu>());
    }
    leafSpawnTimer += dt;
    objectManager.UpdateAll(dt, engineContext);
}

void Tutorial::LateUpdate(float dt, const EngineContext& engineContext)
{
}

void Tutorial::Draw(const EngineContext& engineContext)
{
    objectManager.DrawAll(engineContext);
}


void Tutorial::Free(const EngineContext& engineContext)
{
    SNAKE_LOG("[Tutorial] free called");
}

void Tutorial::Unload(const EngineContext& engineContext)
{
    for (int i = 0; i < 100; i++)
    {
        engineContext.renderManager->UnregisterTexture("test" + std::to_string(i), engineContext);
    }

    SNAKE_LOG("[Tutorial] unload called");
}
