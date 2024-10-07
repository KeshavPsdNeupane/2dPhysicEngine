#include "Path.h"
#include "../PhysicUtility/Utility.h"
#include "../GameObjects.h"

Path::Path(const int id, const float& mass, const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Vector2f& velocity,
    const sf::Vector2f& accleration)
    : GameShape(id, mass, pos, size, velocity, accleration,
        sf::Vector2f(GMNumber::COEFF_OF_RESTITUTION_PATH_X , GMNumber::COEFF_OF_RESTITUTION_PATH_Y),
        sf::Vector2f(GMNumber::COEFF_OF_FRICTION_PATH, GMNumber::COEFF_OF_FRICTION_PATH)) {
    this->shape->setPosition(this->position);
    this->shape->setSize(this->size);
    // gameObject.grid.AddObject(this->path ,this->ID);
}

void Path::Load() {
    this->shape->setFillColor(sf::Color::Blue);
}

void Path::Update(const float& dT) {
    if (this->velocity.x != 0 || this->velocity.y != 0) {
        this->shape->setPosition(this->NewPosition(dT));
    }
}

void Path::CollisionRedirection(std::shared_ptr<GameShape> playerShape,
    std::shared_ptr<GameShape> otherShape, ContactMech& contact) {
    contact.PathCollsionHandleWithShape(playerShape, otherShape);
}

void Path::Draw(std::shared_ptr<sf::RenderWindow>window) {
    window->draw(*this->shape);
}

inline void Path::FindMaxVelocities() {
    if (this->mass == 0) {
        this->mass = 1.0f;
    }
    this->maxvelocity = this->velocity;
}
