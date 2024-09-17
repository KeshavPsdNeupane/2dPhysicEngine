#include "Rect.h"
#include"../Body/Collision.h"
#include"../GameObjects.h"

Rect::Rect(const sf::Vector2f& pos, const sf::Vector2f& size)
	:frame(1, 10, pos, { 0.0f,0.0f }, { 0.0f , 0.0f }, { 0.05f ,0.1f }), DT(0.0f), gravity(0.f, 100.f), id(0) {
	this->shape.setPosition(pos);
	this->shape.setSize(size);
}

void Rect::Load(){
	this->shape.setFillColor(sf::Color::Red);
}

void Rect::Update(const float& dt){ 
	this->shape.setPosition(this->frame.NewPositionA(this->frame.acceleration + gravity, DT));
	this->DT = dt;
	this->shape.setPosition(this->frame.NewPositionA(this->frame.acceleration + gravity, DT));
	gameObject.collision.CollisionDetection(shape, frame, gameObject.path.GetShape(), gameObject.path.GetFrame());
	std::cout << "Pos = " << frame.position.x << " " << frame.position.y << std::endl;
	ReCentered();
}

void Rect::Draw(std::shared_ptr<sf::RenderWindow> window){
	window->draw(shape);
}

void Rect::ReCentered(){
	auto& pos = this->frame.position;
	if (pos.y > 600 - 50) {
		this->frame.position = sf::Vector2f(pos.x, 0.0f);
		this->shape.setPosition(this->frame.position);
	}
	if (pos.x > 800 - 50) {
		this->frame.position = sf::Vector2f(0.0f, pos.y);
		this->shape.setPosition(this->frame.position);
	}
}
