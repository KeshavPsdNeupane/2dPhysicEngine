//#pragma once
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <fstream>
//#include <array>
//#include <string>
//#include <vector>
//
//struct Entity {
//    const static char Player = '!';
//    const static char path = '@';
//    const static char invisiblEnemy = '#';
//    const static char rightEnemy = '$';
//    const static char leftEnemy = '%';
//    const static char staticEnemy = '^';
//    const static char bouncypad = '&';
//    const static char collectable = '*';
//    const static char Inflator = '(';
//    const static char deflator = ')';
//    const static char checkPoint = '-';
//};
//
//enum EntityId {
//    none = -1,
//    player = 0,
//    path,
//    invisiblEnemy,
//    rightEnemy,
//    leftEnemy,
//    staticEnemy,
//    bouncypad,
//    collectable,
//    inflator,
//    deflator,
//    checkPoint,
//    maxEntityCount
//};
//
//class Count {
//private:
//    std::array<unsigned int, EntityId::maxEntityCount> count = { 0 };
//public:
//    Count() = default;
//    ~Count() {}
//
//    unsigned int TotalCount() const {
//        unsigned int total = 0;
//        for (unsigned int i = 0; i < count.size(); ++i) {
//            total += count[i];
//        }
//        return total;
//    }
//
//    unsigned int SpecificCount(unsigned int id) const {
//        return count.at(id);
//    }
//
//    void IncrementAtId(unsigned int id) {
//        if (id != EntityId::none) {
//            ++count.at(id);
//        }
//    }
//
//    unsigned int GetSize() const {
//        return static_cast<unsigned int>(count.size());
//    }
//
//    unsigned int GetEntityId(const char& c) const {
//        switch (c) {
//        case '!': return EntityId::player;
//        case '@': return EntityId::path;
//        case '#': return EntityId::invisiblEnemy;
//        case '&': return EntityId::bouncypad;
//        case '^': return EntityId::staticEnemy;
//        case '*': return EntityId::collectable;
//        case '(': return EntityId::inflator;
//        case ')': return EntityId::deflator;
//        case '-': return EntityId::checkPoint;
//        default:
//            std::cerr << "Warning: Unknown entity character '" << c << "'\n";
//            return EntityId::none;
//        }
//    }
//};
////
////struct UniqueTile {
////    char tileCharacter = ' ';
////    TilePosition tilePosition;
////};
////
////class TileResource {
////private:
////    std::vector<UniqueTile> uniqueTiles;
////    Count entityCount;
////
////public:
////    TileResource(const std::vector<TilePosition>& tilePositions) {
////        for (const auto& tilePos : tilePositions) {
////            char tileChar = GetTileCharacter(tilePos.tileIndex);
////            unsigned int entityId = entityCount.GetEntityId(tileChar);
////            if (entityId != EntityId::none) {
////                entityCount.IncrementAtId(entityId);
////                uniqueTiles.push_back({ tileChar, tilePos });
////            }
////        }
////    }
////
////    const std::vector<UniqueTile>& GetUniqueTiles() const {
////        return uniqueTiles;
////    }
////
////    const Count& GetEntityCount() const {
////        return entityCount;
////    }
////
////private:
////    char GetTileCharacter(int tileIndex) const {
////        // Map tileIndex to the corresponding character
////        // This mapping should be defined based on your specific tile set
////        switch (tileIndex) {
////        case 1: return Entity::Player;
////        case 2: return Entity::path;
////        case 3: return Entity::invisiblEnemy;
////        case 4: return Entity::rightEnemy;
////        case 5: return Entity::leftEnemy;
////        case 6: return Entity::staticEnemy;
////        case 7: return Entity::bouncypad;
////        case 8: return Entity::collectable;
////        case 9: return Entity::Inflator;
////        case 10: return Entity::deflator;
////        case 11: return Entity::checkPoint;
////        default: return ' ';
////        }
////    }
////};
