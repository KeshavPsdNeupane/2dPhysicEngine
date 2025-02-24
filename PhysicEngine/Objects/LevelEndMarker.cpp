#include "LevelEndMarker.h"

LevelEndMarker::LevelEndMarker(const int id, const int colid,
    const int textureId,
    const sf::Vector2f pos, const sf::Vector2f size) :
    GameShape(id, colid, 10.0f, pos, size,
        { 0.0f,0.0f }, { 0.0f,0.0f }, { 0.0f,0.0f }, 0.0f),
    textureId(textureId) {
    this->sprite.setPosition(pos);
    this->shape->setSize(size);
    this->shape->setPosition(pos);
}

LevelEndMarker::~LevelEndMarker() {}

void LevelEndMarker::Load(std::shared_ptr<Engine::ResourceManager> resources) {
    int textureX = this->textureId % GMNumber::TEXTURE_COUNT_X;
    int textureY = (int)(this->textureId / GMNumber::TEXTURE_COUNT_X);
    int testsize = GMNumber::TEXTURE_SIZE;
    this->sprite.setTexture(resources->GetTexture(ResourceId::TILE_TEXTURE));
    this->sprite.setTextureRect(sf::IntRect(textureX * testsize,
        textureY * testsize, testsize, testsize));

    if (GMNumber::IS_PADDING) {
        this->shape->setOutlineThickness(0.5f);
        this->shape->setOutlineColor(sf::Color::Black);
    }
}

void LevelEndMarker::Update(const float& dT) {
    if (this->velocity.x != 0 || this->velocity.y != 0) {
        this->shape->setPosition(this->NewPosition(dT));
    }
}


void LevelEndMarker::Draw(std::shared_ptr<sf::RenderWindow>window) {
    window->draw(this->sprite);
}

