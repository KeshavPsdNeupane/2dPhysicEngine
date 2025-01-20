#include "InvisibleEnemy.h"
#include"../PhysicUtility/Utility.h"

InvisibleEnemy::InvisibleEnemy(const int id, const int colid, const float mass,
    const sf::Vector2f pos, const sf::Vector2f size) :
    GameShape(id, colid, mass, pos, size,
        { 0.0f,0.0f }, { 0.0f,0.0f }, { 0.0f,0.0f }, 0.0f) {
    this->shape->setSize(size);
    this->shape->setPosition(pos);
}

InvisibleEnemy::~InvisibleEnemy() {}

void InvisibleEnemy::Load(std::shared_ptr<Engine::ResourceManager> resources) {
    this->shape->setFillColor(MyColor::darkSlateGray);
    if (GMNumber::IS_PADDING) {
        this->shape->setOutlineThickness(0.5f);
        this->shape->setOutlineColor(sf::Color::Black);
    }
}
void InvisibleEnemy::Update(const float& dT) {}


void InvisibleEnemy::Draw(std::shared_ptr<sf::RenderWindow>window) {
	window->draw(*this->shape);
}

inline void InvisibleEnemy::FindMaxVelocities() {
    if (this->mass == 0) { this->mass = 1.0f; }
    this->maxVelocity = this->velocity;
}
