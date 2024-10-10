#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<array>
#include<memory>
#include"../PhysicUtility/Utility.h"
#include"../Body/GameShapes.h"
#include"../Body/ContactMechanic.h"

class GameGrid {
    std::vector<std::shared_ptr<sf::RectangleShape>> gridVisual;    
    std::vector<std::vector<std::shared_ptr<GameShape>>> gridCell;
    const std::array<sf::Vector2i, 9> offsetsForPlayerCollision;
public:
    GameGrid();
public:
    void AddObject(std::shared_ptr<GameShape> shape);
    void MoveObject(std::shared_ptr<GameShape> shape);
    void RemoveObject(std::shared_ptr<GameShape> shape);
    std::vector<std::shared_ptr<GameShape>> PotentialCollision(std::shared_ptr<GameShape> shape);
    void Draw(std::shared_ptr<sf::RenderWindow>window);

    void ShowGirdObjectCound();

private:
    void VisualGridInit();
    inline int CalculateIndex(sf::Vector2f pos);
    inline int CalculateIndex(sf::Vector2i gridId);
    inline sf::Vector2i GetGridNumber(sf::Vector2f pos);
    inline int Floor(float i) { return static_cast<int>(std::floor(i)); }
    void AddObjectAtIndex( std::shared_ptr<GameShape> shape, const int& index);
    void RemoveObjectAtIndex(const int& id, const int& index);
};