#include"Collectable.h"

Collectable::Collectable(const int id, const int colid, const float mass,
    const unsigned int points, const int textureId,
    const sf::Vector2f pos, const sf::Vector2f size) :
    point(points), canBeDeleted(false),
    GameShape(id, colid, mass, pos, size,
        { 0.0f,0.0f }, { 0.0f,0.0f }, { 0.0f,0.0f }, 0.0f)  , textureId(0),
	frameClock(), frameSize(4), frame(0),
    textureX(0) , textureY(0) , testsize(0){
    this->textureId = textureId;
    this->shape->setPosition(pos);
    this->shape->setSize(size);
    this->sprite.setPosition(pos);
}

Collectable::~Collectable(){}

void Collectable::Load(std::shared_ptr<Engine::ResourceManager> resources) {
    this->textureX = this->textureId % GMNumber::TEXTURE_COUNT_X;
    this->textureY = (int)(this->textureId / GMNumber::TEXTURE_COUNT_X);
    this->testsize = GMNumber::TEXTURE_SIZE;
    this->sprite.setTexture(resources->GetTexture(ResourceId::TILE_TEXTURE));
    this->sprite.setTextureRect(sf::IntRect(this->textureX * this->testsize,
        this->textureY * this->testsize, this->testsize, this->testsize));

    if (GMNumber::IS_PADDING) {
        this->shape->setOutlineThickness(0.5f);
        this->shape->setOutlineColor(sf::Color::Black);
    }
}

void Collectable::Update(const float& dT) {
	//if (this->frameClock.getElapsedTime().asSeconds() > 0.4f) {
	//	this->frame = (this->frame + 1) % this->frameSize;
 //       this->sprite.setTextureRect(sf::IntRect( this->testsize*(this->textureX + this->frame),
 //           this->textureY * this->testsize , this->testsize, this->testsize));
 //       this->frameClock.restart();
	//}
}


void Collectable::Draw(std::shared_ptr<sf::RenderWindow>window) {
    window->draw(this->sprite);
}
