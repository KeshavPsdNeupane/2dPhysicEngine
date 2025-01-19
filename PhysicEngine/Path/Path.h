#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Body/GameShapes.h"

class Path : public GameShape {
    int textureId;
    sf::Sprite sprite;
public:
    Path() = default;
	Path(const int id, const int colid, const float mass, const int textureId,
        const sf::Vector2f pos,
        const sf::Vector2f size,  const sf::Vector2f coeffOfRest , 
        const float ceoffOfFriction);
    ~Path();
    public:
    void Load(std::shared_ptr<Engine::ResourceManager> resources) override;
    void Update(const float& dt) override;
    void Draw(std::shared_ptr<sf::RenderWindow>window) override;
};
