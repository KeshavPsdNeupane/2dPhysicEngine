#include"Collectable.h"

Collectable::Collectable(const int id, const int colid, const float mass,
    const unsigned int points,
    const sf::Vector2f pos, const sf::Vector2f size) :
    point(points), canBeDeleted(false),
    GameShape(id, colid, mass, pos, size,
        { 0.0f,0.0f }, { 0.0f,0.0f }, { 0.0f,0.0f }, { 0.0f,0.0f }) {
    this->shape->setPosition(pos);
    this->shape->setSize(size);

}

Collectable::~Collectable(){}

void Collectable::Load(std::shared_ptr<Engine::ResourceManager> resources) {
    this->shape->setFillColor(sf::Color::Cyan);
}

void Collectable::Update(const float& dT) {
    if (this->velocity.x != 0 || this->velocity.y != 0) {
        this->shape->setPosition(this->NewPosition(dT));
    }
}


void Collectable::Draw(std::shared_ptr<sf::RenderWindow>window) {
    window->draw(*this->shape);
}

inline void Collectable::FindMaxVelocities() {
    if (this->mass == 0) { this->mass = 1.0f; }
    this->maxvelocity = this->velocity;
}
