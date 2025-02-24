#include "StaticEnemy.h"
#include"../PhysicUtility/Utility.h"

StaticEnemy::StaticEnemy(const int id, const int colid, const float mass, 
    const int textureId, const sf::Vector2f pos, const sf::Vector2f size,
    const sf::Vector2f coeffOfRest, const float ceoffOfFriction) :
    GameShape(id, colid, mass, pos, size,
        { 0.0f,0.0f }, { 0.0f,0.0f }, coeffOfRest, ceoffOfFriction) , textureId(0){

	this->textureId = textureId;
    this->sprite.setPosition(pos);
    sf::Vector2f apparantSize = { size.x * (46.0f / 64.0f) , size.y };
	sf::Vector2f apparentPos = { pos.x + (10.0f/64.0f)*size.x , pos.y};
    this->shape->setSize(apparantSize);
    this->shape->setPosition(apparentPos);
    this->size = apparantSize;
    this->position = apparentPos;
}

StaticEnemy::~StaticEnemy() {}

void StaticEnemy::Load(std::shared_ptr<Engine::ResourceManager> resources) {
    int textureX = this->textureId % GMNumber::TEXTURE_COUNT_X;
    int textureY = (int)(this->textureId / GMNumber::TEXTURE_COUNT_X);
    int testsize = GMNumber::TEXTURE_SIZE;
    this->sprite.setTexture(resources->GetTexture(ResourceId::TILE_TEXTURE));
    this->sprite.setTextureRect(sf::IntRect(textureX * testsize,
        textureY * testsize, testsize, testsize));

    this->shape->setFillColor(MyColor::darkSlateGray);
    if (GMNumber::IS_PADDING) {
        this->shape->setOutlineThickness(0.5f);
        this->shape->setOutlineColor(sf::Color::Black);
    }
}
void StaticEnemy::Update(const float& dT) {
    if (this->velocity.x != 0 || this->velocity.y != 0) {
        this->shape->setPosition(this->NewPosition(dT));
    }
}


void StaticEnemy::Draw(std::shared_ptr<sf::RenderWindow>window) {
	window->draw(this->sprite);
}

inline void StaticEnemy::FindMaxVelocities() {
    if (this->mass == 0) { this->mass = 1.0f; }
    this->maxVelocity = this->velocity;
}
