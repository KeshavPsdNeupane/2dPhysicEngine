#include "DynamicEnemy.h"
#include"../PhysicUtility/Utility.h"

DynamicEnemy::DynamicEnemy(const int id, const int colid, const float mass,
    const int textureId, const sf::Vector2f pos,
    const sf::Vector2f size, const sf::Vector2f velocity) :
    GameShape(id, colid, mass, pos, size,
        velocity, { 0.0f,0.0f }, { 0.0f,0.0f },0.0f), 
    textureId(0), orginPosition(pos){
    this->textureId = textureId;
    this->sprite.setPosition(pos);
    this->shape->setSize(size);
    this->shape->setPosition(pos);
}

DynamicEnemy::~DynamicEnemy() {}

void DynamicEnemy::Load(std::shared_ptr<Engine::ResourceManager> resources) {
    int textureX = this->textureId % GMNumber::TEXTURE_COUNT_X;
    int textureY = (int)(this->textureId / GMNumber::TEXTURE_COUNT_X);
    int testsize = GMNumber::TEXTURE_SIZE;
    this->sprite.setTexture(resources->GetTexture(ResourceId::TILE_TEXTURE));
    this->sprite.setTextureRect(sf::IntRect(textureX * testsize,
        textureY * testsize, testsize, testsize));

    this->shape->setFillColor(MyColor::indigo);
    if (GMNumber::IS_PADDING) {
        this->shape->setOutlineThickness(0.5f);
        this->shape->setOutlineColor(sf::Color::Black);
    }
	this->gravity = 0.0f;
}
void DynamicEnemy::Update(const float& dT) {
	this->shape->setPosition(NewPosition(dT));
	this->sprite.setPosition(this->shape->getPosition());

	const auto& pos = this->shape->getPosition();
	if (pos.y >= orginPosition.y + size.y && this->velocity.y > 0.0f) {
		this->velocity.y = -this->velocity.y;
	}
	else if (pos.y <= orginPosition.y - size.y && this->velocity.y < 0.0f) {
		this->velocity.y = -this->velocity.y;
	}
	else if (pos.x >= orginPosition.x + size.x && this->velocity.x > 0.0f) {
		this->velocity.x = -this->velocity.x;
	}
    else if (pos.x <= orginPosition.x - size.x && this->velocity.y < 0.0f) {
        this->velocity.x = -this->velocity.x;
    }
}


void DynamicEnemy::Draw(std::shared_ptr<sf::RenderWindow>window) {
    window->draw(this->sprite);
}

inline void DynamicEnemy::FindMaxVelocities() {
    if (this->mass == 0) { this->mass = 1.0f; }
    this->maxVelocity = this->velocity;
}
