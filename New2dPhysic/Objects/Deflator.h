#pragma once
#include<SFML/Graphics.hpp>
#include"../Body/GameShapes.h"


class Deflator :public GameShape {
public:
    Deflator() = default;
    Deflator(const int id, const int colid, const float mass, const sf::Vector2f pos,
        const sf::Vector2f size, const sf::Vector2f coeffOfRest,
        const sf::Vector2f ceoffOfFriction);
    ~Deflator();
public:
    void Load(std::shared_ptr<Engine::ResourceManager> resources) override;
    void Update(const float& dt) override;
    void Draw(std::shared_ptr<sf::RenderWindow>window) override;
};