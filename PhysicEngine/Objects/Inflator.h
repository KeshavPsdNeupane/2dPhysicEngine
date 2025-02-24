#pragma once
#include<SFML/Graphics.hpp>
#include"../Body/GameShapes.h"


class Inflator :public GameShape {
    int textureId;
	sf::Sprite sprite;
public:
    Inflator() = default;
    Inflator(const int id, const int colid, const float mass, const int textureId,
        const sf::Vector2f pos,
        const sf::Vector2f size, const sf::Vector2f coeffOfRest,
        float ceoffOfFriction);
    ~Inflator();
public:
    void Load(std::shared_ptr<Engine::ResourceManager> resources) override;
    void Update(const float& dt) override;
    void Draw(std::shared_ptr<sf::RenderWindow>window) override;

};