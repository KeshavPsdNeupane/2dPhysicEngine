#include "Rect.h"
#include"../Body/ContactMechanic.h"
#include"../PhysicUtility/Utility.h"

PlayerBools playerRefenceBools;

Rect::Rect(const int id, const int colid, const float mass, const sf::Vector2f pos, const sf::Vector2f size,
	const sf::Vector2f coeffOfRest, const sf::Vector2f coeffOfFriction , const sf::Font& font):
	GameShape(id, colid, mass, pos, size, {0.0f,0.0f}, { 0.0f,0.0f }
		,coeffOfRest, coeffOfFriction),points(0) , isLarge(false),
	lives(3){
	this->circle.setRadius(size.x / 2.0f);
	this->circle.setPosition(pos);
	FindMaxVelocities();
}

Rect::~Rect(){}

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



void Rect::Load(std::shared_ptr<Engine::ResourceManager> resources) {
	this->text.setFont(resources->GetFont(ResourceId::MAIN_FONT));
	this->shape->setFillColor(sf::Color::Red);
	this->circle.setFillColor(sf::Color::Red);
	this->shape->setOutlineColor(sf::Color::Black);
	this->shape->setOutlineThickness(1.0f);
	this->text.setCharacterSize(15);
}

void Rect::Update(const float& dt) {
	this->DT = dt;	
	ApplyGravity();
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
		ApplyForce({ - ApplyMotionForce.MOVEMENT_FORCE   , 0.0f });
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		ApplyForce({ ApplyMotionForce.MOVEMENT_FORCE   , 0.0f });
	}
	else {
		acceleration.x = 0;
	}
	JumpUpdate();
}


void Rect::DisplayPositionAndVelocity() {
	this->text.setString("Position = " + std::to_string((int)this->position.x) + " "
		+ std::to_string((int)this->position.y) + "\n"
		+ "Velocity = " + std::to_string((int)this->velocity.x) + " "
		+ std::to_string((int)this->velocity.y) + "\n"
		+ "Accleration = " + std::to_string((int)this->acceleration.x) + " "
		+ std::to_string((int)this->acceleration.y) 
	    + " \n\nLives = " + std::to_string(this->lives));
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
 */
	float size = GMNumber::SMALL_BALL_SIZE;
	if (this->mass == 0) { this->mass = 1.0f; }
	this->maxvelocity = { GMNumber::COEFF_MAX_VELOCITY_X / this->mass ,
   std::sqrt((this->mass * GMNumber::COEFF_MAX_VELOCITY_Y)/(size* size))};

	if (std::abs(maxvelocity.x) > GMNumber::ASOLUTE_MAX_VELOCITY.x) {
		maxvelocity.x = GMNumber::ASOLUTE_MAX_VELOCITY.x;
	}
	if (std::abs(maxvelocity.y) > GMNumber::ASOLUTE_MAX_VELOCITY.y) {
		maxvelocity.y = GMNumber::ASOLUTE_MAX_VELOCITY.y;
	}
}

inline sf::Vector2f& Rect::NewPosition(const float& dt) {
	this->velocity += this->acceleration * dt;
	VectorOperation::ClampForVector(this->velocity, -maxvelocity, maxvelocity);
	this->oldPosition = this->position;
	this->position += this->velocity * dt;
	this->acceleration.y = 0.0f;
	return this->position;
}

void Rect::JumpUpdate() {
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		&& playerRefenceBools.canJumping ) {
		playerRefenceBools.canJumping = false;
		// below is use of ternary operator
		this->velocity.y = isLarge? -ApplyMotionForce.JUMP_FORCE * GMNumber::ELASTICITY_RATIO
			: -ApplyMotionForce.JUMP_FORCE;
	}
}
