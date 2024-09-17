#include "Path.h"

Path::Path(const sf::Vector2f& pos, const sf::Vector2f& size)
	: id(1), frame(2, 10000, pos, { 0,0 }, { 0,0 } , { 1.0f , .3f }) {
	this->path.setPosition(pos);
	this->path.setSize(size);
}

void Path::Load(){
	this->path.setFillColor(sf::Color::Blue);
}

void Path::Update(){
}

void Path::Draw(std::shared_ptr<sf::RenderWindow> window){
	window->draw(this->path);
}
