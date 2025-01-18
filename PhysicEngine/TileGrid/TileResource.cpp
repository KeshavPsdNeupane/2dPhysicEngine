#include "TileResource.h"

TileResource::TileResource(){}

TileResource::~TileResource(){}

TotalTileData& TileResource::ListTheEntity(std::string& filepath) {
	std::fstream file;
	file.open(RemoveSpaces(filepath), std::ios::in);
	if (!file.is_open()) {
		std::cout << "File not found" << std::endl;
		exit(1);
	}
	int TotalEntityCount = 0, worldWidth = 0, worldHeight = 0, tileWidth = 0, tileHeight = 0;
	std::string stringbuffer;
	//HERE FIRST WE READ THE TOTAL ENTITY COUNT, WORLD WIDTH, WORLD HEIGHT, TILE WIDTH, TILE HEIGHT
	//THIS WILL GIVE INFO ABOUT THE WORLD
	file >> stringbuffer >> TotalEntityCount >> stringbuffer >> worldWidth
		>> stringbuffer >> worldHeight >> stringbuffer >> tileWidth >> stringbuffer >> tileHeight;
	std::getline(file, stringbuffer); // TO MOVE TO NEXT LINE
	this->totalTileData.TotatEntityCount = TotalEntityCount;
	this->totalTileData.worldWidth = worldWidth;
	this->totalTileData.worldHeight = worldHeight;
	this->totalTileData.tileWidth = tileWidth;
	this->totalTileData.tileHeight = tileHeight;

	//HERE WE READ THE ENTITY COUNT OF EACH ENTITY
	//FOR RESERVE THE MEMORY IN VECTOR
	int GroundCount = 0, EnemyCount = 0, InfilatorCount = 0, DefilatorCount = 0
		, CheckPointCount = 0, BouncyPaCountd = 0, CoinCount = 0;
	file >> stringbuffer >> GroundCount >> stringbuffer >> EnemyCount >> stringbuffer >> InfilatorCount
		>> stringbuffer >> DefilatorCount >> stringbuffer >> CheckPointCount >> stringbuffer >> BouncyPaCountd
		>> stringbuffer >> CoinCount;
	std::getline(file, stringbuffer); // TO MOVE TO NEXT LINE
	this->totalTileData.loadEntity[EntityId::path].reserve(GroundCount);
	this->totalTileData.loadEntity[EntityId::staticEnemy].reserve(EnemyCount);
	this->totalTileData.loadEntity[EntityId::inflator].reserve(InfilatorCount);
	this->totalTileData.loadEntity[EntityId::deflator].reserve(DefilatorCount);
	this->totalTileData.loadEntity[EntityId::checkPoint].reserve(CheckPointCount);
	this->totalTileData.loadEntity[EntityId::bouncypad].reserve(BouncyPaCountd);
	this->totalTileData.loadEntity[EntityId::collectable].reserve(CoinCount);




	//HERE WE READ THE ENTITY DATA
	//WE READ THE ENTITY NAME, TEXTURE INDEX, PIXEL X, PIXEL Y
	//WE STORE THE DATA IN VECTOR THE WE RESIZED ABOVE
	std::string entityName;
	int TextureIndex = 0, PixelX = 0, PixelY = 0;
	while (file >> entityName >> TextureIndex >> PixelX >> PixelY) {
		unsigned int entityId = this->entity.GetEntityId(entityName);
		if (entityId == EntityId::none) {
			std::cout << "Entity not found" << std::endl;
			continue;
		}
		this->totalTileData.loadEntity[entityId].push_back({ TextureIndex - 1, PixelX, PixelY });
	}
	file.close();
	return this->totalTileData;
}

std::string TileResource::RemoveSpaces(const std::string& input){
	std::string result = input;
	result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
	return result;
}
