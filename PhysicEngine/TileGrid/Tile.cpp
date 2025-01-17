//#include "Tile.h"
//#include <iostream>
//
//Tile::Tile() : count(), currentIndex(0) {}
//
//Tile::~Tile() {
//    if (File.is_open()) {
//        File.close();
//    }
//}
//void Tile::ReadDataFromFile(const std::string& filepath) {
//    this->File.open(CleanFilePath(filepath));
//    char buffer;
//
//    if (!this->File.is_open()) {
//        std::cerr << "Error: Failed to open file: " << filepath << "\n";
//        return;
//    }
//
//    this->tilePlaceData.clear();
//    this->currentIndex = 0;
//
//    while (this->File.get(buffer)) {
//        if (buffer == '\n' || buffer == '\r') {
//            continue;
//        }
//        if (buffer == ' ') { this->currentIndex++; continue; }
//
//        UniqueTile tile;
//        unsigned int entityId = this->count.GetEntityId(buffer);
//        this->count.IncrementAtId(entityId);
//
//        tile.gridindex = this->currentIndex;
//        tile.tilecharacter = buffer;
//        this->tilePlaceData.push_back(tile);
//
//        this->currentIndex++;
//    }
//    this->File.close();
//    std::cout << "Total entity count: " << this->count.TotalCount() << "\n";
//    for (unsigned int i = 0; i < this->count.GetSize(); ++i) {
//        std::cout << "Entity ID " << i << " count: " << this->count.SpecificCount(i) << "\n";
//    }
//    for (int i = 0; i < this->tilePlaceData.size(); ++i) {
//        std::cout << " char = " << this->tilePlaceData[i].tilecharacter << "   at index = "
//            << this->tilePlaceData[i].gridindex << "\n";
//    }
//    std::cout << "last index = " << this->currentIndex << "\n";
// }
//
//std::string Tile::CleanFilePath(const std::string& path){
//    std::string cleanPath = path;
//    cleanPath.erase(std::remove(cleanPath.begin(), cleanPath.end(), ' '), cleanPath.end());
//    return cleanPath;
//}
