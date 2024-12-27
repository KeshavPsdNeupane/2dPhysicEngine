#include "Inflator.h"

Inflator::Inflator(const int id, const int colid, const float mass, const sf::Vector2f pos, const sf::Vector2f size,
	const sf::Vector2f velocity, const sf::Vector2f accleration, const sf::Vector2f coeffOfRest, const sf::Vector2f coeffOfFriction) :
	GameShape(id , colid ,mass,pos,size,velocity,accleration,coeffOfRest,coeffOfRest){
	this->shape->setSize(size);
	this->shape->setPosition(pos);
}

void Inflator::Load() {
    this->shape->setFillColor(sf::Color::Green);
    this->shape->setOutlineThickness(1.0f);
    this->shape->setOutlineColor(sf::Color::Black);
}

void Inflator::Update(const float& dT) {
    if (this->velocity.x != 0 || this->velocity.y != 0) {
        this->shape->setPosition(this->NewPosition(dT));
    }
}


void Inflator::Draw(std::shared_ptr<sf::RenderWindow>window) {
    window->draw(*this->shape);
}

inline void Inflator::FindMaxVelocities() {
    if (this->mass == 0) { this->mass = 1.0f; }
    this->maxvelocity = this->velocity;
}
