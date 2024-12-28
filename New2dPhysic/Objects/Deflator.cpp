#include "Deflator.h"
Deflator::Deflator(const int id, const int colid, const float mass, const sf::Vector2f pos, const sf::Vector2f size, const sf::Vector2f velocity,
    const sf::Vector2f accleration, const sf::Vector2f coeffOfRest, const sf::Vector2f ceoffOfFriction)
    : GameShape(id, colid, mass, pos, size, velocity, accleration, coeffOfRest, ceoffOfFriction) {
    this->shape->setPosition(this->position);
    this->shape->setSize(this->size);
}

void Deflator::Load() {
    this->shape->setFillColor(sf::Color::Yellow);
    this->shape->setOutlineThickness(1.0f);
    this->shape->setOutlineColor(sf::Color::Black);
}

void Deflator::Update(const float& dT) {
    if (this->velocity.x != 0 || this->velocity.y != 0) {
        this->shape->setPosition(this->NewPosition(dT));
    }
}


void Deflator::Draw(std::shared_ptr<sf::RenderWindow>window) {
    window->draw(*this->shape);
}

inline void Deflator::FindMaxVelocities() {
    if (this->mass == 0) { this->mass = 1.0f; }
    this->maxvelocity = this->velocity;
}
