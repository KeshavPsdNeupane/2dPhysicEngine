#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<memory>
#include"../PhysicUtility/Utility.h"

struct GridObject {
	int ID;
	int previousGridId;
	std::shared_ptr<sf::RectangleShape> Object;
public:
	GridObject() = default;
	GridObject(const int id, std::shared_ptr<sf::RectangleShape> rect) :
		ID(id), Object(rect) , previousGridId(){}
	inline void Move(sf::Vector2f& newPosition){ Object->setPosition(newPosition); }
};

class GameGrid {
	std::vector<std::pair<std::shared_ptr<sf::RectangleShape>, std::vector<GridObject>>> gridcell;
public:
	GameGrid();
public:
	void AddObject(std::shared_ptr<sf::RectangleShape> rect , const int& id);
	void MoveObject(std::shared_ptr<sf::RectangleShape> rect,const sf::Vector2f& oldPosition ,const int& id);
	void RemoveObject(std::shared_ptr<sf::RectangleShape> rect , const int& id);
	std::vector<std::shared_ptr<sf::RectangleShape>> PotentialCollision(std::shared_ptr<sf::RectangleShape> rect, const int& id);
	void Draw(std::shared_ptr<sf::RenderWindow>window);
private:
	void VisualGridInit();
	inline int GetIndex(sf::Vector2f pos);
	inline int GetIndex(sf::Vector2i pos);
	inline sf::Vector2i GetGridNumber(sf::Vector2f pos);
	inline int Floor(float i){return static_cast<int>(std::floor(i));}
	void AddObjectAtIndex(const std::shared_ptr<sf::RectangleShape>& rect, const int& id, const int& index);
	void RemoveObjectAtIndex(const int& id, const int& index);
};

