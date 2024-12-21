#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<array>
#include<memory>
#include"../PhysicUtility/Utility.h"
#include"../Body/GameShapes.h"
#include"../Body/ContactMechanic.h"

struct GridResult {
    std::vector<std::shared_ptr<GameShape>> staticResult;
    std::vector<std::shared_ptr<GameShape>> dynamicResult;
};

class GameGrid {
    std::vector<std::shared_ptr<sf::RectangleShape>> gridVisual;    

    std::vector<std::vector<std::shared_ptr<GameShape>>> staticGridCell;
    std::vector<std::vector<std::shared_ptr<GameShape>>> dynamicGridCell;
public:
    GameGrid();
public:
    void AddObject(std::shared_ptr<GameShape> shape ,  bool isStatic);
    void MoveObject(std::shared_ptr<GameShape> shape);
    void RemoveObject(std::shared_ptr<GameShape> shape , bool isStatic);
    GridResult PotentialCollision(std::shared_ptr<GameShape> shape);
    GridResult FindUpdatableAndDrawableBlock(std::shared_ptr<GameShape> shape);
    void Draw(std::shared_ptr<sf::RenderWindow>window);
    void ShowGirdObjectCound();

private:
    void VisualGridInit();

    inline int CalculateIndex(sf::Vector2f pos);
    inline int CalculateIndex(sf::Vector2i gridId);
    inline sf::Vector2i GetGridNumber(sf::Vector2f pos);
    inline bool IsValidGridIndex(sf::Vector2i gridNumber) const;
    void AddObjectAtIndex(std::shared_ptr<GameShape> shape, int index, bool isStatic);
    void RemoveObjectAtIndex(int id, int index, bool isStatic);
    GridResult FindObjectsInRange(std::shared_ptr<GameShape> shape, int range, bool skipSelf);
};

