#include "TileManager.h"
#include "GameTypes.h"
#include "Core/LevelSerializer.h"


void TileState::AsyncLoad(const EngineContext& engineContext, LoadingState* loading)
{
    // Tiles
    loading->QueueTexture(engineContext, "[Texture]Floor00", "Textures/Tiles/1.png");
    loading->QueueTexture(engineContext, "[Texture]Floor01", "Textures/Tiles/2.png");
    loading->QueueTexture(engineContext, "[Texture]Floor02", "Textures/Tiles/3.png");
    loading->QueueTexture(engineContext, "[Texture]Floor03", "Textures/Tiles/4.png");
    loading->QueueTexture(engineContext, "[Texture]Floor04", "Textures/Tiles/5.png");
    loading->QueueTexture(engineContext, "[Texture]Floor05", "Textures/Tiles/6.png");
    loading->QueueTexture(engineContext, "[Texture]Floor06", "Textures/Tiles/7.png");
    loading->QueueTexture(engineContext, "[Texture]Floor07", "Textures/Tiles/8.png");
    loading->QueueTexture(engineContext, "[Texture]Floor08", "Textures/Tiles/9.png");
    loading->QueueTexture(engineContext, "[Texture]Floor09", "Textures/Tiles/10.png");
    loading->QueueTexture(engineContext, "[Texture]Floor10", "Textures/Tiles/11.png");
    loading->QueueTexture(engineContext, "[Texture]Floor11", "Textures/Tiles/12.png");
    loading->QueueTexture(engineContext, "[Texture]Floor12", "Textures/Tiles/13.png");
    loading->QueueTexture(engineContext, "[Texture]Floor13", "Textures/Tiles/14.png");
    loading->QueueTexture(engineContext, "[Texture]Floor14", "Textures/Tiles/15.png");
    loading->QueueTexture(engineContext, "[Texture]Floor15", "Textures/Tiles/16.png");
    loading->QueueTexture(engineContext, "[Texture]Water00", "Textures/Tiles/17.png");
    loading->QueueTexture(engineContext, "[Texture]Water01", "Textures/Tiles/18.png");

    // Object Tiles
    loading->QueueTexture(engineContext, "[Texture]Babo00", "Textures/Object/Babo_1.png"); // player = babo
    loading->QueueTexture(engineContext, "[Texture]Babo01", "Textures/Object/Babo_2.png");
    loading->QueueTexture(engineContext, "[Texture]Box00", "Textures/Object/Crate.png"); // box
    loading->QueueTexture(engineContext, "[Texture]Stone00", "Textures/Object/Stone.png"); // wall

    // Environment Tiles << not collision
    loading->QueueTexture(engineContext, "[Texture]Bush00", "Textures/Environment/Bush_1.png");
    loading->QueueTexture(engineContext, "[Texture]Bush01", "Textures/Environment/Bush_2.png");
    loading->QueueTexture(engineContext, "[Texture]Bush02", "Textures/Environment/Bush_3.png");
    loading->QueueTexture(engineContext, "[Texture]Bush03", "Textures/Environment/Bush_4.png");
    loading->QueueTexture(engineContext, "[Texture]Sign00", "Textures/Environment/Sign_1.png");
    loading->QueueTexture(engineContext, "[Texture]Sign01", "Textures/Environment/Sign_2.png");
    loading->QueueTexture(engineContext, "[Texture]Tree00", "Textures/Environment/Tree_1.png");
    loading->QueueTexture(engineContext, "[Texture]Tree01", "Textures/Environment/Tree_2.png");
    loading->QueueTexture(engineContext, "[Texture]Tree02", "Textures/Environment/Tree_3.png");
}

void TileManager::Load(const EngineContext& engineContext)
{
    RenderManager* rm = engineContext.renderManager;

    // Tiles
    rm->RegisterMaterial("[Material]Floor00", "[EngineShader]default_texture", { {"u_Texture","[Texture]Floor00"} });
    rm->RegisterMaterial("[Material]Floor01", "[EngineShader]default_texture", { {"u_Texture","[Texture]Floor01"} });
    rm->RegisterMaterial("[Material]Floor02", "[EngineShader]default_texture", { {"u_Texture","[Texture]Floor02"} });
    rm->RegisterMaterial("[Material]Floor03", "[EngineShader]default_texture", { {"u_Texture","[Texture]Floor03"} });
    rm->RegisterMaterial("[Material]Floor04", "[EngineShader]default_texture", { {"u_Texture","[Texture]Floor04"} });
    rm->RegisterMaterial("[Material]Floor05", "[EngineShader]default_texture", { {"u_Texture","[Texture]Floor05"} });
    rm->RegisterMaterial("[Material]Floor06", "[EngineShader]default_texture", { {"u_Texture","[Texture]Floor06"} });
    rm->RegisterMaterial("[Material]Floor07", "[EngineShader]default_texture", { {"u_Texture","[Texture]Floor07"} });
    rm->RegisterMaterial("[Material]Floor08", "[EngineShader]default_texture", { {"u_Texture","[Texture]Floor08"} });
    rm->RegisterMaterial("[Material]Floor09", "[EngineShader]default_texture", { {"u_Texture","[Texture]Floor09"} });
    rm->RegisterMaterial("[Material]Floor10", "[EngineShader]default_texture", { {"u_Texture","[Texture]Floor10"} });
    rm->RegisterMaterial("[Material]Floor11", "[EngineShader]default_texture", { {"u_Texture","[Texture]Floor11"} });
    rm->RegisterMaterial("[Material]Floor12", "[EngineShader]default_texture", { {"u_Texture","[Texture]Floor12"} });
    rm->RegisterMaterial("[Material]Floor13", "[EngineShader]default_texture", { {"u_Texture","[Texture]Floor13"} });
    rm->RegisterMaterial("[Material]Floor14", "[EngineShader]default_texture", { {"u_Texture","[Texture]Floor14"} });
    rm->RegisterMaterial("[Material]Floor15", "[EngineShader]default_texture", { {"u_Texture","[Texture]Floor15"} });
    rm->RegisterMaterial("[Material]Water00", "[EngineShader]default_texture", { {"u_Texture","[Texture]Water00"} });
    rm->RegisterMaterial("[Material]Water01", "[EngineShader]default_texture", { {"u_Texture","[Texture]Water01"} });

    // Object Tiles
    rm->RegisterMaterial("[Material]Babo00", "[EngineShader]default_texture", { {"u_Texture","[Texture]Babo00"} });
    rm->RegisterMaterial("[Material]Babo01", "[EngineShader]default_texture", { {"u_Texture","[Texture]Babo01"} });
    rm->RegisterMaterial("[Material]Box00", "[EngineShader]default_texture", { {"u_Texture","[Texture]Box00"} });
    rm->RegisterMaterial("[Material]Stone00", "[EngineShader]default_texture", { {"u_Texture","[Texture]Stone00"} });

    // Environment Tiles << not collision
    rm->RegisterMaterial("[Material]Bush00", "[EngineShader]default_texture", { {"u_Texture","[Texture]Bush00"} });
    rm->RegisterMaterial("[Material]Bush01", "[EngineShader]default_texture", { {"u_Texture","[Texture]Bush01"} });
    rm->RegisterMaterial("[Material]Bush02", "[EngineShader]default_texture", { {"u_Texture","[Texture]Bush02"} });
    rm->RegisterMaterial("[Material]Bush03", "[EngineShader]default_texture", { {"u_Texture","[Texture]Bush03"} });
    rm->RegisterMaterial("[Material]Sign00", "[EngineShader]default_texture", { {"u_Texture","[Texture]Sign00"} });
    rm->RegisterMaterial("[Material]Sign01", "[EngineShader]default_texture", { {"u_Texture","[Texture]Sign01"} });
    rm->RegisterMaterial("[Material]Tree00", "[EngineShader]default_texture", { {"u_Texture","[Texture]Tree00"} });
    rm->RegisterMaterial("[Material]Tree01", "[EngineShader]default_texture", { {"u_Texture","[Texture]Tree01"} });
    rm->RegisterMaterial("[Material]Tree02", "[EngineShader]default_texture", { {"u_Texture","[Texture]Tree02"} });
}

void TileManager::Init(const EngineContext& engineContext)
{

    //Player Obj
    /*player = static_cast<TileObject*>(objectManager.AddObject(std::make_unique<TileObject>(), "[Object]player00"));
    player->SetRenderLayer("[Layer]Player");*/

    //Floor Obj
    /*frObj00 = static_cast<TileObject*>(objectManager.AddObject(std::make_unique<TileObject>(), "[Object]floor00"));
    frObj00->SetColor(glm::vec4(0, 0, 1, 1));
    frObj00->SetMesh(engineContext, "[EngineMesh]default");*/


    //Floor Collider
   /* float colHeight = engineContext.windowManager->GetHeight() / 4.5;
    auto frCol = std::make_unique<AABBCollider>(frObj00, glm::vec2(1.0, 1.0));
    frCol->SetUseTransformScale(false);
    frCol->SetSize({ engineContext.windowManager->GetWidth(), colHeight });
    frCol->SetOffset({ glm::vec2(0,(-engineContext.windowManager->GetHeight() / 2) + (colHeight / 2)) });
    frObj00->SetCollider(std::move(frCol));
    frObj00->SetCollision(engineContext.stateManager->GetCurrentState()->GetObjectManager(), "[CollisionTag]tile", { "[CollisionTag]player" });*/

}

void TileManager::LateInit(const EngineContext& engineContext)
{
}

void TileManager::Update(float dt, const EngineContext& engineContext)
{
    /*if (engineContext.inputManager->IsKeyPressed(KEY_1))
    {
        player->PlayerMove(Player::PlayerMoveType::LEFT, engineContext);
    }
    if (engineContext.inputManager->IsKeyPressed(KEY_2))
    {
        player->PlayerMove(Player::PlayerMoveType::RIGHT, engineContext);
    }
    if (engineContext.inputManager->IsKeyPressed(KEY_3))
    {
        player->PlayerMove(Player::PlayerMoveType::UP, engineContext);
    }*/
}

void TileManager::LateUpdate(float dt, const EngineContext& engineContext)
{
}

void TileManager::Draw(const EngineContext& engineContext)
{

}

void TileManager::Free(const EngineContext& engineContext)
{
}

void TileManager::Unload(const EngineContext& engineContext)
{
}



void TileManager::SyncToLogicGrid(BABO::World::GridSystem& grid, ObjectManager& objectManager) {
  
    grid.Reset();


    for (auto* obj : objectManager.GetAllRawPtrObjects()) {

        if (!obj || !obj->IsAlive()) continue;


        glm::vec2 pos = obj->GetTransform2D().GetPosition();

        BABO::World::GridPoint gp = grid.WorldToGrid(BABO::Math::Fix64(pos.x), BABO::Math::Fix64(pos.y));


        BABO::World::Cell* cell = grid.GetCell(gp.x, gp.y);

        if (cell) {

            const std::string& tag = obj->GetTag();

  
            if (WordDictionary::IsSubject(tag))      cell->wordType = WordType::Subject;
            else if (WordDictionary::IsVerb(tag))    cell->wordType = WordType::Verb;
            else if (WordDictionary::IsObject(tag))  cell->wordType = WordType::Object;

            if (tag == "Wall") {
                cell->isStaticWall = true;
            }


        }
    }
}
void TileManager::SaveCurrentLevel(const std::string& path, BABO::World::GridSystem& grid, ObjectManager& objectManager) {
    std::vector<BABO::IO::EntityData> entities;
    std::vector<std::string> tags;

    for (auto* obj : objectManager.GetAllRawPtrObjects()) {
        if (!obj || !obj->IsAlive()) continue;

        BABO::IO::EntityData data;
        // Babo 태그면 type 0, 나머지는 1로 설정 (기존 저장 규칙)
        data.type = (obj->GetTag() == "Babo") ? 0 : 1;

        // Fix64 Raw 데이터로 좌표 저장
        glm::vec2 pos = obj->GetTransform2D().GetPosition();
        data.x = BABO::Math::Fix64(pos.x).Raw();
        data.y = BABO::Math::Fix64(pos.y).Raw();

        entities.push_back(data);
        tags.push_back(obj->GetTag());
    }

    BABO::IO::LevelSerializer::Save(path, grid, entities, tags);
}

void TileManager::CreateDefaultLevel(const std::string& path) {
    BABO::World::GridSystem defaultGrid;
    defaultGrid.Resize(42, 24); //

    std::vector<BABO::IO::EntityData> entities;
    std::vector<std::string> tags;

    BABO::IO::EntityData baboData;
    baboData.type = 0;
    baboData.x = BABO::Math::Fix64(60.0f).Raw();
    baboData.y = BABO::Math::Fix64(60.0f).Raw();

    entities.push_back(baboData);
    tags.push_back("Babo");

    BABO::IO::LevelSerializer::Save(path, defaultGrid, entities, tags);
}

