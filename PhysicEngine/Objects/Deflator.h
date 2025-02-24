#pragma once
#include"../Body/GameShapes.h"


class Deflator :public GameShape {
    int textureId;
    sf::Sprite sprite;
public:
    Deflator() = default;
    Deflator(const int id, const int colid, const float mass, const int textureId,
        const sf::Vector2f pos,
        const sf::Vector2f size, const sf::Vector2f coeffOfRest,
        const float ceoffOfFriction);
    ~Deflator();
public:
    void Load(std::shared_ptr<Engine::ResourceManager> resources) override;
    void Update(const float& dt) override;
    void Draw(std::shared_ptr<sf::RenderWindow>window) override;
};