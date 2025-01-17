#include "BouncyPath.h"


BouncyPath::BouncyPath(const int id, const int colid, const float mass, const sf::Vector2f pos, const sf::Vector2f size,
    const sf::Vector2f coeffOfRest, const float ceoffOfFriction) :
    GameShape(id, colid, mass, pos, size,
        { 0.0f,0.0f }, { 0.0f,0.0f }, coeffOfRest, ceoffOfFriction) {
    this->shape->setPosition(this->position);
    this->shape->setSize(this->size);

}


BouncyPath::~BouncyPath(){}



void BouncyPath::Load(std::shared_ptr<Engine::ResourceManager> resources) {
    this->shape->setFillColor(sf::Color::Magenta);
    if (GMNumber::IS_PADDING) {
        this->shape->setOutlineThickness(.5f);
        this->shape->setOutlineColor(sf::Color::Black);
    }
}

void BouncyPath::Update(const float& dT) {
    if (this->velocity.x != 0 || this->velocity.y != 0) {
        this->shape->setPosition(this->NewPosition(dT));
    }
}


void BouncyPath::Draw(std::shared_ptr<sf::RenderWindow>window) {
    window->draw(*this->shape);
}

