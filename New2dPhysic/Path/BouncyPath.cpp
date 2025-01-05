#include "BouncyPath.h"


BouncyPath::BouncyPath(const int id, const int colid, const float mass, const sf::Vector2f pos, const sf::Vector2f size,
    const sf::Vector2f coeffOfRest, const sf::Vector2f ceoffOfFriction) :
    GameShape(id, colid, mass, pos, size,
        { 0.0f,0.0f }, { 0.0f,0.0f }, coeffOfRest, ceoffOfFriction) {
    this->shape->setPosition(this->position);
    this->shape->setSize(this->size);
    this->shape->setFillColor(sf::Color::Magenta);
}
void BouncyPath::Load() {
    this->shape->setOutlineThickness(1.0f);
    this->shape->setOutlineColor(sf::Color::Black);
}

void BouncyPath::Update(const float& dT) {
    if (this->velocity.x != 0 || this->velocity.y != 0) {
        this->shape->setPosition(this->NewPosition(dT));
    }
}


void BouncyPath::Draw(std::shared_ptr<sf::RenderWindow>window) {
    window->draw(*this->shape);
}

inline void BouncyPath::FindMaxVelocities() {
    if (this->mass == 0) { this->mass = 1.0f; }
    this->maxvelocity = this->velocity;
}
