//#include "Level.h"
//#include "MainMenu.h"
//
//namespace LevelState
//{
//    void AsyncLoad(const EngineContext& engineContext, LoadingState* loading)
//    {
//        TextureSettings ts = { TextureMinFilter::Nearest,TextureMagFilter::Nearest,TextureWrap::ClampToBorder,TextureWrap::ClampToBorder };
//        loading->QueueTexture(engineContext, "[Texture]MainCharacter", "Textures/MainCharacter/player.png", ts);
//        loading->QueueTexture(engineContext, "[Texture]MainCharacter1", "Textures/MainCharacter/player1.png", ts);
//        loading->QueueTexture(engineContext, "[Texture]Flag", "Textures/flag.png");
//        loading->QueueTexture(engineContext, "[Texture]Background00", "Textures/Background/_09_background.png");
//        loading->QueueTexture(engineContext, "[Texture]Background01", "Textures/Background/_08_distant_clouds.png");
//        loading->QueueTexture(engineContext, "[Texture]Background02", "Textures/Background/_07_clouds.png");
//        loading->QueueTexture(engineContext, "[Texture]Background03", "Textures/Background/_06_hill2.png");
//        loading->QueueTexture(engineContext, "[Texture]Background04", "Textures/Background/_05_hill1.png");
//        loading->QueueTexture(engineContext, "[Texture]Background05", "Textures/Background/_04_bushes.png");
//        loading->QueueTexture(engineContext, "[Texture]Background06", "Textures/Background/_03_distant_trees.png");
//        loading->QueueTexture(engineContext, "[Texture]Background07", "Textures/Background/_02_trees and bushes.png");
//        loading->QueueTexture(engineContext, "[Texture]Background08", "Textures/Background/_01_ground.png");
//
//        loading->QueueShader(engineContext, "[Shader]ColorOnly", { {ShaderStage::Vertex, "Shaders/ColorOnly.vert" },{ShaderStage::Fragment,"Shaders/ColorOnly.frag"} });
//        loading->QueueShader(engineContext, "[Shader]Instancing", { {ShaderStage::Vertex, "Shaders/Instancing.vert" },{ShaderStage::Fragment,"Shaders/Instancing.frag"} });
//
//        for (int i = 0; i < 10; i++)
//        {
//            loading->QueueTexture(engineContext, "test" + std::to_string(i), "Textures/test.jpg",
//                TextureSettings{ TextureMinFilter::Linear, TextureMagFilter::Linear, TextureWrap::ClampToEdge, TextureWrap::ClampToEdge, /*generateMipmap*/true });
//        }
//
//        loading->QueueShader(engineContext, "S_Sprite",
//            {
//                { ShaderStage::Vertex,   "Shaders/default.vert" },
//                { ShaderStage::Fragment, "Shaders/default.frag" }
//            });
//
//
//        loading->QueueFont(engineContext, "F_UI", "Fonts/font1.ttf", 32);
//
//        loading->QueueSound("BGM_Main", "Sounds/test.mp3", true);
//
//
//    }
//}
//
//void Level::Load(const EngineContext& engineContext)
//{
//    m_gridSystem.Resize(42, 24); // 30*30 타일 기준 화면 크기
//
//    auto spawner = [&](uint32_t id, int type, int64_t x, int64_t y) {
//        float fx = BABO::Math::Fix64(x, BABO::Math::Fix64::RawTag{}).ToFloat();
//        float fy = BABO::Math::Fix64(y, BABO::Math::Fix64::RawTag{}).ToFloat();
//        if (type == 0) {
//            player = static_cast<Player*>(objectManager.AddObject(std::make_unique<Player>(), "Player"));
//            player->GetTransform2D().SetPosition({ fx, fy });
//        }
//        else {
//            auto t = std::make_unique<TileObject>();
//            t->GetTransform2D().SetPosition({ fx, fy });
//            objectManager.AddObject(std::move(t), "Tile");
//        }
//        };
//
//    if (!BABO::IO::LevelSerializer::Load(m_levelPath, m_gridSystem, spawner)) {
//        CreateDefaultLevel(m_levelPath);
//        BABO::IO::LevelSerializer::Load(m_levelPath, m_gridSystem, spawner);
//    }
//    JIN_LOG("[Level] load called");
//    RenderManager* rm = engineContext.renderManager;
//
//    rm->RegisterSpriteSheet("[SpriteSheet]MainCharacter", "[Texture]MainCharacter", 32, 32);
//    rm->RegisterSpriteSheet("[SpriteSheet]MainCharacter1", "[Texture]MainCharacter1", 32, 32);
//    rm->RegisterSpriteSheet("[SpriteSheet]Flag", "[Texture]Flag", 60, 60);
//
//    rm->RegisterMaterial("[Material]default", "[EngineShader]default_texture", { {"u_Texture","[EngineTexture]RenderTexture"} });
//
//    rm->RegisterMaterial("[Material]ColorOnly", "[Shader]ColorOnly", {});
//
//    rm->RegisterMaterial("[Material]Instancing", "[Shader]Instancing", { {"u_Texture","[Texture]Leaf"} });
//
//    rm->RegisterMaterial("[Material]Background00", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background00"} });
//    rm->RegisterMaterial("[Material]Background01", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background01"} });
//    rm->RegisterMaterial("[Material]Background02", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background02"} });
//    rm->RegisterMaterial("[Material]Background03", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background03"} });
//    rm->RegisterMaterial("[Material]Background04", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background04"} });
//    rm->RegisterMaterial("[Material]Background05", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background05"} });
//    rm->RegisterMaterial("[Material]Background06", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background06"} });
//    rm->RegisterMaterial("[Material]Background07", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background07"} });
//    rm->RegisterMaterial("[Material]Background08", "[EngineShader]default_texture", { {"u_Texture","[Texture]Background08"} });
//}
//
//
//void Level::LateInit(const EngineContext& engineContext)
//{
//}
//
//void Level::Update(float dt, const EngineContext& engineContext)
//{
//    //Floor Collider
//    auto* col = static_cast<AABBCollider*>(frObj00->GetCollider());
//    col->SetSize({ engineContext.windowManager->GetWidth(), 90 });
//
//    //Cursor
//    cursor->GetTransform2D().SetPosition(glm::vec2(engineContext.inputManager->GetMousePos().x - engineContext.windowManager->GetWidth() / 2.f, engineContext.windowManager->GetHeight() / 2.f - engineContext.inputManager->GetMousePos().y) + glm::vec2(11, -11));
//    if (engineContext.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || engineContext.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) || engineContext.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
//    {
//        cursor->SetColor({ 0.7f, 0.7f, 0.7f, 1.0f });
//    }
//    if (engineContext.inputManager->IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || engineContext.inputManager->IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE) || engineContext.inputManager->IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
//    {
//        cursor->SetColor({ 1.0f, 1.0f,1.0f,1.0f });
//    }
//
//    timer += dt;
//
//    if (engineContext.inputManager->IsKeyDown(KEY_LEFT))
//    {
//        cameraManager.GetActiveCamera()->AddPosition({ -500 * dt,0 });
//    }
//    if (engineContext.inputManager->IsKeyDown(KEY_RIGHT))
//    {
//        cameraManager.GetActiveCamera()->AddPosition({ 500 * dt,0 });
//    }
//    if (engineContext.inputManager->IsKeyDown(KEY_DOWN))
//    {
//        cameraManager.GetActiveCamera()->SetZoom({ cameraManager.GetActiveCamera()->GetZoom() - 5 * dt });
//    }
//    if (engineContext.inputManager->IsKeyDown(KEY_UP))
//    {
//        cameraManager.GetActiveCamera()->SetZoom({ cameraManager.GetActiveCamera()->GetZoom() + 5 * dt });
//    }
//    if (engineContext.inputManager->IsKeyDown(KEY_ESCAPE))
//    {
//        engineContext.engine->RequestQuit();
//    }
//    if (engineContext.inputManager->IsKeyReleased(KEY_N))
//    {
//        engineContext.stateManager->ChangeState(std::make_unique<MainMenu>());
//    }
//    if (engineContext.inputManager->IsKeyReleased(KEY_O))
//    {
//        engineContext.engine->RenderDebugDraws(true);
//    }
//    if (engineContext.inputManager->IsKeyReleased(KEY_P))
//    {
//        engineContext.engine->RenderDebugDraws(false);
//    }
//    if (engineContext.inputManager->IsKeyReleased(KEY_F))
//    {
//        engineContext.windowManager->SetFullScreen(true);
//    }
//    if (engineContext.inputManager->IsKeyReleased(KEY_G))
//    {
//        engineContext.windowManager->SetFullScreen(false);
//    }
//    if (engineContext.inputManager->IsKeyPressed(KEY_1))
//    {
//        player->PlayerMove(Player::PlayerMoveType::LEFT, engineContext);
//    }
//    if (engineContext.inputManager->IsKeyPressed(KEY_2))
//    {
//        player->PlayerMove(Player::PlayerMoveType::RIGHT, engineContext);
//    }
//    if (engineContext.inputManager->IsKeyPressed(KEY_3))
//    {
//        player->PlayerMove(Player::PlayerMoveType::UP, engineContext);
//    }
//    objectManager.UpdateAll(dt, engineContext);
//    if (engineContext.inputManager->IsKeyPressed(KEY_SPACE)) {
//        SyncToLogicGrid();
//        m_ruleManager.Parse(m_gridSystem); 
//        for (auto& r : m_ruleManager.activeRules) JIN_LOG("Rule Active!");
//    }
//    objectManager.UpdateAll(dt, engineContext);
//
//}
//
//void Level::LateUpdate(float dt, const EngineContext& engineContext)
//{
//}
//
//void Level::Draw(const EngineContext& engineContext)
//{
//    cursor->SetVisibility(false);
//    for (int i = 0; i <= 42; ++i) engineContext.renderManager->DrawLine({ i * 30, 0 }, { i * 30, 720 }, { 1,1,1,0.2f });
//    for (int j = 0; j <= 24; ++j) engineContext.renderManager->DrawLine({ 0, j * 30 }, { 1280, j * 30 }, { 1,1,1,0.2f });
//    objectManager.DrawAll(engineContext);
//
//}
//
//void Level::Free(const EngineContext& engineContext)
//{
//    engineContext.windowManager->RemoveResizeCallback("[PostFX]WaterDrop");
//    JIN_LOG("[Level] free called");
//}
//
//void Level::Unload(const EngineContext& engineContext)
//{
//    for (int i = 0; i < 10; i++)
//    {
//        engineContext.renderManager->UnregisterTexture("test" + std::to_string(i), engineContext);
//    }
//
//    JIN_LOG("[Level] unload called");
//}
//
//void Level::CreateDefaultLevel(const std::string& path)
//{
//    BABO::World::GridSystem temp; temp.Resize(42, 24);
//    std::vector<BABO::IO::EntityData> ents;
//    BABO::IO::EntityData p; p.type = 0; p.x = BABO::Math::Fix64(60.0f).Raw(); p.y = BABO::Math::Fix64(60.0f).Raw();
//    ents.push_back(p);
//    BABO::IO::LevelSerializer::Save(path, temp, ents);
//}
//
//void Level::SyncToLogicGrid()
//{
//    m_gridSystem.Reset();
//    for (auto* obj : objectManager.GetAllRawPtrObjects()) {
//        auto gp = m_gridSystem.WorldToGrid(BABO::Math::Fix64(obj->GetTransform2D().GetPosition().x),
//            BABO::Math::Fix64(obj->GetTransform2D().GetPosition().y));
//        if (auto* cell = m_gridSystem.GetCell(gp.x, gp.y)) {
//            if (obj->GetTag() == "Player") cell->word = BABO::Logic::WordType::PLAYER;
//            cell->entities.push_back(0);
//        }
//    }
//}
#ifdef FALSE



#include "Level.h"
#include "Core/LevelSerializer.h"
#include "Engine.h"
#include "MainMenu.h"

namespace LevelState
{
	void AsyncLoad(const EngineContext& engineContext, LoadingState* loading)
	{
		TextureSettings ts = { TextureMinFilter::Nearest,TextureMagFilter::Nearest,TextureWrap::ClampToBorder,TextureWrap::ClampToBorder };
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
void Level::Load(const EngineContext& engineContext) {

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
        JIN_WRN("Map file not found. Creating default...");
        CreateDefaultLevel(m_levelPath);
        BABO::IO::LevelSerializer::Load(m_levelPath, m_gridSystem, spawner);
    }




	    RenderManager* rm = engineContext.renderManager;
	
	    rm->RegisterSpriteSheet("[SpriteSheet]MainCharacter", "[Texture]MainCharacter", 32, 32);
	    rm->RegisterSpriteSheet("[SpriteSheet]MainCharacter1", "[Texture]MainCharacter1", 32, 32);
	    rm->RegisterSpriteSheet("[SpriteSheet]Flag", "[Texture]Flag", 60, 60);
        JIN_LOG("[Level] load called");
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

            if (tag == "Player") cell->word = BABO::Logic::WordType::PLAYER;
            else if (tag == "Word_IS") cell->word = BABO::Logic::WordType::IS;
            else if (tag == "Word_YOU") cell->word = BABO::Logic::WordType::YOU;
            else if (tag == "Word_PUSH") cell->word = BABO::Logic::WordType::PUSH;
            else if (tag == "Word_STOP") cell->word = BABO::Logic::WordType::STOP;

            cell->entities.push_back(0);
        }
    }
}

void Level::SaveCurrentLevel() {
    std::vector<BABO::IO::EntityData> entities;
    std::vector<std::string> tags; 

    for (auto* obj : objectManager.GetAllRawPtrObjects()) {
        if (!obj || !obj->IsAlive()) continue;

        BABO::IO::EntityData data;
        data.type = (obj->GetTag() == "Player") ? 0 : 1;
        data.x = BABO::Math::Fix64(obj->GetTransform2D().GetPosition().x).Raw();
        data.y = BABO::Math::Fix64(obj->GetTransform2D().GetPosition().y).Raw();

        entities.push_back(data);
        tags.push_back(obj->GetTag()); 
    }
    BABO::IO::LevelSerializer::Save(m_levelPath, m_gridSystem, entities, tags);
}

void Level::Update(float dt, const EngineContext& engineContext)
{
#ifdef FALSE
    // 카메라 이동 (좌/우)
    if (engineContext.inputManager->IsKeyDown(KEY_LEFT))
    {
        cameraManager.GetActiveCamera()->AddPosition({ -500 * dt, 0 });
    }
    if (engineContext.inputManager->IsKeyDown(KEY_RIGHT))
    {
        cameraManager.GetActiveCamera()->AddPosition({ 500 * dt, 0 });
    }

    // 카메라 줌 (상/하)
    if (engineContext.inputManager->IsKeyDown(KEY_DOWN))
    {
        cameraManager.GetActiveCamera()->SetZoom({ cameraManager.GetActiveCamera()->GetZoom() - 5 * dt });
    }
    if (engineContext.inputManager->IsKeyDown(KEY_UP))
    {
        cameraManager.GetActiveCamera()->SetZoom({ cameraManager.GetActiveCamera()->GetZoom() + 5 * dt });
    }
	bool isTickInput = engineContext.inputManager->IsKeyPressed(KEY_LEFT) ||
		engineContext.inputManager->IsKeyPressed(KEY_RIGHT) ||
		engineContext.inputManager->IsKeyPressed(KEY_SPACE);
    if (engineContext.inputManager->IsKeyReleased(KEY_F))
    {
        engineContext.windowManager->SetFullScreen(true);
    }
    if (engineContext.inputManager->IsKeyReleased(KEY_G))
    {
        engineContext.windowManager->SetFullScreen(false);
    }

    // ESC 키로 엔진 종료 요청
    if (engineContext.inputManager->IsKeyDown(KEY_ESCAPE))
    {
        engineContext.engine->RequestQuit();
    }
    // 디버그 드로잉 On/Off
    if (engineContext.inputManager->IsKeyReleased(KEY_O))
    {
        engineContext.engine->RenderDebugDraws(true);
    }
    if (engineContext.inputManager->IsKeyReleased(KEY_P))
    {
        engineContext.engine->RenderDebugDraws(false);
    }

    // 'N' 키 입력 시 메인 메뉴 상태로 변경
    if (engineContext.inputManager->IsKeyReleased(KEY_N))
    {
        engineContext.stateManager->ChangeState(std::make_unique<MainMenu>());
    }
    // 커서 위치 업데이트 (화면 중앙 기준 좌표 계산)
    cursor->GetTransform2D().SetPosition(glm::vec2(
        engineContext.inputManager->GetMousePos().x - engineContext.windowManager->GetWidth() / 2.f,
        engineContext.windowManager->GetHeight() / 2.f - engineContext.inputManager->GetMousePos().y) + glm::vec2(11, -11));

    // 마우스 버튼 클릭 시 색상 변경
    if (engineContext.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ||
        engineContext.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) ||
        engineContext.inputManager->IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        cursor->SetColor({ 0.7f, 0.7f, 0.7f, 1.0f });
    }
    if (engineContext.inputManager->IsMouseButtonReleased(MOUSE_BUTTON_LEFT) ||
        engineContext.inputManager->IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE) ||
        engineContext.inputManager->IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
    {
        cursor->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
    }
	if (isTickInput) {
		// 1. 논리 그리드 동기화
		SyncToLogicGrid();

		// 2. 규칙 파싱 
		m_ruleManager.Parse(m_gridSystem);
		for (auto& r : m_ruleManager.activeRules) {
			JIN_LOG("Rule Detected!"); 
		}

		// 3. 물리 솔버 업데이트 (GDD 2.2 구현 시)
		// BABO::Physics::PhysicsSolver solver(&m_gridSystem);
		// solver.Update(dt);
	}

	objectManager.UpdateAll(dt, engineContext);

#else
    if (engineContext.inputManager->IsKeyDown(KEY_LEFT)) cameraManager.GetActiveCamera()->AddPosition({ -500 * dt, 0 });
    if (engineContext.inputManager->IsKeyDown(KEY_RIGHT)) cameraManager.GetActiveCamera()->AddPosition({ 500 * dt, 0 });
    if (engineContext.inputManager->IsKeyDown(KEY_DOWN)) cameraManager.GetActiveCamera()->SetZoom(cameraManager.GetActiveCamera()->GetZoom() - 5 * dt);
    if (engineContext.inputManager->IsKeyDown(KEY_UP)) cameraManager.GetActiveCamera()->SetZoom(cameraManager.GetActiveCamera()->GetZoom() + 5 * dt);
        if (engineContext.inputManager->IsKeyReleased(KEY_O))
    {
        engineContext.engine->RenderDebugDraws(true);
    }
    if (engineContext.inputManager->IsKeyReleased(KEY_P))
    {
        engineContext.engine->RenderDebugDraws(false);
    }

    if (engineContext.inputManager->IsKeyPressed(KEY_S)) { SaveCurrentLevel(); }
    if (engineContext.inputManager->IsKeyPressed(KEY_L)) {
        engineContext.stateManager->ChangeState(std::make_unique<Level>());
        JIN_LOG("Reloading Level from file...");
    }
    if (engineContext.inputManager->IsKeyPressed(KEY_SPACE)) {
        SyncToLogicGrid();
        m_ruleManager.Parse(m_gridSystem);
        JIN_LOG("Rules Updated. Current count: " << m_ruleManager.activeRules.size());
    }

    cursor->GetTransform2D().SetPosition(glm::vec2(
        engineContext.inputManager->GetMousePos().x - engineContext.windowManager->GetWidth() / 2.f,
        engineContext.windowManager->GetHeight() / 2.f - engineContext.inputManager->GetMousePos().y) + glm::vec2(11, -11));

    objectManager.UpdateAll(dt, engineContext);
#endif
}

void Level::LateUpdate(float dt, const EngineContext& engineContext)
{
}

void Level::Draw(const EngineContext& engineContext)
{
    if (cursor) cursor->SetVisibility(false);

    // 2. 디버그 정보 그리기 (격자 및 논리 데이터 확인)
    if (engineContext.engine->ShouldRenderDebugDraws()) {
        int w = m_gridSystem.GetWidth();
        int h = m_gridSystem.GetHeight();

        // [격자 그리기] 아주 연한 흰색 선
        for (int i = 0; i <= w; ++i)
            engineContext.renderManager->DrawLine({ i * 30, 0 }, { i * 30, h * 30 }, { 1, 1, 1, 0.1f });
        for (int j = 0; j <= h; ++j)
            engineContext.renderManager->DrawLine({ 0, j * 30 }, { w * 30, j * 30 }, { 1, 1, 1, 0.1f });

        // [셀 내부 논리 상태 확인]
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                auto* cell = m_gridSystem.GetCell(x, y);
                if (!cell) continue;

                glm::vec2 pos = { x * 30, y * 30 };
                glm::vec2 nextPos = { (x + 1) * 30, (y + 1) * 30 };


                if (cell->isStaticWall) {
                    engineContext.renderManager->DrawLine(pos, nextPos, { 1, 0, 0, 0.6f }, 2.0f);
                    engineContext.renderManager->DrawLine({ pos.x + 30, pos.y }, { pos.x, pos.y + 30 }, { 1, 0, 0, 0.6f }, 2.0f);
                }

    
                if (cell->word != BABO::Logic::WordType::None) {
                    glm::vec4 color = { 1, 1, 1, 1 }; 
                    if (cell->word == BABO::Logic::WordType::PLAYER) color = { 0, 1, 0, 1 }; 
                    if (cell->word == BABO::Logic::WordType::YOU)    color = { 1, 1, 0, 1 }; 

     
                    float margin = 10.0f;
                    engineContext.renderManager->DrawLine({ pos.x + margin, pos.y + margin }, { pos.x + 30 - margin, pos.y + margin }, color, 2.0f);
                    engineContext.renderManager->DrawLine({ pos.x + margin, pos.y + 30 - margin }, { pos.x + 30 - margin, pos.y + 30 - margin }, color, 2.0f);
                }
            }
        }
    }

    // 3. 실제 게임 객체들 그리기
    objectManager.DrawAll(engineContext);
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

    //Player Obj
    player = static_cast<Player*>(objectManager.AddObject(std::make_unique<Player>(), "[Object]player"));
    player->SetRenderLayer("[Layer]Player");

    //Floor Obj
    frObj00 = static_cast<TileObject*>(objectManager.AddObject(std::make_unique<TileObject>(), "[Object]frObj00"));
    frObj00->SetMaterial(engineContext, "[Material]Background08");
    frObj00->SetRenderLayer("[Layer]Tile");
    frObj00->SetFactor(0.0);
    frObj00->SetColor(glm::vec4(0, 0, 1, 1));
    frObj00->GetTransform2D().SetScale(glm::vec2(100.f));
    frObj00->SetMesh(engineContext, "[EngineMesh]default");

    //Obj Depth
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

    frObj00->GetTransform2D().SetDepth(00.0f);

    //Cursor
    cursor = static_cast<GameObject*>(objectManager.AddObject(std::make_unique<GameObject>(), "[Object]cursor"));
    cursor->SetMaterial(engineContext, "[Material]cursor");
    cursor->SetMesh(engineContext, "[EngineMesh]default");
    cursor->GetTransform2D().SetScale({ 30,30 });
    cursor->SetRenderLayer("[Layer]Cursor");
    cursor->SetIgnoreCamera(true, cameraManager.GetActiveCamera());

    //Floor Collider
    float colHeight = 250.f;
    auto frCol = std::make_unique<AABBCollider>(frObj00, glm::vec2(1.0, 1.0));
    frCol->SetUseTransformScale(false);
    frCol->SetSize({ engineContext.windowManager->GetWidth(), colHeight });
    frCol->SetOffset({ glm::vec2(0,(-engineContext.windowManager->GetHeight() / 2) + (colHeight / 2)) });
    frObj00->SetCollider(std::move(frCol));
    frObj00->SetCollision(engineContext.stateManager->GetCurrentState()->GetObjectManager(), "[CollisionTag]player", { "[CollisionTag]flag" });

    //BGM
    engineContext.soundManager->Play("BGM_Main", 1, 0);

    //Resolution
    int w = engineContext.windowManager->GetWidth();
    int h = engineContext.windowManager->GetHeight();
    int newH = w * 720.f / 1280.f;

    //Scale
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
    frObj00->GetTransform2D().SetScale({ w, newH });
    player->GetTransform2D().SetPosition(glm::vec2(0, h * 160.f / 720.f - h / 2.f));
}
void Level::LateInit(const EngineContext& engineContext)
{
}
void Level::Free(const EngineContext& engineContext)
{
    engineContext.windowManager->RemoveResizeCallback("[PostFX]WaterDrop");
    JIN_LOG("[Level] free called");
}

void Level::Unload(const EngineContext& engineContext)
{
    for (int i = 0; i < 10; i++)
    {
        engineContext.renderManager->UnregisterTexture("test" + std::to_string(i), engineContext);
    }

    JIN_LOG("[Level] unload called");
}

void Level::CreateDefaultLevel(const std::string& path)
{

    BABO::World::GridSystem temp;
    temp.Resize(42, 24);

 
    std::vector<BABO::IO::EntityData> ents;
    std::vector<std::string> tags;
    BABO::IO::EntityData p;
    p.id = 1;
    p.type = 0;
    p.x = BABO::Math::Fix64(60.0f).Raw();
    p.y = BABO::Math::Fix64(60.0f).Raw();

    ents.push_back(p);
    tags.push_back("Player"); 
    BABO::IO::LevelSerializer::Save(path, temp, ents, tags);


}

#else
#include "Level.h"
#include "Core/LevelSerializer.h"
#include "Engine.h"
#include "MainMenu.h"

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
#endif
