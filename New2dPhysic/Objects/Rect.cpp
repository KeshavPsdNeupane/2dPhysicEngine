#include "Rect.h"
#include"../Body/ContactMechanic.h"
#include"../GameObjects.h"
#include"../PhysicUtility/Utility.h"


Rect::Rect(const int id, const int colid, const float mass, const sf::Vector2f pos, const sf::Vector2f size,
	const sf::Vector2f velocity, const sf::Vector2f accleration, const sf::Vector2f coeffOfRest, const sf::Vector2f coeffOfFriction)
	:GameShape(id, colid, 60.0f, pos, size, velocity, accleration, coeffOfRest,coeffOfFriction),
	DT(0.0f) {
	this->shape->setSize(GetSize());
	this->shape->setPosition(GetPosition());
	FindMaxVelocities();
	this->font = gameObject.resource.GetFont();
	this->text.setFont(this->font);
}


void Rect::Load() {
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
	this->shape->setPosition(NewPosition(DT));

}




void Rect::Draw(std::shared_ptr<sf::RenderWindow> window) {
	window->draw(*shape);
	window->draw(text);
}

void Rect::ReCentered() {
	if (position.y > 600 - size.y) {
		position.y = 600 - size.y;
		oldPosition.y = 600 - size.y;
	}
	if (position.y < 0) {
		position.y = 0;
		oldPosition.y = 0;
	}
	if (position.x > 800 - size.x) {
		position.x = 800 - size.x;
		oldPosition.x = 800 - size.x;
	}
	if (position.x < 0) {
		position.x = 0;
		oldPosition.x = 0;
	}
	this->shape->setPosition(position);
}


void Rect::MovementUpdate() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		ApplyForce({ -GMNumber::MOVEMENT_FORCE , 0 });
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		ApplyForce({ GMNumber::MOVEMENT_FORCE  , 0 });
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

void Rect::DisplayPositionAndVelocity() {
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
   GMNumber::COEFF_MAX_VELOCITY_Y * std::sqrt(mass) / this->size.x};

	if (std::abs(maxvelocity.x) > GMNumber::ABSOLUTE_MAX_VELOCITY_X) {
		maxvelocity.x = GMNumber::ABSOLUTE_MAX_VELOCITY_X;
	}
	if (std::abs(maxvelocity.y) > GMNumber::ABSOLUTE_MAX_VELOCITY_Y) {
		maxvelocity.y = GMNumber::ABSOLUTE_MAX_VELOCITY_Y;
	}
}

inline sf::Vector2f& Rect::NewPosition(const float& dt) {
	this->velocity += this->acceleration * dt;
	if (this->velocity.y > maxvelocity.y) { this->velocity.y = maxvelocity.y; }
	if (this->velocity.y < -maxvelocity.y) { this->velocity.y = -maxvelocity.y; }
	if (this->velocity.x > maxvelocity.x) { this->velocity.x = maxvelocity.x; }
	if (this->velocity.x < -maxvelocity.x) { this->velocity.x = -maxvelocity.x; }
	this->oldPosition = this->position;
	this->position += this->velocity * dt;
	this->acceleration.y = 0;
	return this->position;
}
