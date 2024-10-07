#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<memory>
#include"../PhysicUtility/Utility.h"
#include"../Body/GameShapes.h"
#include"../Body/ContactMechanic.h"

struct GridObject {
    std::shared_ptr<GameShape> Object; 
public:
    GridObject() = default;
    GridObject(std::shared_ptr<GameShape> gameShapes): Object(gameShapes){}
};

class GameGrid {
    std::vector<std::shared_ptr<sf::RectangleShape>> gridVisual;    
    std::vector<std::vector<std::shared_ptr<GridObject>>> gridCell;
public:
    GameGrid();
public:
    void AddObject(std::shared_ptr<GameShape> rect);

    //void MoveObject(std::shared_ptr<sf::RectangleShape> rect, const sf::Vector2f& oldPosition, const int& id);
    //void RemoveObject(std::shared_ptr<sf::RectangleShape> rect, const int& id);
    //std::vector<std::shared_ptr<sf::RectangleShape>> PotentialCollision(std::shared_ptr<sf::RectangleShape> rect, const int& id);
    void Draw(std::shared_ptr<sf::RenderWindow>window);



private:
    void VisualGridInit();
    inline int GetIndex(sf::Vector2f pos);
    inline int GetIndex(sf::Vector2i pos);
    inline sf::Vector2i GetGridNumber(sf::Vector2f pos);
    inline int Floor(float i) { return static_cast<int>(std::floor(i)); }
    void AddObjectAtIndex( std::shared_ptr<GameShape> shape, const int& index);
    //void RemoveObjectAtIndex(const int& id, const int& index);
};