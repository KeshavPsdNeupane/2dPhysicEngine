#include "TileResource.h"
#include <algorithm>

TileResource::TileResource() {}

TileResource::~TileResource() {}

TotalTileData& TileResource::ListTheEntity(const std::string& filepath) {
    std::fstream file;
    file.open(RemoveSpaces(filepath), std::ios::in);
    if (!file.is_open()) {
        std::cerr << "File not found" << std::endl;
        exit(1);
    }

    int TotalEntityCount = 0, worldWidth = 0, worldHeight = 0, tileWidth = 0, tileHeight = 0;
    std::string stringbuffer;

    // Read the total entity count, world width, world height, tile width, tile height
    file >> stringbuffer >> TotalEntityCount >> stringbuffer >> worldWidth
        >> stringbuffer >> worldHeight >> stringbuffer >> tileWidth >> stringbuffer >> tileHeight;
    std::getline(file, stringbuffer); // Move to next line
    this->totalTileData.TotatEntityCount = TotalEntityCount;
    this->totalTileData.worldWidth = worldWidth;
    this->totalTileData.worldHeight = worldHeight;
    this->totalTileData.tileWidth = tileWidth;
    this->totalTileData.tileHeight = tileHeight;

    // Read the entity count of each entity
    int Playercount = 0, GroundCount = 0,
        StaticEnemyCount = 0, StaticEnemySCount = 0,
        DynamicEnemyCount = 0, InvisibleCount = 0,
        InfilatorCount = 0, DefilatorCount = 0,
        CheckPointCount = 0, BouncyPaCountd = 0,
        CoinCount = 0, EndGameMarkerCount = 0;

    file >> stringbuffer >> Playercount
        >> stringbuffer >> GroundCount
        >> stringbuffer >> StaticEnemyCount
        >> stringbuffer >> StaticEnemySCount
        >> stringbuffer >> DynamicEnemyCount
        >> stringbuffer >> InvisibleCount
        >> stringbuffer >> InfilatorCount
        >> stringbuffer >> DefilatorCount
        >> stringbuffer >> CheckPointCount
        >> stringbuffer >> BouncyPaCountd
        >> stringbuffer >> CoinCount
        >> stringbuffer >> EndGameMarkerCount;

    std::getline(file, stringbuffer); // Move to next line
    this->totalTileData.loadEntity[EntityId::player].reserve(Playercount);
    this->totalTileData.loadEntity[EntityId::path].reserve(GroundCount);
    this->totalTileData.loadEntity[EntityId::staticEnemy].reserve(StaticEnemyCount);
    this->totalTileData.loadEntity[EntityId::staticEnemyS].reserve(StaticEnemySCount);
    this->totalTileData.loadEntity[EntityId::dynamicEnemy].reserve(DynamicEnemyCount);
    this->totalTileData.loadEntity[EntityId::invisibleEnemy].reserve(InvisibleCount);
    this->totalTileData.loadEntity[EntityId::inflator].reserve(InfilatorCount);
    this->totalTileData.loadEntity[EntityId::deflator].reserve(DefilatorCount);
    this->totalTileData.loadEntity[EntityId::checkPoint].reserve(CheckPointCount);
    this->totalTileData.loadEntity[EntityId::bouncypad].reserve(BouncyPaCountd);
    this->totalTileData.loadEntity[EntityId::collectable].reserve(CoinCount);
    this->totalTileData.loadEntity[EntityId::EndGameMarker].reserve(EndGameMarkerCount);

    // Read the entity data
    std::string entityName;
    int TextureIndex = 0, PixelX = 0, PixelY = 0;
    while (file >> entityName >> TextureIndex >> PixelX >> PixelY) {
        EntityId entityId = static_cast<EntityId>(this->entity.GetEntityId(entityName));
        if (entityId == EntityId::none) {
            std::cerr << "Entity not found: " << entityName << std::endl;
            continue;
        }
        this->totalTileData.loadEntity[entityId].push_back({ TextureIndex - 1, PixelX, PixelY });
    }
    file.close();
    return this->totalTileData;
}

std::string TileResource::RemoveSpaces(const std::string& input) {
    std::string result = input;
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    return result;
}

