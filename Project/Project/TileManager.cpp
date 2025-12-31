#include "TileManager.h"

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
    loading->QueueTexture(engineContext, "[Texture]Danger00", "Textures/Object/Danger.png"); // player = babo
    loading->QueueTexture(engineContext, "[Texture]Star00", "Textures/Object/Star.png");
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
    rm->RegisterMaterial("[Material]Danger00", "[EngineShader]default_texture", { {"u_Texture","[Texture]Danger00"} });
    rm->RegisterMaterial("[Material]Star00", "[EngineShader]default_texture", { {"u_Texture","[Texture]Star00"} });
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

void TileManager::Init(const EngineContext& engineContext, ObjectManager& om)
{
    //Init om
    objectManager = &om;

    //Init tilemap

    //Tiles Load Part in lv File
    //...

    //*TEST OBJs*
    AddTileObject(engineContext, "[Object]babo00", TileObject::TileType::BABO, {});
    AddTileObject(engineContext, "[Object]floor00", TileObject::TileType::FLOOR, {}, {1,0});
    AddTileObject(engineContext, "[Object]box00", TileObject::TileType::BOX, {}, {2,0});
    AddTileObject(engineContext, "[Object]deadzone00", TileObject::TileType::DEADZONE, {}, {3,0});
    AddTileObject(engineContext, "[Object]wall00", TileObject::TileType::WALL, {}, {4,0});
    AddTileObject(engineContext, "[Object]star00", TileObject::TileType::STAR, {}, {5,0});

}

void TileManager::LateInit(const EngineContext& engineContext)
{
}

void TileManager::Update(float dt, const EngineContext& engineContext)
{
    if (engineContext.inputManager->IsKeyPressed(KEY_A))
    {
        for (TileObject* objs : tileObjects) {
            if (objs->GetTileType() == 0)
            {
                TileMove(*objs, ObjectiveType::LEFT);
            }
        }
    }
    if (engineContext.inputManager->IsKeyPressed(KEY_D))
    {
        for (TileObject* objs : tileObjects) {
            if (objs->GetTileType() == 0)
            {
                TileMove(*objs, ObjectiveType::RIGHT);
            }
        }
    }
    if (engineContext.inputManager->IsKeyPressed(KEY_W))
    {
        for (TileObject* objs : tileObjects) {
            if (objs->GetTileType() == 0)
            {
                TileMove(*objs, ObjectiveType::UP);
            }
        }
    }
}

void TileManager::LateUpdate(float dt, const EngineContext& engineContext)
{
    GravityFunc();
}

void TileManager::Draw(const EngineContext& engineContext)
{

}

void TileManager::Free(const EngineContext& engineContext)
{
    tileObjects.clear();
}

void TileManager::Unload(const EngineContext& engineContext)
{
}

TileObject* TileManager::AddTileObject(const EngineContext& engineContext, const std::string& tag, TileObject::TileType tileType, std::vector<bool> rules, const glm::vec2& defPos)
{
    // Create Object
    TileObject* tileObj = static_cast<TileObject*>(objectManager->AddObject(std::make_unique<TileObject>(), tag));
    // Set TileType
    tileObj->SetTileType(tileType);
    // Set RuleType
    tileObj->SetTileRules(rules);
    // Set Default Postion
    SetTilePosition(engineContext, *tileObj, defPos);

    tileObjects.push_back(tileObj);
    return tileObj;
}

void TileManager::TileMove(TileObject& tileObj, ObjectiveType moveType)
{
    glm::vec2 direction = glm::vec2(0, 0);
    switch (moveType)
    {
    case ObjectiveType::LEFT:
        direction.x = -1;
        tileObj.SetFlipUV_X(true);
        break;
    case ObjectiveType::RIGHT:
        direction.x = 1;
        tileObj.SetFlipUV_X(false);
        break;
    case ObjectiveType::UP:
        direction.y = 1;
        break;
    }
    AddTilePosition(tileObj, direction);
}

bool TileManager::AddTilePosition(TileObject& tileObj, const glm::vec2& pos)
{
    glm::vec2 cord = tileObj.GetCellPos();

    //exam
    if (CheckBlankPosition(cord + pos)) // if BLANK
    {
        //replace
        SetTileTypeInTilemap(cord, TileObject::BLANK);
        cord += pos;
        tileObj.SetCellPos(cord);
        SetTileTypeInTilemap(cord, tileObj.GetTileType());
        tileObj.GetTransform2D().AddPosition(pos * TILE_INTERVAL);

        return true;
    }
    else // if Something have
    {
        //examine pushable
        if(CheckPushable) 
    }
    return false;
}

void TileManager::SetTilePosition(const EngineContext& engineContext, TileObject& tileObj, const glm::vec2& cord)
{
    tileObj.SetCellPos(cord);
    SetTileTypeInTilemap(cord, tileObj.GetTileType());
    int w = engineContext.windowManager->GetWidth();
    int h = engineContext.windowManager->GetHeight();
    glm::vec2 resPos = { 0, 0 };
    glm::vec2 originPos = { 0 + TILE_INTERVAL / 2, h / 2 - TILE_INTERVAL / 2 };
    resPos = originPos + cord * TILE_INTERVAL;
    tileObj.GetTransform2D().SetPosition(resPos);
}

bool TileManager::CheckBlankPosition(const glm::vec2& cord)
{
    return (GetTileTypeInTilemap(cord) == TileObject::TileType::BLANK);
}

bool TileManager::CheckPushable(TileObject& tileObj, const glm::vec2& dir)
{
    //...
    return false;
}

void TileManager::PushTiles(TileObject& tileObj, const glm::vec2& dir)
{
    //...
}

void TileManager::GravityFunc()
{
    //...
    //  If not fixed, Fall until a tile is encountered below.
}
 
void TileManager::SetTileTypeInTilemap(const glm::vec2& cord, TileObject::TileType type)
{
    if (MAX_TILEMAP_SIZE.x <= cord.x || MAX_TILEMAP_SIZE.y <= cord.y) {
        JIN_ERR("Coordinate out of bounds.");
        return;
    }
    tilemap[cord.y * MAX_TILEMAP_SIZE.x + cord.x] = (int)type;
}

TileObject::TileType TileManager::GetTileTypeInTilemap(const glm::vec2& cord)
{
    if (MAX_TILEMAP_SIZE.x <= cord.x || MAX_TILEMAP_SIZE.y <= cord.y) {
        JIN_ERR("Coordinate out of bounds.");
        return TileObject::TileType(0);
    }
    return TileObject::TileType(tilemap[cord.y * MAX_TILEMAP_SIZE.x + cord.x]);
}
