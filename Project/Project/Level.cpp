#include "Level.h"
#include "Core/LevelSerializer.h"
#include "Engine.h"
#include "MainMenu.h"
#include "WordObject.h"
#include "TileManager.h"

TileManager* tileManager;

namespace LevelState
{
    void AsyncLoad(const EngineContext& engineContext, LoadingState* loading)
    {
        TextureSettings ts = { TextureMinFilter::Nearest, TextureMagFilter::Nearest, TextureWrap::ClampToBorder, TextureWrap::ClampToBorder };

        //BG
        loading->QueueTexture(engineContext, "[Texture]Bg00", "Textures/BG/BG.png");

        //Tiles
        TileState::AsyncLoad(engineContext, loading);
      
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
 
    /*auto spawner = [&](uint32_t id, int type, int64_t x, int64_t y, std::string tag) {
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
    }*/

    RenderManager* rm = engineContext.renderManager;

    rm->RegisterMaterial("[Material]default", "[EngineShader]default_texture", { {"u_Texture","[EngineTexture]RenderTexture"} });
    rm->RegisterMaterial("[Material]ColorOnly", "[Shader]ColorOnly", {});
    rm->RegisterMaterial("[Material]Instancing", "[Shader]Instancing", { {"u_Texture","[Texture]Leaf"} });

    wordManager = static_cast<WordManager*>(objectManager.AddObject(std::make_unique<WordManager>(), "[Object]wordManager"));
    wordManager->ReadFile(engineContext, 1);

    // BG
    rm->RegisterMaterial("[Material]Bg00", "[EngineShader]default_texture", { {"u_Texture","[Texture]Bg00"} });

    // Tiles
    tileManager = &TileManager::instance();
    tileManager->Load(engineContext);
}

void Level::Init(const EngineContext& engineContext)
{
    cursor = static_cast<GameObject*>(objectManager.AddObject(std::make_unique<GameObject>()));
    cursor->SetMaterial(engineContext, "[Material]cursor");
    cursor->SetMesh(engineContext, "[EngineMesh]default");
    cursor->GetTransform2D().SetScale({ 30,30 });
    cursor->SetRenderLayer("[Layer]Cursor");

    bgObj00 = static_cast<BackgroundObject*>(objectManager.AddObject(std::make_unique<BackgroundObject>(), "[Object]Bg00"));
    bgObj00->SetMaterial(engineContext, "[Material]Bg00");
    bgObj00->SetRenderLayer("[Layer]Background");

    engineContext.soundManager->Play("BGM_Main", 1, 0);

    int w = engineContext.windowManager->GetWidth();
    int h = engineContext.windowManager->GetHeight();

    bgObj00->GetTransform2D().SetScale({ w, h });
    bgObj00->GetTransform2D().AddPosition({ w / 4, 0 });

    // Tiles
    tileManager->Init(engineContext, objectManager);
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
    cursor->GetTransform2D().SetPosition(ec.inputManager->GetMouseWorldPos(cameraManager.GetActiveCamera()) + glm::vec2(11, -11));
    if (ec.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || ec.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) || ec.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        cursor->SetColor({ 0.7f, 0.7f, 0.7f, 1.0f });
    }
    if (ec.inputManager->IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || ec.inputManager->IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE) || ec.inputManager->IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
    {
        cursor->SetColor({ 1.0f, 1.0f,1.0f,1.0f });
    }
    //if (ec.inputManager->IsKeyDown(KEY_LEFT)) cameraManager.GetActiveCamera()->AddPosition({ -500 * dt, 0 });
    //if (ec.inputManager->IsKeyDown(KEY_RIGHT)) cameraManager.GetActiveCamera()->AddPosition({ 500 * dt, 0 });
    //if (ec.inputManager->IsKeyDown(KEY_DOWN)) cameraManager.GetActiveCamera()->SetZoom(cameraManager.GetActiveCamera()->GetZoom() - 5 * dt);
    //if (ec.inputManager->IsKeyDown(KEY_UP)) cameraManager.GetActiveCamera()->SetZoom(cameraManager.GetActiveCamera()->GetZoom() + 5 * dt);

    if (ec.inputManager->IsKeyDown(KEY_ESCAPE)) ec.engine->RequestQuit();
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

    // Tiles
    tileManager->Update(dt, ec);

    objectManager.UpdateAll(dt, ec);
}

void Level::Draw(const EngineContext& ec)
{
    if (cursor) cursor->SetVisibility(true);

    //Grid
    if (ec.engine->ShouldRenderDebugDraws())
    {
        int w = m_gridSystem.GetWidth();
        int h = m_gridSystem.GetHeight();

        float cellSize = 30.0f;

        float offsetX = 0;
        float offsetY = -(h * cellSize) * 0.5f;

        // virtical line
        for (int i = 0; i <= w; ++i) {
            float x = offsetX + i * cellSize;
            ec.renderManager->DrawLine( { x, offsetY }, { x, offsetY + h * cellSize }, { 0, 0, 1, 0.3f } );
        }

        // horizontal line
        for (int j = 0; j <= h; ++j) {
            float y = offsetY + j * cellSize;
            ec.renderManager->DrawLine( { offsetX, y }, { offsetX + w * cellSize, y }, { 0, 0, 1, 0.3f } );
        }

        // cell line
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                auto* cell = m_gridSystem.GetCell(x, y);
                if (cell && cell->isStaticWall) {
                    float x0 = offsetX + x * cellSize;
                    float y0 = offsetY + y * cellSize;
                    float x1 = offsetX + (x + 1) * cellSize;
                    float y1 = offsetY + (y + 1) * cellSize;

                    ec.renderManager->DrawLine( { x0, y0 }, { x1, y1 }, { 1, 0, 0, 0.5f }, 2.0f );
                    ec.renderManager->DrawLine( { x1, y0 }, { x0, y1 }, { 1, 0, 0, 0.5f }, 2.0f );
                }
            }
        }
    }


    // Tiles
    tileManager->Draw(ec);

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
void Level::LateInit(const EngineContext& ec) {

    // Tiles
    tileManager->LateInit(ec);
}
void Level::LateUpdate(float dt, const EngineContext& ec) {


    // Tiles
    tileManager->LateUpdate(dt, ec);
}
void Level::Free(const EngineContext& ec) { 

    // Tiles
    tileManager->Free(ec);
}
void Level::Unload(const EngineContext& ec) {
    for (int i = 0; i < 10; i++) ec.renderManager->UnregisterTexture("test" + std::to_string(i), ec);

    // Tiles
    tileManager->Unload(ec);
}
