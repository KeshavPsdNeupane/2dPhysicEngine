#include "GameGrid.h"
#include <cmath>
GameGrid::GameGrid(){
	gridcell.reserve(static_cast<int>(GMNumber::GRID_COUNT_X * GMNumber::GRID_COUNT_Y));
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
	//std::cout << "potential test 1 " << std::endl;
	auto pos = rect->getPosition();
	auto getGridNumber = GetGridNumber(pos);
	std::vector<std::shared_ptr<sf::RectangleShape>> potentialCollider;
	//std::cout << " grid position = " << getGridNumber.x << " " << getGridNumber.y << std::endl;
	for (int i = -1; i <= 1; ++i) {
		//std::cout << "potential test 2 " << std::endl;
		for (int j = -1; j <= 1; ++j) {
			//std::cout << "potential test 3 " << std::endl;
			int tempIndex = GetIndex(getGridNumber + sf::Vector2i(i, j));
			if (tempIndex >= 0 && tempIndex < gridcell.size()) {
				//std::cout << "potential test 4 " << std::endl;
				auto& vectorlist = gridcell[tempIndex].second;
				for (const auto& obj : vectorlist) {
					//std::cout << "potential test 5 " << std::endl;
					if (obj.ID != id) {
						std::cout << " index = " << tempIndex << std::endl;
						potentialCollider.push_back(obj.Object);
					}
				}
			}
		}
		//std::cout << std::endl;
	}

	return potentialCollider;
	//std::cout << std::endl;
}

void GameGrid::MoveObject(std::shared_ptr<sf::RectangleShape> rect, const sf::Vector2f& oldPosition, const int& id) {
	auto newPos = rect->getPosition();
	int oldIndex = GetIndex(oldPosition);
	int newIndex = GetIndex(newPos);

	// DONT REMOVE THIS IS NEEDED FOR DEBUGGING 
	//if (oldIndex == newIndex) {
	//	//std::cout << " same as old " << std::endl << std::endl;
	//	auto& gridObjects = gridcell[oldIndex].second;
	//	for (auto& obj : gridObjects) {
	//		if (obj.ID == id) {
	//			auto pos = obj.Object->getPosition();
	//			std::cout << " Position in grid = " << pos.x << " " << pos.y << std::endl;
	//			break;
	//		}
	//	}
	//	return;
	//}


	if(oldIndex !=newIndex) {
	// std::cout << "  different old index = "<< oldIndex << " NewIndex = " << newIndex << std::endl << std::endl;
		RemoveObjectAtIndex(oldIndex, id);
		AddObjectAtIndex(rect, id , newIndex);
	}
}


void GameGrid::Draw(std::shared_ptr<sf::RenderWindow> window){
	for (int i = 0; i < gridcell.size(); ++i) {
		window->draw(*gridcell[i].first);
	}
}


void GameGrid::VisualGridInit(){  
	for (int y = 0; y < GMNumber::GRID_COUNT_Y; ++y) {
		for (int x = 0; x < GMNumber::GRID_COUNT_X; ++x) {
			int index = x + y *(int)GMNumber::GRID_COUNT_X;
			//std::cout << " index = " << index << std::endl;
			 std::shared_ptr<sf::RectangleShape>Trect = std::make_shared<sf::RectangleShape>();
			Trect->setSize(sf::Vector2f(GMNumber::BASE_GRID_SIZE_X, GMNumber::BASE_GRID_SIZE_Y));
			Trect->setPosition(x * GMNumber::BASE_GRID_SIZE_X, y * GMNumber::BASE_GRID_SIZE_Y);
			Trect->setOutlineThickness(2);
			Trect->setOutlineColor(sf::Color(165, 42, 42, 128));
			Trect->setFillColor(sf::Color::Transparent);
			gridcell.emplace_back(Trect, std::vector<GridObject>());
			//sf::Vector2f pos = Trect->getPosition();
			//std::cout << "positions = " << pos.x << " " << pos.y << std::endl << std::endl;
		}
	}
}








inline int GameGrid::GetIndex(sf::Vector2f pos){
	int x = Floor(pos.x / GMNumber::BASE_GRID_SIZE_X);
	int y = Floor(pos.y / GMNumber::BASE_GRID_SIZE_Y);
	return x + y * (int)GMNumber::GRID_COUNT_X;
}

inline int GameGrid::GetIndex(sf::Vector2i pos){
	int x = Floor(pos.x / GMNumber::BASE_GRID_SIZE_X);
	int y = Floor(pos.y / GMNumber::BASE_GRID_SIZE_Y);
	return x + y * (int)GMNumber::GRID_COUNT_X;
}

inline sf::Vector2i GameGrid::GetGridNumber(sf::Vector2f pos){
	int x = Floor(pos.x / GMNumber::BASE_GRID_SIZE_X);
	int y = Floor(pos.y / GMNumber::BASE_GRID_SIZE_Y);
	return { x,y };
}

void GameGrid::AddObjectAtIndex(const std::shared_ptr<sf::RectangleShape>& rect, const int& id, const int& index) {
	if (index >= 0 && index < gridcell.size()) {
		GridObject object(id, rect);
		object.previousGridId = index;
		gridcell[index].second.push_back(object);
	}
	else {
		std::cerr << "Error: Calculated grid index (" << index << ") is out of bounds!" << std::endl;
	}
}

void GameGrid::RemoveObjectAtIndex(const int& id, const int& index) {
	if (index >= 0 && index < gridcell.size()) {
		auto& objects = gridcell[index].second;
		objects.erase(std::remove_if(objects.begin(), objects.end(),
			[id](const GridObject& obj) { return obj.ID == id; }), objects.end());
	}
	else {
		std::cerr << "Error: Calculated grid index (" << index << ") is out of bounds!" << std::endl;
	}
}
