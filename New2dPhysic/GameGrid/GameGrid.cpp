
#include "GameGrid.h"
#include <cmath>

GameGrid::GameGrid() : 
    offsetsForPlayerCollision{ {
       {0, 0}, {-1, -1}, {-1, 0}, 
       {-1, 1}, {0, -1}, {0, 1},
       {1, -1}, {1, 0}, {1, 1}
   } }
{
    gridVisual.reserve(static_cast<int>(GMNumber::GRID_COUNT_X * GMNumber::GRID_COUNT_Y));
    gridCell.resize(static_cast<int>(GMNumber::GRID_COUNT_X * GMNumber::GRID_COUNT_Y));     
    VisualGridInit();
}

void GameGrid::AddObject(std::shared_ptr<GameShape> shape) {
    auto pos = shape->GetPosition();
    //std::cout << " position = " << pos.x << " " << pos.y << std::endl;
    int index = CalculateIndex(pos);
   // std::cout << "index = " << index << std::endl;
    AddObjectAtIndex(shape, index);

}

void GameGrid::RemoveObject(std::shared_ptr<GameShape> shape) {
    sf::Vector2f pos = shape->GetPosition();
    int index = CalculateIndex(pos);
    int id = shape->GetIndex();
    std::cout << "Remove called " << index << std::endl;
    RemoveObjectAtIndex(id, index);
}

std::vector<std::shared_ptr<GameShape>> GameGrid::PotentialCollision(std::shared_ptr<GameShape> shape) {
    sf::Vector2f pos = shape->GetPosition();
    int id = shape->GetIndex();
    sf::Vector2i objectGridNumber = GetGridNumber(pos);
    std::vector<std::shared_ptr<GameShape>> potentialCollider;
    for (const auto& offset : offsetsForPlayerCollision) {
        sf::Vector2i potentialGridNumber = objectGridNumber + offset;
        if (potentialGridNumber.x >= 0 && potentialGridNumber.x < GMNumber::GRID_COUNT_X &&
            potentialGridNumber.y >= 0 && potentialGridNumber.y < GMNumber::GRID_COUNT_Y) {
            int tempIndex = CalculateIndex(potentialGridNumber);
            for (const auto& obj : gridCell[tempIndex]) {
                if (obj->GetIndex() != id) {
                    potentialCollider.push_back(obj);
                }
            }
        }
    }
    return potentialCollider;
}

void GameGrid::MoveObject(std::shared_ptr<GameShape> shape) {
    sf::Vector2f newPos = shape->GetPosition();
    sf::Vector2f oldPos = shape->GetOldPosition();
    int oldIndex = CalculateIndex(oldPos);
    int newIndex = CalculateIndex(newPos);
    int id = shape->GetIndex();

    // DONT REMOVE THIS IS NEEDED FOR DEBUGGING 
    //if (oldIndex == newIndex) {
    //  //std::cout << " same as old " << std::endl << std::endl;
    //  auto& gridObjects = gridCell[oldIndex];
    //  for (auto& obj : gridObjects) {
    //      if (obj->GetIndex() == id) {
    //          auto pos = obj->GetPosition();
    //          std::cout << " Position in grid = " << pos.x << " " << pos.y << std::endl;
    //          break;
    //      }
    //  }
    //  return;
    //}

    if (oldIndex != newIndex) {
        //std::cout << "  different newIndex = "<< newIndex << " oldIndex = " <<  oldIndex << std::endl;
        RemoveObjectAtIndex(oldIndex, id);
        AddObjectAtIndex(shape , newIndex);
    }
}

void GameGrid::Draw(std::shared_ptr<sf::RenderWindow> window) {
    for (int i = 0; i < gridVisual.size(); ++i) {
        window->draw(*gridVisual[i]); 
    }
}

void GameGrid::ShowGirdObjectCound(){
    int count = 0;
    for (int i = 0; i < gridCell.size(); ++i) {
        count += (int)gridCell[i].size();
    }
    std::cout << " grid object count = " << count << std::endl;
    return;
}

void GameGrid::VisualGridInit() {
    for (int y = 0; y < GMNumber::GRID_COUNT_Y; ++y) {
        for (int x = 0; x < GMNumber::GRID_COUNT_X; ++x) {
            int index = x + y * (int)GMNumber::GRID_COUNT_X;;
            std::shared_ptr<sf::RectangleShape> Trect = std::make_shared<sf::RectangleShape>();
            Trect->setSize(sf::Vector2f(GMNumber::BASE_GRID_SIZE_X, GMNumber::BASE_GRID_SIZE_Y));
            Trect->setPosition(x * GMNumber::BASE_GRID_SIZE_X, y * GMNumber::BASE_GRID_SIZE_Y);
            Trect->setOutlineThickness(.5f);
            Trect->setOutlineColor(sf::Color(165, 42, 42, 128));  
            Trect->setFillColor(sf::Color::Transparent);
            gridVisual.push_back(Trect);
            gridCell[index] = std::vector<std::shared_ptr<GameShape>>();
        }
    }
}

inline int GameGrid::CalculateIndex(sf::Vector2f pos) {
    int x = Floor(pos.x / GMNumber::BASE_GRID_SIZE_X);
    int y = Floor(pos.y / GMNumber::BASE_GRID_SIZE_Y);
    return x + y * (int)GMNumber::GRID_COUNT_X;
}

inline int GameGrid::CalculateIndex(sf::Vector2i gridId) {
    return gridId.x + gridId.y * (int)GMNumber::GRID_COUNT_X;
}

inline sf::Vector2i GameGrid::GetGridNumber(sf::Vector2f pos) {
    int x = Floor(pos.x / GMNumber::BASE_GRID_SIZE_X);
    int y = Floor(pos.y / GMNumber::BASE_GRID_SIZE_Y);
    return { x, y };
}

void GameGrid::AddObjectAtIndex(std::shared_ptr<GameShape> shape, const int& index) {
    if (index >= 0 && index < gridCell.size()) {
       // std::cout << "ADD at index " << index << std::endl;
        gridCell[index].push_back(shape);  // Add object to the appropriate grid cell
    }
    else {
        // std::cerr << "Error: Calculated grid index (" << index << ") is out of bounds!" << std::endl;
        return;
    }
}

void GameGrid::RemoveObjectAtIndex(const int& id, const int& index) {
    if (index >= 0 && index < gridCell.size()) {
        auto& shapeVector = gridCell[index];
        shapeVector.erase(std::remove_if(shapeVector.begin(), shapeVector.end(),
            [id](std::shared_ptr<GameShape> obj) { return obj->GetIndex() == id; }), shapeVector.end());
       // std::cout << " removed object at index = " << index << "  " << id << std::endl;
    }
    else {
       // std::cerr << "Error: Calculated grid index (" << index << ") is out of bounds!" << std::endl;
        return;
    }
}