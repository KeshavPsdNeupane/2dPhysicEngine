
#include "GameGrid.h"
#include <cmath>

GameGrid::GameGrid() {
	int Gx = GMNumber::GRID_COUNT_X;
    int Gy = GMNumber::GRID_COUNT_Y;
    gridVisual.reserve(Gx * Gy);
    staticGridCell.resize(Gx * Gy);
    dynamicGridCell.resize(Gx * Gy);
	tileVisual.reserve(GMNumber::TILE_COUNT_X * GMNumber::TILE_COUNT_Y);
    VisualGridInit();
}


void GameGrid::RemoveObject(std::shared_ptr<GameShape> shape, bool isStatic) {
    sf::Vector2f position = shape->GetPosition();
    int index = CalculateIndex(position);
    int id = shape->GetShapeID();
    RemoveObjectAtIndex(id, index, isStatic);
}


GridResult GameGrid::PotentialCollision(std::shared_ptr<GameShape> shape) {
    return FindObjectsInRange(shape, GMNumber::POTENTIAL_COLLISION_RANGE, true);
}

GridResult GameGrid::FindUpdatableAndDrawableBlock(std::shared_ptr<GameShape> shape) {
    return FindObjectsInRange(shape, GMNumber::UPDATE_DRAW_RANGE, false);
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

    if (oldIndex != newIndex && newIndex < this->dynamicGridCell.size()) {
        RemoveObjectAtIndex(shape->GetShapeID(), oldIndex,false);
        AddObjectAtIndex(shape , newIndex, false);
    }
}

void GameGrid::Draw(std::shared_ptr<sf::RenderWindow> window){
 /*   for (int i = 0; i < gridVisual.size(); ++i) {
        window->draw(*gridVisual[i]);
    }*/
	for (int i = 0; i < tileVisual.size(); ++i) {
		window->draw(*tileVisual[i]);
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
            float size = GMNumber::BASE_GRID_SIZE;
            float posX = x * size;
            float posY = y * size;
            sf::Vector2f position(posX, posY);
            sf::Color rectangleColor(162, 42, 42 , 100);
            std::shared_ptr<OutlineRectangle> out = std::make_shared<OutlineRectangle>(size, size, position, rectangleColor);
            gridVisual.push_back(out);
        }
    }

    for (int y = 0; y < GMNumber::TILE_COUNT_Y; ++y) {
        for (int x = 0; x < GMNumber::TILE_COUNT_X; ++x) {
            float size = GMNumber::TILE_SIZE;
            float posX = x * size;
            float posY = y * size;
            sf::Vector2f position(posX, posY);
            sf::Color color(255,255,255,100);
            std::shared_ptr<OutlineRectangle> out = std::make_shared<OutlineRectangle>(size, size, position, color);
            tileVisual.push_back(out);
        }
    }




}

inline int GameGrid::CalculateIndex(sf::Vector2f pos) {
    int x = static_cast<int>(pos.x / GMNumber::BASE_GRID_SIZE);
    int y = static_cast<int>(pos.y / GMNumber::BASE_GRID_SIZE);
    return x + y * (int)GMNumber::GRID_COUNT_X;
}

inline int GameGrid::CalculateIndex(sf::Vector2i gridId) {
    return gridId.x + gridId.y * (int)GMNumber::GRID_COUNT_X;
}

inline sf::Vector2i GameGrid::GetGridNumber(sf::Vector2f pos) {
    int x = static_cast<int>(pos.x / GMNumber::BASE_GRID_SIZE);
    int y = static_cast<int>(pos.y / GMNumber::BASE_GRID_SIZE);
    return { x, y };
}

inline bool GameGrid::IsValidGridIndex(sf::Vector2i gridNumber) const{
    return gridNumber.x >= 0 && gridNumber.x < GMNumber::GRID_COUNT_X &&
        gridNumber.y >= 0 && gridNumber.y < GMNumber::GRID_COUNT_Y;
}

void GameGrid::AddObjectAtIndex(std::shared_ptr<GameShape> shape, int index, bool isStatic) {
    auto& vectorType = (isStatic) ? staticGridCell : dynamicGridCell;
    if (index >= 0 && index < (int)vectorType.size()) {;
        vectorType[index].push_back(shape);
    }
}

void GameGrid::RemoveObjectAtIndex(int id, int index, bool isStatic) {
    auto& shapeVector = isStatic ? staticGridCell : dynamicGridCell;
    if (index >= 0 && index < shapeVector.size()) {
        auto& objectsInCell = shapeVector[index];
        auto it = std::remove_if(objectsInCell.begin(), objectsInCell.end(),
            [id](std::shared_ptr<GameShape> obj) { return obj->GetShapeID() == id; });

        if (it != objectsInCell.end()) {
            objectsInCell.erase(it, objectsInCell.end());
        }
    }
}




GridResult GameGrid::FindObjectsInRange(std::shared_ptr<GameShape> shape, int range, bool skipSelf) {
    GridResult result;
    sf::Vector2f pos = shape->GetPosition();
    int id = shape->GetShapeID();
    sf::Vector2i objectGridNumber = GetGridNumber(pos);
    result.dynamicResult.reserve((2 * range + 1) * (2 * range + 1));
    result.staticResult.reserve((2 * range + 1) * (2 * range + 1));
    for (int y = -range; y <= range; ++y) {
        for (int x = -range; x <= range; ++x) {

            sf::Vector2i potentialGridNumber = objectGridNumber + sf::Vector2i(x, y);

            if (IsValidGridIndex(potentialGridNumber)) {
                int gridCellIndex = CalculateIndex(potentialGridNumber);

                for (const auto& obj : staticGridCell[gridCellIndex]) {
                    if (skipSelf && obj->GetShapeID() != id) {
                        result.staticResult.push_back(obj);
                    }
                    else if (!skipSelf) {
                        result.staticResult.push_back(obj);
                    }
                }

                for (const auto& obj : dynamicGridCell[gridCellIndex]) {
                    if (skipSelf && obj->GetShapeID() != id) {
                        result.dynamicResult.push_back(obj);
                    }
                    else if (!skipSelf) {
                        result.dynamicResult.push_back(obj);
                    }
                }
            }
        }
    }
    result.dynamicResult.shrink_to_fit();
    result.staticResult.shrink_to_fit();
    return result;
}
