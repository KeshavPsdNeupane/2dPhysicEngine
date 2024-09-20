#include "Path.h"
#include"../PhysicUtility/Utility.h"
Path::Path(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Vector2f& velocity,
	const sf::Vector2f& accleration, const float& mass)
	: id(1), frame(2, mass, pos, size ,velocity, accleration,
		{GMNumber::COEFF_OF_RESTITUTION_PATH , GMNumber::COEFF_OF_RESTITUTION_PATH },
		{GMNumber::COEFF_OF_FRICTION_PATH,GMNumber::COEFF_OF_FRICTION_PATH }) {
	this->path.setPosition(pos);
	this->path.setSize(size);
}

void Path::Load(){
	this->path.setFillColor(sf::Color::Blue);
}

void Path::Update(const float& DT){
	if (this->frame.velocity.x != 0 || this->frame.velocity.y != 0) {
	this->path.setPosition(this->frame.NewPosition(DT));
	}
}

void Path::Draw(std::shared_ptr<sf::RenderWindow> window){
	window->draw(this->path);
}
