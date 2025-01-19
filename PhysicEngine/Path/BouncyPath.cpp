#include "BouncyPath.h"


BouncyPath::BouncyPath(const int id, const int colid, const float mass,
    const int textureId,
    const sf::Vector2f pos, const sf::Vector2f size,
    const sf::Vector2f coeffOfRest, const float ceoffOfFriction) :
    GameShape(id, colid, mass, pos, size,
        { 0.0f,0.0f }, { 0.0f,0.0f }, coeffOfRest, ceoffOfFriction), textureId(textureId) {
    this->sprite.setPosition(pos);
    sf::Vector2f apparentSize(size.x, size.y * (26.0f / 64.0f));
	sf::Vector2f apparentPos = { pos.x , pos.y + (38.0f / 64.0f) * size.y };
	this->size = apparentSize;
	this->position = apparentPos;
	this->shape->setSize(apparentSize);
	this->shape->setPosition(apparentPos);
}


BouncyPath::~BouncyPath(){}



void BouncyPath::Load(std::shared_ptr<Engine::ResourceManager> resources) {
    int textureX = this->textureId % GMNumber::TEXTURE_COUNT_X;
    int textureY = (int)(this->textureId / GMNumber::TEXTURE_COUNT_X);
    int testsize = GMNumber::TEXTURE_SIZE;
    this->sprite.setTexture(resources->GetTexture(ResourceId::TILE_TEXTURE));
    this->sprite.setTextureRect(sf::IntRect(textureX * testsize,
        textureY * testsize, testsize, testsize));

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
    window->draw(this->sprite);
}

