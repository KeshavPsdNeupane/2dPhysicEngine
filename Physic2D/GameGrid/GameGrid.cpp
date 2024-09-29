
#include "GameGrid.h"
#include <cmath>
GameGrid::GameGrid() {
    gridVisual.reserve(static_cast<int>(GMNumber::GRID_COUNT_X * GMNumber::GRID_COUNT_Y));  // Reserve space for grid visuals
    gridCell.resize(static_cast<int>(GMNumber::GRID_COUNT_X * GMNumber::GRID_COUNT_Y));     // Resize the grid cells
    VisualGridInit();
}

void GameGrid::AddObject(std::shared_ptr<sf::RectangleShape> rect, const int& id) {
    auto pos = rect->getPosition();
    std::cout << " position = " << pos.x << " " << pos.y << std::endl;
    int index = GetIndex(pos);
    std::cout << "index = " << index << std::endl;
    AddObjectAtIndex(rect, id, index);
}

void GameGrid::RemoveObject(std::shared_ptr<sf::RectangleShape> rect, const int& id) {
    auto pos = rect->getPosition();
    int index = GetIndex(pos);
    RemoveObjectAtIndex(id, index);
}

std::vector<std::shared_ptr<sf::RectangleShape>> GameGrid::PotentialCollision(std::shared_ptr<sf::RectangleShape> rect, const int& id) {
    auto pos = rect->getPosition();
    auto objectGridNumber = GetGridNumber(pos);
    std::vector<std::shared_ptr<sf::RectangleShape>> potentialCollider;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            sf::Vector2i potentialGridNumber = objectGridNumber + sf::Vector2i(i, j);
            if ((potentialGridNumber.x >= 0 && potentialGridNumber.x < GMNumber::GRID_COUNT_X)
                && potentialGridNumber.y >= 0 && potentialGridNumber.y < GMNumber::GRID_COUNT_Y) {
                int tempIndex = GetIndex(potentialGridNumber);
                for (const auto& obj : gridCell[tempIndex]) {
                    if (obj.ID != id) {
                        potentialCollider.push_back(obj.Object);
                    }
                }

            }
        }
    }
    return potentialCollider;
}

void GameGrid::MoveObject(std::shared_ptr<sf::RectangleShape> rect, const sf::Vector2f& oldPosition, const int& id) {
    auto newPos = rect->getPosition();
    int oldIndex = GetIndex(oldPosition);
    int newIndex = GetIndex(newPos);

    // DONT REMOVE THIS IS NEEDED FOR DEBUGGING 
    //if (oldIndex == newIndex) {
    //  //std::cout << " same as old " << std::endl << std::endl;
    //  auto& gridObjects = gridCell[oldIndex];
    //  for (auto& obj : gridObjects) {
    //      if (obj.ID == id) {
    //          auto pos = obj.Object->getPosition();
    //          std::cout << " Position in grid = " << pos.x << " " << pos.y << std::endl;
    //          break;
    //      }
    //  }
    //  return;
    //}

    if (oldIndex != newIndex) {
        // std::cout << "  different old index = "<< oldIndex << " NewIndex = " << newIndex << std::endl << std::endl;
        RemoveObjectAtIndex(oldIndex, id);
        AddObjectAtIndex(rect, id, newIndex);
    }
}

void GameGrid::Draw(std::shared_ptr<sf::RenderWindow> window) {
    for (int i = 0; i < gridVisual.size(); ++i) {
        window->draw(*gridVisual[i]);  // Draw each visual grid cell
    }
}

void GameGrid::VisualGridInit() {
    for (int y = 0; y < GMNumber::GRID_COUNT_Y; ++y) {
        for (int x = 0; x < GMNumber::GRID_COUNT_X; ++x) {
            int index = x + y * (int)GMNumber::GRID_COUNT_X;
            //std::cout << " index = " << index << std::endl;
            std::shared_ptr<sf::RectangleShape> Trect = std::make_shared<sf::RectangleShape>();
            Trect->setSize(sf::Vector2f(GMNumber::BASE_GRID_SIZE_X, GMNumber::BASE_GRID_SIZE_Y));
            Trect->setPosition(x * GMNumber::BASE_GRID_SIZE_X, y * GMNumber::BASE_GRID_SIZE_Y);
            Trect->setOutlineThickness(.5f);
            Trect->setOutlineColor(sf::Color(165, 42, 42, 128));  // Brownish color with transparency
            Trect->setFillColor(sf::Color::Transparent);
            gridVisual.push_back(Trect);  // Store visual part of grid
            gridCell[index] = std::vector<GridObject>();  // Initialize grid cell for objects
            //sf::Vector2f pos = Trect->getPosition();
            //std::cout << "positions = " << pos.x << " " << pos.y << std::endl << std::endl;
        }
    }
}

inline int GameGrid::GetIndex(sf::Vector2f pos) {
    int x = Floor(pos.x / GMNumber::BASE_GRID_SIZE_X);
    int y = Floor(pos.y / GMNumber::BASE_GRID_SIZE_Y);
    return x + y * (int)GMNumber::GRID_COUNT_X;
}

inline int GameGrid::GetIndex(sf::Vector2i oldIndex) {
    return oldIndex.x + oldIndex.y * (int)GMNumber::GRID_COUNT_X;
}

inline sf::Vector2i GameGrid::GetGridNumber(sf::Vector2f pos) {
    int x = Floor(pos.x / GMNumber::BASE_GRID_SIZE_X);
    int y = Floor(pos.y / GMNumber::BASE_GRID_SIZE_Y);
    return { x, y };
}

void GameGrid::AddObjectAtIndex(const std::shared_ptr<sf::RectangleShape>& rect, const int& id, const int& index) {
    if (index >= 0 && index < gridCell.size()) {
        GridObject object(id, rect);
        object.previousGridId = index;
        gridCell[index].push_back(object);  // Add object to the appropriate grid cell
    }
    else {
       // std::cerr << "Error: Calculated grid index (" << index << ") is out of bounds!" << std::endl;
    }
}

void GameGrid::RemoveObjectAtIndex(const int& id, const int& index) {
    if (index >= 0 && index < gridCell.size()) {
        auto& objects = gridCell[index];
        objects.erase(std::remove_if(objects.begin(), objects.end(),
            [id](const GridObject& obj) { return obj.ID == id; }), objects.end());  // Remove object by ID
    }
    else {
       // std::cerr << "Error: Calculated grid index (" << index << ") is out of bounds!" << std::endl;
    }
}