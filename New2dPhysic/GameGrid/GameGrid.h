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

    std::vector<std::vector<std::shared_ptr<GameShape>>> staticGridCell;
    std::vector<std::vector<std::shared_ptr<GameShape>>> dynamicGridCell;
    const std::array<sf::Vector2i, 9> offsetsForPlayerCollision;
public:
    GameGrid();
public:
    void AddObject(std::shared_ptr<GameShape> shape ,  bool isStatic);
    void MoveObject(std::shared_ptr<GameShape> shape);
    void RemoveObject(std::shared_ptr<GameShape> shape , bool isStatic);

    std::vector<std::shared_ptr<GameShape>> PotentialCollision(std::shared_ptr<GameShape> shape);
   
    void Draw(std::shared_ptr<sf::RenderWindow>window);

    void ShowGirdObjectCound();

private:
    void VisualGridInit();

    inline int CalculateIndex(sf::Vector2f pos);
    inline int CalculateIndex(sf::Vector2i gridId);
    inline sf::Vector2i GetGridNumber(sf::Vector2f pos);

    inline bool IsValidGridIndex(sf::Vector2i gridNumber) const {
        return gridNumber.x >= 0 && gridNumber.x < GMNumber::GRID_COUNT_X &&
            gridNumber.y >= 0 && gridNumber.y < GMNumber::GRID_COUNT_Y;
    }

    void AddObjectAtIndex(std::shared_ptr<GameShape> shape, int index, bool isStatic);
    void RemoveObjectAtIndex(int id, int index, bool isStatic);
};

