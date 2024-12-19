
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
    staticGridCell.resize(static_cast<int>(GMNumber::GRID_COUNT_X * GMNumber::GRID_COUNT_Y));
    dynamicGridCell.resize(static_cast<int>(GMNumber::GRID_COUNT_X * GMNumber::GRID_COUNT_Y));
    VisualGridInit();
}


void GameGrid::RemoveObject(std::shared_ptr<GameShape> shape, bool isStatic) {
    sf::Vector2f pos = shape->GetPosition();
    int index = CalculateIndex(pos);
    int id = shape->GetShapeID();
    RemoveObjectAtIndex(id, index, isStatic);
}


std::vector<std::shared_ptr<GameShape>> GameGrid::PotentialCollision(std::shared_ptr<GameShape> shape) {
    std::vector<std::shared_ptr<GameShape>> potentialCollider;
    sf::Vector2f pos = shape->GetPosition();
    int id = shape->GetShapeID();
    sf::Vector2i objectGridNumber = GetGridNumber(pos);
    potentialCollider.reserve(GMNumber::EXPECTED_POTENTIAL_COLLISION);

    for (const auto& offset : offsetsForPlayerCollision) {

        sf::Vector2i potentialGridNumber = objectGridNumber + offset;
        if (IsValidGridIndex(potentialGridNumber)) {
            int gridCellIndex = CalculateIndex(potentialGridNumber);

            for (const auto& obj : staticGridCell[gridCellIndex]) {
                if (obj->GetShapeID() != id) {
                    potentialCollider.push_back(obj);
                }
            }
            for (const auto& obj : dynamicGridCell[gridCellIndex]) {
                if (obj->GetShapeID() != id) {
                    potentialCollider.push_back(obj);
                }
            }

        }
    }

    return potentialCollider;
}


void GameGrid::AddObject(std::shared_ptr<GameShape> shape, bool isStatic){
    auto  position = shape->GetPosition();
    int index = CalculateIndex(position);
    AddObjectAtIndex(shape, index, isStatic);
}



void GameGrid::MoveObject(std::shared_ptr<GameShape> shape) {
    sf::Vector2f newPos = shape->GetPosition();
    sf::Vector2f oldPos = shape->GetOldPosition();
    int oldIndex = CalculateIndex(oldPos);
    int newIndex = CalculateIndex(newPos);

    if (oldIndex != newIndex) {
    int id = shape->GetShapeID();
        RemoveObjectAtIndex(oldIndex, id,false);
        AddObjectAtIndex(shape , newIndex, false);
    }
}

void GameGrid::Draw(std::shared_ptr<sf::RenderWindow> window) {
    for (int i = 0; i < gridVisual.size(); ++i) {
        window->draw(*gridVisual[i]); 
    }
}

void GameGrid::ShowGirdObjectCound() {
    size_t count = 0;
    for (int i = 0; i < staticGridCell.size(); ++i) {
        count += staticGridCell[i].size();
    }
    for (int i = 0; i < dynamicGridCell.size(); ++i) {
        count += dynamicGridCell[i].size();
    }
    std::cout << " grid object count = " << count << std::endl;
    return;
}


void GameGrid::VisualGridInit() {
    for (int y = 0; y < GMNumber::GRID_COUNT_Y; ++y) {
        for (int x = 0; x < GMNumber::GRID_COUNT_X; ++x) {
            int index = x + y * (int)GMNumber::GRID_COUNT_X;;
            std::shared_ptr<sf::RectangleShape> VisualRectangle = std::make_shared<sf::RectangleShape>();
            VisualRectangle->setSize(sf::Vector2f(GMNumber::BASE_GRID_SIZE_X, GMNumber::BASE_GRID_SIZE_Y));
            VisualRectangle->setPosition(x * GMNumber::BASE_GRID_SIZE_X, y * GMNumber::BASE_GRID_SIZE_Y);
            VisualRectangle->setOutlineThickness(.5f);
            VisualRectangle->setOutlineColor(sf::Color(165, 42, 42, 128));
            VisualRectangle->setFillColor(sf::Color::Transparent);
            gridVisual.push_back(VisualRectangle);
        }
    }
}

inline int GameGrid::CalculateIndex(sf::Vector2f pos) {
    int x = static_cast<int>(pos.x / GMNumber::BASE_GRID_SIZE_X);
    int y = static_cast<int>(pos.y / GMNumber::BASE_GRID_SIZE_Y);
    return x + y * (int)GMNumber::GRID_COUNT_X;
}

inline int GameGrid::CalculateIndex(sf::Vector2i gridId) {
    return gridId.x + gridId.y * (int)GMNumber::GRID_COUNT_X;
}

inline sf::Vector2i GameGrid::GetGridNumber(sf::Vector2f pos) {
    int x = static_cast<int>(pos.x / GMNumber::BASE_GRID_SIZE_X);
    int y = static_cast<int>(pos.y / GMNumber::BASE_GRID_SIZE_Y);
    return { x, y };
}

void GameGrid::AddObjectAtIndex(std::shared_ptr<GameShape> shape, int index, bool isStatic) {
    auto& vectorType = (isStatic) ? staticGridCell : dynamicGridCell;
    if (index >= 0 && index < (int)vectorType.size()) {
        vectorType[index].push_back(shape);
    }
}

void GameGrid::RemoveObjectAtIndex(int id, int index, bool isStatic) {
    if (index >= 0 && index < (int)staticGridCell.size()) {
        auto& shapeVector = isStatic ? staticGridCell[index] : dynamicGridCell[index];
        shapeVector.erase(std::remove_if(shapeVector.begin(), shapeVector.end(),
            [id](std::shared_ptr<GameShape> obj) { return obj->GetShapeID() == id; }), shapeVector.end());
    }
}
