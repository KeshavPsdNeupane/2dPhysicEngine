#include "Rect.h"
#include"../Body/ContactMechanic.h"
#include"../GameObjects.h"
#include"../PhysicUtility/Utility.h"


Rect::Rect(const int id, const int colid, const float mass, const sf::Vector2f pos, const sf::Vector2f size,
	const sf::Vector2f coeffOfRest, const sf::Vector2f coeffOfFriction):
	GameShape(id, colid, mass, pos, size, {0.0f,0.0f}, { 0.0f,0.0f }
		,coeffOfRest, coeffOfFriction),points(0){
	this->circle.setRadius(size.x / 2.0f);
	this->circle.setPosition(pos);
	FindMaxVelocities();
	this->font = gameObject.resource.GetFont();
	this->text.setFont(this->font);
}

inline void Rect::SetPosition(const sf::Vector2f position){
	this->position = position;
	this->shape->setPosition(position);
	this->circle.setPosition(position);
}

inline void Rect::SetSize(const sf::Vector2f size){
	if (size.x == GMNumber::SMALL_BALL_SIZE) {this->isLarge = false;}
	else {this->isLarge = true;}
	this->size = size;
	this->shape->setSize(size);
	this->circle.setRadius(size.x * 0.5f);
}



void Rect::Load() {
	this->shape->setFillColor(sf::Color::Red);
	this->circle.setFillColor(sf::Color::Red);
	this->shape->setOutlineColor(sf::Color::Black);
	this->shape->setOutlineThickness(1.0f);
	this->text.setCharacterSize(15);
}

void Rect::Update(const float& dt) {
	this->DT = dt;
	AddAcceleration(sf::Vector2f(0.0f, GMNumber::GRAVITY));
	MovementUpdate();
	this->shape->setPosition(NewPosition(DT));
}


void Rect::Draw(std::shared_ptr<sf::RenderWindow> window) {
	window->draw(text);
	window->draw(this->circle);
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
	this->circle.setPosition(position);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
		float bigsize = GMNumber::BIG_BALL_SIZE;
		SetSize({ bigsize ,bigsize });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		float smallsize = GMNumber::SMALL_BALL_SIZE;
		SetSize({ smallsize,smallsize });
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
	/**
 * @brief Calculates and sets the maximum velocities for the Rect object based on its mass and size.
 *
 * This function computes the maximum velocities in both the x and y directions for the Rect object.
 * The maximum velocities are determined using coefficients and thresholds defined in the GMNumber namespace.
 * The calculated maximum velocities are stored in the `maxvelocity` member variable.
 *
 * The maximum velocity in the x direction is calculated as:
 * maxvelocity.x = GMNumber::COEFF_MAX_VELOCITY_X / mass
 *
 * The maximum velocity in the y direction is calculated as:
 * maxvelocity.y = GMNumber::COEFF_MAX_VELOCITY_Y * sqrt(mass) / size.x
 *
 * If the calculated maximum velocities exceed the absolute maximum velocities defined in GMNumber,
 * they are clamped to the absolute maximum values.
 *
 * If the mass of the Rect object is zero, it is set to 1.0f to avoid division by zero.
 *
 *
 * @note This function should be called whenever the mass or size of the Rect object changes.
 */
	if (this->mass == 0) { this->mass = 1.0f; }
	this->maxvelocity = { GMNumber::COEFF_MAX_VELOCITY_X / this->mass ,
   std::sqrt((this->mass * GMNumber::COEFF_MAX_VELOCITY_Y)/(this->size.x * this->size.y))};

	if (std::abs(maxvelocity.x) > GMNumber::ABSOLUTE_MAX_VELOCITY_X) {
		maxvelocity.x = GMNumber::ABSOLUTE_MAX_VELOCITY_X;
	}
	if (std::abs(maxvelocity.y) > GMNumber::ABSOLUTE_MAX_VELOCITY_Y) {
		maxvelocity.y = GMNumber::ABSOLUTE_MAX_VELOCITY_Y;
	}
	//std::cout << " max vel = " << maxvelocity.x << " " << maxvelocity.y << std::endl;
}

inline sf::Vector2f& Rect::NewPosition(const float& dt) {
	this->velocity += this->acceleration * dt;
	if (this->velocity.y > maxvelocity.y) { this->velocity.y = maxvelocity.y; }
	if (this->velocity.y < -maxvelocity.y) { this->velocity.y = -maxvelocity.y; }
	if (this->velocity.x > maxvelocity.x) { this->velocity.x = maxvelocity.x; }
	if (this->velocity.x < -maxvelocity.x) { this->velocity.x = -maxvelocity.x; }
	this->oldPosition = this->position;
	this->position += this->velocity * dt;
	this->acceleration.y = 0.0f;
	return this->position;
}
