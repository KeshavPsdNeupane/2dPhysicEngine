#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <vector>

enum EntityId {
    player = 0,
    path,
    staticEnemy,
    staticEnemyS,
    dynamicEnemy,
    invisibleEnemy,
    bouncypad,
    collectable,
    inflator,
    deflator,
    checkPoint,
    EndGameMarker,
    maxEntityCount,
    none,
};

struct StringEntity {
    const std::string player = "Player";
    const std::string path = "Ground";
    const std::string staticEnemy = "StaticEnemy";
    const std::string staticEnemyS = "StaticEnemyS";
    const std::string dynamicEnemy = "DynamicEnemy";
    const std::string invisibleEnemy = "InvisibleEnemy";
    const std::string bouncypad = "BouncyPad";
    const std::string collectable = "Coin";
    const std::string Inflator = "Infilator";
    const std::string deflator = "Defilator";
    const std::string checkPoint = "CheckPoint";
    const std::string endGameMarker = "EndGameMarker";




    unsigned int GetEntityId(const std::string& entity) {
        if (entity == player) {
            return EntityId::player;
        }
        else if (entity == path) {
            return EntityId::path;
        }
        else if (entity == staticEnemy) {
            return EntityId::staticEnemy;
        }
        else if (entity == staticEnemyS) {
            return EntityId::staticEnemyS;
        }
        else if (entity == dynamicEnemy) {
            return EntityId::dynamicEnemy;
        }
        else if (entity == invisibleEnemy) {
            return EntityId::invisibleEnemy;
        }
        else if (entity == bouncypad) {
            return EntityId::bouncypad;
        }
        else if (entity == collectable) {
            return EntityId::collectable;
        }
        else if (entity == Inflator) {
            return EntityId::inflator;
        }
        else if (entity == deflator) {
            return EntityId::deflator;
        }
        else if (entity == checkPoint) {
            return EntityId::checkPoint;
        }
		else if (entity == endGameMarker) {
			return EntityId::EndGameMarker;
		}
        else {
            return EntityId::none;
        }
    }
};

struct Entity {
    int textureIndex = -1;
    int pixelX = 0;
    int pixelY = 0;
};

struct TotalTileData {
    std::vector<std::vector<Entity>> loadEntity;
    int TotatEntityCount;
    int worldWidth;
    int worldHeight;
    int tileWidth;
    int tileHeight;

    TotalTileData() {
        loadEntity.resize(EntityId::maxEntityCount);
        TotatEntityCount = 0;
        worldWidth = 0;
        worldHeight = 0;
        tileWidth = 0;
        tileHeight = 0;
    }
};

class TileResource {
    StringEntity entity;
    TotalTileData totalTileData;
public:
    TileResource();
    ~TileResource();

    TotalTileData& ListTheEntity(const std::string& filepath);

private:
    static std::string RemoveSpaces(const std::string& input);
};

