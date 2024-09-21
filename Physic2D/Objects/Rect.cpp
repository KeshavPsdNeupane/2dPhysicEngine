#include "Rect.h"
#include"../Body/ContactMechanic.h"
#include"../GameObjects.h"
#include"../PhysicUtility/Utility.h"

Rect::Rect(const int index, const sf::Vector2f& pos, const sf::Vector2f& size)
	:RigidBody(index, 60.0f, pos, size, { GMNumber::ZERO, GMNumber::ZERO }, { GMNumber::ZERO , GMNumber::ZERO },
	//	{1,0.3f} , {0,0}),
	{ GMNumber::COEFF_OF_RESTITUTION_OBJECT , GMNumber::COEFF_OF_RESTITUTION_OBJECT },
		{ GMNumber::COEFF_OF_FRICTION_OBJECT , GMNumber::COEFF_OF_FRICTION_OBJECT }),
	DT(0.0f), gravity(0.f, 10.0f * 50.f) {
	this->shape.setPosition(pos);
	this->shape.setSize(size);
	this->font = gameObject.resource.GetFont();
	this->text.setFont(this->font);
}



void Rect::Load(){
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setOutlineThickness(2.0f);
	this->text.setCharacterSize(15);
	this->text.setPosition({ 50,00 });
}

void Rect::Update(const float& dt) {
	this->DT = dt;
	MovementUpdate();
	AddAcceleration(this->gravity);
	for (int i = 0; i < gameObject.path.size(); ++i) {
		this->contact.Friction(this->shape, *this,
			gameObject.path[i].GetShape(), gameObject.path[i].GetFrame(), this->DT);
	}
	//std::cout << " acceleration = " << acceleration.x << " " << acceleration.y << std::endl;
	this->shape.setPosition(NewPosition(DT));
	for (int i = 0; i < gameObject.path.size(); ++i) {
		this->contact.CollisionDetection(this->shape, *this,
			gameObject.path[i].GetShape(), gameObject.path[i].GetFrame());
	}
	DisplayPositionAndVelocity();
	ReCentered();
}


void Rect::Draw(std::shared_ptr<sf::RenderWindow> window){
	window->draw(shape);
	window->draw(text);
}

void Rect::ReCentered(){
	auto& pos = this->position;
	if (pos.y > 600 - 50) {
		this->position = sf::Vector2f(pos.x, 0.0f);
		this->shape.setPosition(this->position);
	}
	if (pos.x > 800 - 50) {
		this->position = sf::Vector2f(0.0f, pos.y);
		this->shape.setPosition(this->position);
	}

}

void Rect::MovementUpdate() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		ApplyForce({ -35775.0f , 0 });
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		ApplyForce({ 35775.0f   , 0 });
	}
	else {
		acceleration.x = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		velocity.y = -250;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		velocity.y = 30;
	}
}

void Rect::DisplayPositionAndVelocity(){
	this->text.setString("Position = " + std::to_string((int)this->position.x) + " " 
		+ std::to_string((int)this->position.y) + "\n"
		+ "Velocity = " + std::to_string((int)this->velocity.x) + " "
		+ std::to_string((int)this->velocity.y) + "\n"
		+ "Accleration = " + std::to_string((int)this->acceleration.x) + " "
		+ std::to_string((int)this->acceleration.y));
}
