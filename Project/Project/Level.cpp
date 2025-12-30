#include "Level.h"
#include "Core/LevelSerializer.h"
#include "Engine.h"
#include "MainMenu.h"
#include "WordObject.h"
namespace LevelState
{
    void AsyncLoad(const EngineContext& engineContext, LoadingState* loading)
    {
        TextureSettings ts = { TextureMinFilter::Nearest, TextureMagFilter::Nearest, TextureWrap::ClampToBorder, TextureWrap::ClampToBorder };

     
        loading->QueueTexture(engineContext, "[Texture]MainCharacter", "Textures/MainCharacter/player.png", ts);
        loading->QueueTexture(engineContext, "[Texture]MainCharacter1", "Textures/MainCharacter/player1.png", ts);
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

      
        loading->QueueShader(engineContext, "[Shader]ColorOnly", { {ShaderStage::Vertex, "Shaders/ColorOnly.vert" },{ShaderStage::Fragment,"Shaders/ColorOnly.frag"} });
        loading->QueueShader(engineContext, "[Shader]Instancing", { {ShaderStage::Vertex, "Shaders/Instancing.vert" },{ShaderStage::Fragment,"Shaders/Instancing.frag"} });
        loading->QueueShader(engineContext, "S_Sprite", { { ShaderStage::Vertex, "Shaders/default.vert" }, { ShaderStage::Fragment, "Shaders/default.frag" } });

        loading->QueueFont(engineContext, "F_UI", "Fonts/font1.ttf", 32);
        loading->QueueSound("BGM_Main", "Sounds/test.mp3", true);
    }
}

void Level::Load(const EngineContext& engineContext)
{
    m_gridSystem.Resize(42, 24);
 
    auto spawner = [&](uint32_t id, int type, int64_t x, int64_t y, std::string tag) {
        float fx = BABO::Math::Fix64(x, BABO::Math::Fix64::RawTag{}).ToFloat();
        float fy = BABO::Math::Fix64(y, BABO::Math::Fix64::RawTag{}).ToFloat();

        if (type == 0) { 
            player = static_cast<Player*>(objectManager.AddObject(std::make_unique<Player>(), tag));
            player->GetTransform2D().SetPosition({ fx, fy });
        }
        else {
            auto t = std::make_unique<TileObject>();
            t->GetTransform2D().SetPosition({ fx, fy });
            objectManager.AddObject(std::move(t), tag);
        }
        };

    if (!BABO::IO::LevelSerializer::Load(m_levelPath, m_gridSystem, spawner)) {
        CreateDefaultLevel(m_levelPath);
        BABO::IO::LevelSerializer::Load(m_levelPath, m_gridSystem, spawner);
    }

    RenderManager* rm = engineContext.renderManager;
    rm->RegisterSpriteSheet("[SpriteSheet]MainCharacter", "[Texture]MainCharacter", 32, 32);
    rm->RegisterSpriteSheet("[SpriteSheet]MainCharacter1", "[Texture]MainCharacter1", 32, 32);
    rm->RegisterSpriteSheet("[SpriteSheet]Flag", "[Texture]Flag", 60, 60);

    rm->RegisterMaterial("[Material]default", "[EngineShader]default_texture", { {"u_Texture","[EngineTexture]RenderTexture"} });
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

    wordManager = static_cast<WordManager*>(objectManager.AddObject(std::make_unique<WordManager>(), "[Object]wordManager"));
	wordManager->ReadFile(engineContext, 1);

    for (int i = 0; i <= 8; ++i) {
        std::string name = "[Material]Background0" + std::to_string(i);
        std::string tex = "[Texture]Background0" + std::to_string(i);
        rm->RegisterMaterial(name, "[EngineShader]default_texture", { {"u_Texture", tex} });
    }
}

void Level::Init(const EngineContext& engineContext)
{

    auto setupBG = [&](BackgroundObject*& bg, BackgroundObject*& sub, int idx, float factor) {
        std::string mat = "[Material]Background0" + std::to_string(idx);
        bg = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg"));
        bg->SetMaterial(engineContext, mat);
        bg->SetRenderLayer("[Layer]Background");
        bg->SetFactor(factor);

        sub = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]bg"));
        sub->SetMaterial(engineContext, mat);
        sub->SetRenderLayer("[Layer]Background");
        sub->SetBasePos({ (float)engineContext.windowManager->GetWidth() ,0 });
        sub->SetFactor(factor);
        bg->SetNextBackground(sub);
        sub->SetNextBackground(bg);
        };

    setupBG(bgObj00, bgObj00Sub, 0, 1.0f);
    setupBG(bgObj01, bgObj01Sub, 1, 0.9f);
    setupBG(bgObj02, bgObj02Sub, 2, 0.8f);
    setupBG(bgObj03, bgObj03Sub, 3, 0.7f);
    setupBG(bgObj04, bgObj04Sub, 4, 0.5f);
    setupBG(bgObj05, bgObj05Sub, 5, 0.4f);
    setupBG(bgObj06, bgObj06Sub, 6, 0.3f);
    setupBG(bgObj07, bgObj07Sub, 7, 0.2f);
    setupBG(bgObj08, bgObj08Sub, 8, 0.0f);


    flag00 = static_cast<FlagObject*>(objectManager.AddObject(std::make_unique<FlagObject>(), "[Object]flag"));
    flag00->SetRenderLayer("[Layer]Flag");
    flag00->GetTransform2D().SetPosition({ -600, -170 });
    flag00->GetTransform2D().SetScale({ 100, 100 });
    flag00->SetGuide("Logic Test Level");


    cursor = static_cast<GameObject*>(objectManager.AddObject(std::make_unique<GameObject>(), "[Object]cursor"));
    cursor->SetMaterial(engineContext, "[Material]cursor");
    cursor->SetMesh(engineContext, "[EngineMesh]default");
    cursor->GetTransform2D().SetScale({ 30, 30 });
    cursor->SetRenderLayer("[Layer]Cursor");
    cursor->SetIgnoreCamera(true, cameraManager.GetActiveCamera());

    engineContext.soundManager->Play("BGM_Main", 1, 0);
}

void Level::SyncToLogicGrid()
{
    m_gridSystem.Reset();
    for (auto* obj : objectManager.GetAllRawPtrObjects()) {
        if (!obj || !obj->IsAlive()) continue;
        auto gp = m_gridSystem.WorldToGrid(BABO::Math::Fix64(obj->GetTransform2D().GetPosition().x),
            BABO::Math::Fix64(obj->GetTransform2D().GetPosition().y));
        if (auto* cell = m_gridSystem.GetCell(gp.x, gp.y)) {
            std::string tag = obj->GetTag();

            if (tag == "Player" || tag == "Word_PLAYER") cell->word = BABO::Logic::WordType::PLAYER;
            else if (tag == "Word_IS")   cell->word = BABO::Logic::WordType::IS;
            else if (tag == "Word_YOU")  cell->word = BABO::Logic::WordType::YOU;
            else if (tag == "Word_WALL") cell->word = BABO::Logic::WordType::WALL;
            else if (tag == "Word_STOP") cell->word = BABO::Logic::WordType::STOP;
            cell->entities.push_back(0);
        }
    }
}

void Level::Update(float dt, const EngineContext& ec)
{
  
    if (ec.inputManager->IsKeyDown(KEY_LEFT)) cameraManager.GetActiveCamera()->AddPosition({ -500 * dt, 0 });
    if (ec.inputManager->IsKeyDown(KEY_RIGHT)) cameraManager.GetActiveCamera()->AddPosition({ 500 * dt, 0 });
    if (ec.inputManager->IsKeyDown(KEY_DOWN)) cameraManager.GetActiveCamera()->SetZoom(cameraManager.GetActiveCamera()->GetZoom() - 5 * dt);
    if (ec.inputManager->IsKeyDown(KEY_UP)) cameraManager.GetActiveCamera()->SetZoom(cameraManager.GetActiveCamera()->GetZoom() + 5 * dt);


    if (ec.inputManager->IsKeyReleased(KEY_O)) ec.engine->RenderDebugDraws(true);
    if (ec.inputManager->IsKeyReleased(KEY_P)) ec.engine->RenderDebugDraws(false);
    if (ec.inputManager->IsKeyPressed(KEY_S)) SaveCurrentLevel();
    if (ec.inputManager->IsKeyPressed(KEY_L)) ec.stateManager->ChangeState(std::make_unique<Level>());

 
    if (ec.inputManager->IsKeyPressed(KEY_SPACE)) {
        SyncToLogicGrid();
        m_ruleManager.Parse(m_gridSystem);
        JIN_LOG("Active Rules Found: " << m_ruleManager.activeRules.size());
    }

    cursor->GetTransform2D().SetPosition(glm::vec2(
        ec.inputManager->GetMousePos().x - ec.windowManager->GetWidth() / 2.f,
        ec.windowManager->GetHeight() / 2.f - ec.inputManager->GetMousePos().y) + glm::vec2(11, -11));

    objectManager.UpdateAll(dt, ec);
}

void Level::Draw(const EngineContext& ec)
{
    if (cursor) cursor->SetVisibility(false);


    if (ec.engine->ShouldRenderDebugDraws()) {
        int w = m_gridSystem.GetWidth();
        int h = m_gridSystem.GetHeight();

        for (int i = 0; i <= w; ++i) ec.renderManager->DrawLine({ i * 30, 0 }, { i * 30, h * 30 }, { 1, 1, 1, 0.1f });
        for (int j = 0; j <= h; ++j) ec.renderManager->DrawLine({ 0, j * 30 }, { w * 30, j * 30 }, { 1, 1, 1, 0.1f });

        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                auto* cell = m_gridSystem.GetCell(x, y);
                if (cell && cell->isStaticWall) { 
                    ec.renderManager->DrawLine({ x * 30, y * 30 }, { (x + 1) * 30, (y + 1) * 30 }, { 1, 0, 0, 0.5f }, 2.0f);
                    ec.renderManager->DrawLine({ (x + 1) * 30, y * 30 }, { x * 30, (y + 1) * 30 }, { 1, 0, 0, 0.5f }, 2.0f);
                }
            }
        }
    }
    objectManager.DrawAll(ec);
}

void Level::SaveCurrentLevel()
{
    std::vector<BABO::IO::EntityData> entities;
    std::vector<std::string> tags;
    for (auto* obj : objectManager.GetAllRawPtrObjects()) {
        if (!obj || !obj->IsAlive()) continue;
        BABO::IO::EntityData d;
        d.type = (obj->GetTag() == "Player") ? 0 : 1;
        d.x = BABO::Math::Fix64(obj->GetTransform2D().GetPosition().x).Raw();
        d.y = BABO::Math::Fix64(obj->GetTransform2D().GetPosition().y).Raw();
        entities.push_back(d);
        tags.push_back(obj->GetTag());
    }
    BABO::IO::LevelSerializer::Save(m_levelPath, m_gridSystem, entities, tags);
}

void Level::CreateDefaultLevel(const std::string& path)
{
    BABO::World::GridSystem temp; temp.Resize(42, 24);
    std::vector<BABO::IO::EntityData> ents;
    std::vector<std::string> tags;
    BABO::IO::EntityData p; p.id = 1; p.type = 0;
    p.x = BABO::Math::Fix64(60.0f).Raw(); p.y = BABO::Math::Fix64(60.0f).Raw();
    ents.push_back(p); tags.push_back("Player");
    BABO::IO::LevelSerializer::Save(path, temp, ents, tags);
}
void Level::LateInit(const EngineContext& ec) {}
void Level::LateUpdate(float dt, const EngineContext& ec) {}
void Level::Free(const EngineContext& ec) { ec.windowManager->RemoveResizeCallback("[PostFX]WaterDrop"); }
void Level::Unload(const EngineContext& ec) {
    for (int i = 0; i < 10; i++) ec.renderManager->UnregisterTexture("test" + std::to_string(i), ec);
}
