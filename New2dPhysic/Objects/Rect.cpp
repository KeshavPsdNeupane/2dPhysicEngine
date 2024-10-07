#include "Rect.h"
#include"../Body/ContactMechanic.h"
#include"../GameObjects.h"
#include"../PhysicUtility/Utility.h"


Rect::Rect(const int id, const sf::Vector2f& pos, const sf::Vector2f& size)
	:GameShape(id, 60.0f, pos, size, {GMNumber::ZERO, GMNumber::ZERO}, {GMNumber::ZERO , GMNumber::ZERO},
	{ GMNumber::COEFF_OF_RESTITUTION_OBJECT_X , GMNumber::COEFF_OF_RESTITUTION_OBJECT_Y },
		{ GMNumber::COEFF_OF_FRICTION_OBJECT , GMNumber::COEFF_OF_FRICTION_OBJECT }),
	DT(0.0f) {

	this->shape->setSize(GetSize());
	this->shape->setPosition(GetPosition());
	FindMaxVelocities();
	this->font = gameObject.resource.GetFont();
	this->text.setFont(this->font);
	//gameObject.grid.AddObject(shape, *this, *this);
}




void Rect::Load(){
	this->shape->setFillColor(sf::Color::Red);
	this->shape->setOutlineColor(sf::Color::Black);
	this->shape->setOutlineThickness(2.0f);
	this->text.setCharacterSize(15);
	this->text.setPosition({ 50.0f,00.0f });
}

void Rect::Update(const float& dt) {
	this->DT = dt;
	MovementUpdate();
	AddAcceleration(sf::Vector2f(GMNumber::ZERO, GMNumber::GRAVITY));
	DisplayPositionAndVelocity();
	auto oldPosition = this->shape->getPosition();
	this->shape->setPosition(NewPosition(DT));
	ReCentered();
}


void Rect::CollisionRedirection(std::shared_ptr<GameShape> playerShape,
	std::shared_ptr<GameShape> otherShape,ContactMech& contact){
	std::cout << " Player only detect, dont handle collision" << std::endl;
}


void Rect::Draw(std::shared_ptr<sf::RenderWindow> window){
	window->draw(*shape);
	window->draw(text);
}

void Rect::ReCentered(){
	auto& pos = this->position;
	if (pos.y > 600 - 50) {
		this->position = sf::Vector2f(pos.x, 0.0f);
		this->shape->setPosition(this->position);
	}
	if (pos.x > 800 - 50) {
		this->position = sf::Vector2f(0.0f, pos.y);
		this->shape->setPosition(this->position);
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

inline void Rect::FindMaxVelocities() {
	if (this->mass == 0) { this->mass = 1.0f; }
	this->maxvelocity = { GMNumber::COEFF_MAX_VELOCITY_X / this->mass ,
   GMNumber::COEFF_MAX_VELOCITY_Y * std::sqrt(mass) / this->shape->getGlobalBounds().width};

	if (std::abs(maxvelocity.x) > GMNumber::ABSOLUTE_MAX_VELOCITY_X) {
		maxvelocity.x = GMNumber::ABSOLUTE_MAX_VELOCITY_X;
	}
	if (std::abs(maxvelocity.y) > GMNumber::ABSOLUTE_MAX_VELOCITY_Y) {
		maxvelocity.y = GMNumber::ABSOLUTE_MAX_VELOCITY_Y;
	}
}

inline sf::Vector2f& Rect::NewPosition(const float& dt){
	this->velocity += this->acceleration * dt;
	if (this->velocity.y > maxvelocity.y) this->velocity.y = maxvelocity.y;
	if (this->velocity.y < -maxvelocity.y) this->velocity.y = -maxvelocity.y;
	if (this->velocity.x > maxvelocity.x) this->velocity.x = maxvelocity.x;
	if (this->velocity.x < -maxvelocity.x) this->velocity.x = -maxvelocity.x;
	this->position += this->velocity * dt;
	this->acceleration.y = 0;
	return this->position;
}
