#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Body/GameShapes.h"
#include "../Body/ContactMechanic.h"

class Path : public GameShape {
public:
    Path() = default;
    Path(const int id, const float mass, const sf::Vector2f pos,
        const sf::Vector2f size, const sf::Vector2f velocity,
        const sf::Vector2f accleration , const sf::Vector2f coeffOfRest , const sf::Vector2f ceoffOfFriction);

    inline std::shared_ptr<sf::RectangleShape> GetShape() { return shape; }
    inline RigidBody& GetFrame() { return *this; }

    public:
    void Load() override;
    void Update(const float& dt) override;
    void CollisionRedirection(std::shared_ptr<GameShape> playerShape,
        ContactMech& contact) override;
    void Draw(std::shared_ptr<sf::RenderWindow>window) override;

private:
    inline void FindMaxVelocities() override;
};
