#include "Rect.h"
#include"../Body/ContactMechanic.h"
#include"../GameObjects.h"
#include"../PhysicUtility/Utility.h"

Rect::Rect(const int index, const sf::Vector2f& pos, const sf::Vector2f& size)
	:frame(index, 60.0f, pos, size, { GMNumber::ZERO, GMNumber::ZERO }, { GMNumber::ZERO , GMNumber::ZERO },
		{ GMNumber::COEFF_OF_RESTITUTION_OBJECT , GMNumber::COEFF_OF_RESTITUTION_OBJECT },
		{ GMNumber::COEFF_OF_FRICTION_OBJECT , GMNumber::COEFF_OF_FRICTION_OBJECT }),
	DT(0.0f), gravity(0.f, 10.0f * 50.f) {
	this->shape.setPosition(pos);
	this->shape.setSize(size);
	//this->frame.SetLengthForTerminalVelocity(size.x/50.0f);
	this->font = gameObject.resource.GetFont();
	this->text.setFont(this->font);
}

inline void Rect::SetIndex(const float& index) {this->frame.index = index;}
inline void Rect::SetMass(const float& mass) { this->frame.mass = mass; }
inline void Rect::SetPosition(const sf::Vector2f& position) {this->frame.position = position;}
inline void Rect::SetVelocity(const sf::Vector2f& velocity) {this->frame.velocity = velocity;}
inline void Rect::SetAccleration(const sf::Vector2f& accleration) {this->frame.acceleration = accleration;}
inline void Rect::SetCoefficientOfRestitution(const sf::Vector2f& E) {this->frame.coefficientOfRestitution = E;}
inline void Rect::SetCoefficientOfFriction(const sf::Vector2f& u) {this->frame.ceofficientOfFriction = u;}

void Rect::Load(){
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setOutlineThickness(2.0f);
	this->text.setCharacterSize(15.0f);
	this->text.setPosition({ 50,00 });
}

void Rect::Update(const float& dt) {
	this->DT = dt;
	MovementUpdate();
	this->frame.AddAcceleration(this->gravity);
	if (frame.velocity.x != 0 || frame.velocity.y != 0) {
		for (int i = 0; i < gameObject.path.size(); ++i) {
			this->contact.Friction(this->shape, this->frame,
				gameObject.path[i].GetShape(), gameObject.path[i].GetFrame(), this->DT);
		}
	}
	this->shape.setPosition(this->frame.NewPosition(DT));
	for (int i = 0; i < gameObject.path.size(); ++i) {
		this->contact.CollisionDetection(this->shape, this->frame,
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

void Rect::MovementUpdate() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->frame.ApplyForce( {-35775.0f , 0});
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->frame.ApplyForce({ 35775.0f   , 0 });
	}
	else {
		this->frame.acceleration.x = 0;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		this->frame.velocity.y = -250; 
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->frame.velocity.y = 30;  
	}
}

void Rect::DisplayPositionAndVelocity(){
	this->text.setString("Position = " + std::to_string((int)this->frame.position.x) + " " 
		+ std::to_string((int)this->frame.position.y) + "\n"
		+ "Velocity = " + std::to_string((int)this->frame.velocity.x) + " "
		+ std::to_string((int)this->frame.velocity.y));
}
