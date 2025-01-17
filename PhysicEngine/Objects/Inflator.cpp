#include "Inflator.h"

Inflator::Inflator(const int id, const int colid, const float mass, const sf::Vector2f pos, const sf::Vector2f size,
    const sf::Vector2f coeffOfRest, const float ceoffOfFriction) :
    GameShape(id, colid, mass, pos, size,
        { 0.0f,0.0f }, { 0.0f,0.0f }, coeffOfRest, ceoffOfFriction) {
    this->shape->setPosition(this->position);
    this->shape->setSize(this->size);
}

Inflator::~Inflator(){}

void Inflator::Load(std::shared_ptr<Engine::ResourceManager> resources) {
    this->shape->setFillColor(sf::Color::Green);
    if (GMNumber::IS_PADDING) {
        this->shape->setOutlineThickness(0.5f);
        this->shape->setOutlineColor(sf::Color::Black);
    }
}

void Inflator::Update(const float& dT) {
    if (this->velocity.x != 0 || this->velocity.y != 0) {
        this->shape->setPosition(this->NewPosition(dT));
    }
}


void Inflator::Draw(std::shared_ptr<sf::RenderWindow>window) {
    window->draw(*this->shape);
}

