#include "Rect.h"
#include"../Body/ContactMechanic.h"
#include"../PhysicUtility/Utility.h"


PlayerReference playerReference;

Rect::Rect(const int id, const int colid, const float mass, const sf::Vector2f pos, const sf::Vector2f size,
	const sf::Vector2f coeffOfRest, const float coeffOfFriction):
	GameShape(id, colid, mass, pos, size, {0.0f,0.0f}, { 0.0f,0.0f }
		,coeffOfRest, coeffOfFriction), isLarge(false) ,
	sizeOfSprite(GMNumber::PLAYER_SPRITE_SIZE), airResistanceConstants(){
	FindMaxVelocities();
	JumpTimeConstraintsFinder();
	FindAirResistanceConstants();
}

Rect::~Rect(){}

inline void Rect::SetPosition(const sf::Vector2f position){
	this->position = position;
	this->shape->setPosition(position);
	this->sprite.setPosition(position);
}

inline void Rect::SetSize(const sf::Vector2f size){
	if (size.x == GMNumber::SMALL_BALL_SIZE) {this->isLarge = false;}
	else {this->isLarge = true;}
	this->size = size;
	this->shape->setSize(size);
	this->sprite.setScale(size.x / sizeOfSprite, size.y / sizeOfSprite);
}



void Rect::Load(std::shared_ptr<Engine::ResourceManager> resources) {
	this->text.setFont(resources->GetFont(ResourceId::MAIN_FONT));
	this->texture = resources->GetTexture(ResourceId::PLAYER_TEXTURE);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, sizeOfSprite, sizeOfSprite));
	this->sprite.setPosition(this->position);
	this->sprite.setScale(this->size.x/ sizeOfSprite, this->size.y/ sizeOfSprite);
	this->text.setCharacterSize(15);
}

void Rect::Update(const float& dt) {
	this->DT = dt;	
	ApplyGravity();
	MovementUpdate();
	MOvementAnimation();
	ApplyAirResistance();
	this->shape->setPosition(NewPosition(DT));
	this->sprite.setPosition(this->shape->getPosition());
}


void Rect::Draw(std::shared_ptr<sf::RenderWindow> window) {
	window->draw(this->sprite);
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
	this->sprite.setPosition(position);
}

void Rect::DrawStats(std::shared_ptr<sf::RenderWindow> window){
	window->draw(text);
}


void Rect::MovementUpdate() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->velocity.x += -ApplyMotionForce.MOVEMENT_FORCE;
		this->bools.isMovingLeft = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->velocity.x += ApplyMotionForce.MOVEMENT_FORCE;
		this->bools.isMovingRight = true;
	}
	else {
		this->bools.isMovingLeft = false;
		this->bools.isMovingRight = false;
	}
	JumpUpdate();
}

void Rect::MOvementAnimation() {
	// Check if the player is not moving or moving both left and right simultaneously
	if ((bools.isMovingLeft == bools.isMovingRight) && (velocity.x == 0)) {
		return;
	}
	// Check if enough time has passed to update the animation frame
	if (gameClock.movementAnimaton.getElapsedTime().asSeconds()
		>= TimeConstraints.MOVEMENT_ANIMATION_TIME_CONSTRAINTS) {
		// Update the animation frame count and wrap around if necessary
		frameCount.movementFrameCount = (frameCount.movementFrameCount + 1)
			% frameMaxSize.movementFrameSize;
		// Restart the animation clock
		gameClock.movementAnimaton.restart();
		// Update the sprite's texture rectangle to display the next frame
		this->sprite.setTextureRect(sf::IntRect(sizeOfSprite * frameCount.movementFrameCount,
			0, sizeOfSprite, sizeOfSprite));
	}
}




void Rect::DisplayPositionAndVelocity() {
	this->text.setString("Position = " + std::to_string((int)this->position.x) + " "
		+ std::to_string((int)this->position.y) + "\n"
		+ "Velocity = " + std::to_string((int)this->velocity.x) + " "
		+ std::to_string((int)this->velocity.y));
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
	this->maxVelocity = { GMNumber::COEFF_MAX_VELOCITY_X / this->mass ,
   std::sqrt((this->mass * GMNumber::COEFF_MAX_VELOCITY_Y)/(size* size))};

	if (std::abs(maxVelocity.x) > GMNumber::ASOLUTE_MAX_VELOCITY.x) {
		maxVelocity.x = GMNumber::ASOLUTE_MAX_VELOCITY.x;
	}
	if (std::abs(maxVelocity.y) > GMNumber::ASOLUTE_MAX_VELOCITY.y) {
		maxVelocity.y = GMNumber::ASOLUTE_MAX_VELOCITY.y;
	}
}

void Rect::FindAirResistanceConstants(){
	float hardcoadedsize = GMNumber::HARDCOADED_SMALL_BALL_SIZE;
	float area = GMNumber::PI * hardcoadedsize * hardcoadedsize * 0.25f;
	this->airResistanceConstants.x = 6.0f * area / this->mass;
	this->airResistanceConstants.y = 3.5f * area / this->mass;
}

inline sf::Vector2f& Rect::NewPosition(const float& dt) {
	this->velocity += this->acceleration * dt;
	float clampY = (!this->isLarge) ? this->maxVelocity.y : 1.25f * this->maxVelocity.y;
	sf::Vector2f clapVecelocity = { this->maxVelocity.x ,clampY };
	VectorOperation::ClampForVector(this->velocity, -clapVecelocity, clapVecelocity);
	this->oldPosition = this->position;
	this->position += this->velocity * dt;
	this->acceleration.y = 0.0f;
	return this->position;
}

void Rect::JumpUpdate() {
	const float jumpConstraints = isLarge
		? TimeConstraints.JUMP_TIME_CONSTRAINTS * GMNumber::ELASTICITY_RATIO
		: TimeConstraints.JUMP_TIME_CONSTRAINTS;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		playerReference.canjump && 
		gameClock.jumpClock.getElapsedTime().asSeconds() >= jumpConstraints) {
		float jumpForce = isLarge
			? ApplyMotionForce.JUMP_FORCE * GMNumber::ELASTICITY_RATIO
			: ApplyMotionForce.JUMP_FORCE;
		playerReference.canjump = false;
		this->velocity.y = -jumpForce;
		this->gameClock.jumpClock.restart();
	}
}


void Rect::JumpTimeConstraintsFinder() {
	TimeConstraints.JUMP_TIME_CONSTRAINTS = (ApplyMotionForce.JUMP_FORCE / GMNumber::GRAVITY);
}

void Rect::ApplyAirResistance() {
	float apparentConst = (!this->isLarge) ? this->airResistanceConstants.x : this->airResistanceConstants.y;
	float airresistance = -(float)Sign(this->velocity.x) * this->velocity.x / (apparentConst * this->DT * this->velocity.x + 1);
	this->velocity.x += airresistance;
}
