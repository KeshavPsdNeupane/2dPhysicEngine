#include "StaticEnemyS.h"
#include"../PhysicUtility/Utility.h"

StaticEnemyS::StaticEnemyS(const int id, const int colid, const float mass,
    const int textureId, const sf::Vector2f pos, const sf::Vector2f size,
    const sf::Vector2f coeffOfRest, const float ceoffOfFriction) :
    GameShape(id, colid, mass, pos, size,
        { 0.0f,0.0f }, { 0.0f,0.0f }, coeffOfRest, ceoffOfFriction), textureId(0) {

    this->textureId = textureId +1;
    this->sprite.setPosition(pos);
    sf::Vector2f apparantSize = { size.x, size.y * (46.0f / 64.0f) };
    sf::Vector2f apparentPos = { pos.x, pos.y + size.y * (12.0f /64.0f)};
    this->shape->setSize(apparantSize);
    this->shape->setPosition(apparentPos);
    this->size = apparantSize;
    this->position = apparentPos;
}

StaticEnemyS::~StaticEnemyS() {}

void StaticEnemyS::Load(std::shared_ptr<Engine::ResourceManager> resources) {
    int textureX = this->textureId % GMNumber::TEXTURE_COUNT_X;
    int textureY = (int)(this->textureId / GMNumber::TEXTURE_COUNT_X);
    int testsize = GMNumber::TEXTURE_SIZE;
    this->sprite.setTexture(resources->GetTexture(ResourceId::TILE_TEXTURE));
    this->sprite.setTextureRect(sf::IntRect(textureX * testsize,
        textureY * testsize, testsize, testsize));

    this->shape->setFillColor(MyColor::chocolate);
    if (GMNumber::IS_PADDING) {
        this->shape->setOutlineThickness(0.5f);
        this->shape->setOutlineColor(sf::Color::Black);
    }
}
void StaticEnemyS::Update(const float& dT) {}


void StaticEnemyS::Draw(std::shared_ptr<sf::RenderWindow>window) {
	window->draw(*this->shape);
    window->draw(this->sprite);
}

inline void StaticEnemyS::FindMaxVelocities() {
    if (this->mass == 0) { this->mass = 1.0f; }
    this->maxVelocity = this->velocity;
}
