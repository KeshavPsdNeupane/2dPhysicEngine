#pragma once
#include "../Body/GameShapes.h"


class BouncyPath : public GameShape {
public:
    BouncyPath() = default;
    BouncyPath(const int id, const int colid, const float mass, const sf::Vector2f pos,
        const sf::Vector2f size, const sf::Vector2f coeffOfRest,
        const float ceoffOfFriction);
    ~BouncyPath();
public:
    void Load(std::shared_ptr<Engine::ResourceManager> resources) override;
    void Update(const float& dt) override;
    void Draw(std::shared_ptr<sf::RenderWindow>window) override;
};
