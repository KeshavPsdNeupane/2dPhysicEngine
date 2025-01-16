#include"CheckPoint.h"
#include"../PhysicUtility/Utility.h"
CheckPoint::CheckPoint(const int id, const int colid, 
    const sf::Vector2f pos, const sf::Vector2f size) :
    GameShape(id, colid, 1.0f, pos, size,
        { 0.0f,0.0f }, { 0.0f,0.0f }, { 0.0f,0.0f }, 0.0f),
    isFound(false){
    this->shape->setPosition(this->position);
    this->shape->setSize(this->size);
}

CheckPoint::~CheckPoint() {}

void CheckPoint::Load(std::shared_ptr<Engine::ResourceManager> resources) {
    this->shape->setFillColor(MyColor::teal);
    if (GMNumber::IS_PADDING) {
        this->shape->setOutlineThickness(0.5f);
        this->shape->setOutlineColor(sf::Color::Black);
    }
}

void CheckPoint::Update(const float& dT) {
    if (this->velocity.x != 0 || this->velocity.y != 0) {
        this->shape->setPosition(this->NewPosition(dT));
    }
}


void CheckPoint::Draw(std::shared_ptr<sf::RenderWindow>window) {
    window->draw(*this->shape);
}
