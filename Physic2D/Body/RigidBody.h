#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "../PhysicUtility/Utility.h"
#include<cmath>
#include"../PhysicUtility/Utility.h"
class RigidBody {
public:
    int index;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f coefficientOfRestitution;
    sf::Vector2f ceofficientOfFriction;
    float mass;
private:
    sf::Vector2f maxvelocity;
public:
    RigidBody()
        : position(0.0f, 0.0f), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), mass(1.0f), index()
        , coefficientOfRestitution(0.0f, 0.0f), ceofficientOfFriction(0.0f, 0.0f) {}

    RigidBody(const int& id, const float& mass, const sf::Vector2f& position, const sf::Vector2f& size,
        const sf::Vector2f& velocity, const sf::Vector2f& acceleration,
        const sf::Vector2f& coefficientOfRestitution, const sf::Vector2f& ceofficientOfFriction)
        : mass(mass), position(position), velocity(velocity),
        acceleration(acceleration), index(id),
        coefficientOfRestitution(coefficientOfRestitution),
        ceofficientOfFriction(ceofficientOfFriction) {

        SetLengthForTerminalVelocity(size.x);
    }

public:
    inline  void ApplyForce(const sf::Vector2f& force) {
        if (mass != 0) {
            acceleration += force / mass;
        }
    }


    inline void AddAcceleration(const sf::Vector2f& acceleration) {this->acceleration += acceleration;}
    inline void AddVelocity(const sf::Vector2f& deltaVelocity) {velocity += deltaVelocity;}
    inline sf::Vector2f& GetVelocity() {return this->velocity; }
  

    inline sf::Vector2f& NewPosition(const float& dt) {
        this->velocity += this->acceleration * dt;
        if (this->velocity.y > maxvelocity.y) this->velocity.y = maxvelocity.y;
        if (this->velocity.y < -maxvelocity.y) this->velocity.y = -maxvelocity.y;
        if (this->velocity.x > maxvelocity.x) this->velocity.x = maxvelocity.x;
        if (this->velocity.x < -maxvelocity.x) this->velocity.x = -maxvelocity.x;
        this->position += this->velocity * dt;
        this->acceleration.y = 0;
        return this->position;
    }


private:
    inline void SetLengthForTerminalVelocity(const float& length) { 
        if (this->mass == 0) { this->mass = 1.0f; }
        this->maxvelocity = { GMNumber::COEFF_MAX_VELOCITY_X / this->mass ,
            GMNumber::COEFF_MAX_VELOCITY_Y* std::sqrt(mass) / length };
        if (std::abs(maxvelocity.x) > GMNumber::ABSOLUTE_MAX_VELOCITY_X) {
            maxvelocity.x = GMNumber::ABSOLUTE_MAX_VELOCITY_X;
        }
        if (std::abs(maxvelocity.y) > GMNumber::ABSOLUTE_MAX_VELOCITY_Y) {
            maxvelocity.y = GMNumber::ABSOLUTE_MAX_VELOCITY_Y;
        }
    }
};
