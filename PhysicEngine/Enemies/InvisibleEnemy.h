#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include"../Body/GameShapes.h"


class InvisibleEnemy : public GameShape {
public:
    InvisibleEnemy() = default;
    InvisibleEnemy(const int id, const int colid, const float mass, const sf::Vector2f pos,
        const sf::Vector2f size);
    ~InvisibleEnemy();
public:
    void Load(std::shared_ptr<Engine::ResourceManager> resources) override;
    void Update(const float& dt) override;
    void Draw(std::shared_ptr<sf::RenderWindow>window) override;

private:
    inline void FindMaxVelocities() override;
};
