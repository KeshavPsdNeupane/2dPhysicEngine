#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Body/GameShapes.h"
#include "../Body/ContactMechanic.h"

class Path : public GameShape, public ContactMech {
public:
    Path() = default;
    Path(const int id, const float& mass, const sf::Vector2f& pos,
        const sf::Vector2f& size, const sf::Vector2f& velocity,
        const sf::Vector2f& accleration);

    inline std::shared_ptr<sf::RectangleShape> GetShape() { return shape; }
    inline RigidBody& GetFrame() { return *this; }
    inline ContactMech& GetContactHandler() { return *this; }


    void Load() override;
    void Update(const float& dt) override;
    void CollisionRedirection(std::shared_ptr<GameShape> playerShape,
        std::shared_ptr<GameShape> otherShape, ContactMech& contact) override;
    void Draw(std::shared_ptr<sf::RenderWindow>window) override;

    void PathBasedCollisionHandle(sf::FloatRect& Bound1, RigidBody& F1,
        sf::FloatRect& Bound2, RigidBody& F2);

private:
    inline void FindMaxVelocities() override;
};
