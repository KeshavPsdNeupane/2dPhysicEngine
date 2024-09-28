#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "../PhysicUtility/Utility.h"
#include<cmath>
#include"../PhysicUtility/Utility.h"
class RigidBody {
public:
    int ID;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f coefficientOfRestitution;
    sf::Vector2f ceofficientOfFriction;
    float mass;
protected:
    sf::Vector2f maxvelocity;

public:
    RigidBody()
        : position(0.0f, 0.0f),
        velocity(0.0f, 0.0f),
        acceleration(0.0f, 0.0f),
        mass(1.0f), ID(),
        coefficientOfRestitution(0.0f, 0.0f),
        ceofficientOfFriction(0.0f, 0.0f), 
        maxvelocity(0,0) {}

    RigidBody(const int& id, const float& mass, const sf::Vector2f& position, const sf::Vector2f& size,
        const sf::Vector2f& velocity, const sf::Vector2f& acceleration,
        const sf::Vector2f& coefficientOfRestitution, const sf::Vector2f& ceofficientOfFriction)
        :ID(id), mass(mass),
        position(position),
        velocity(velocity),
        acceleration(acceleration), 
        coefficientOfRestitution(coefficientOfRestitution),
        ceofficientOfFriction(ceofficientOfFriction) {}



public:
    inline void SetIndex(const int& index) { this->ID = index; }
    inline void SetMass(const float& mass) { this->mass = mass; }
    inline void SetPosition(const sf::Vector2f& position) { this->position = position; }
    inline void SetVelocity(const sf::Vector2f& velocity) { this->velocity = velocity; }
    inline void SetAccleration(const sf::Vector2f& accleration) { this->acceleration = accleration; }
    inline void SetCoefficientOfRestitution(const sf::Vector2f& E) { this->coefficientOfRestitution = E; }
    inline void SetCoefficientOfFriction(const sf::Vector2f& u) { this->ceofficientOfFriction = u; }





public:
    inline void ApplyForce(const sf::Vector2f& force) {
        if (mass != 0) {
            if ((force.x > 0 && velocity.x < maxvelocity.x) || (force.x < 0 && velocity.x > -maxvelocity.x)) {
                acceleration.x += force.x / mass;     // Calculate the force in x direction
            }
            else if ((force.x < 0 && velocity.x >= 0) || (force.x > 0 && velocity.x <= 0)) {
                acceleration.x += force.x / mass;      // Allow instant change in direction
            }
            if ((force.y > 0 && velocity.y < maxvelocity.y) || (force.y < 0 && velocity.y > -maxvelocity.y)) {
                acceleration.y += force.y / mass;      // Calculate the force in y direction
            }
            else if ((force.y < 0 && velocity.y >= 0) || (force.y > 0 && velocity.y <= 0)) {
                acceleration.y += force.y / mass;       // Allow instant change in direction
            }
        }
    }

    inline void AddAcceleration(const sf::Vector2f& acceleration) { this->acceleration += acceleration; }
    inline void AddVelocity(const sf::Vector2f& deltaVelocity) { velocity += deltaVelocity; }
    inline sf::Vector2f& GetVelocity() { return this->velocity; }


    virtual inline sf::Vector2f& NewPosition(const float& dt) {
        this->velocity += this->acceleration * dt;
        if (this->velocity.y > maxvelocity.y) this->velocity.y = maxvelocity.y;
        if (this->velocity.y < -maxvelocity.y) this->velocity.y = -maxvelocity.y;
        if (this->velocity.x > maxvelocity.x) this->velocity.x = maxvelocity.x;
        if (this->velocity.x < -maxvelocity.x) this->velocity.x = -maxvelocity.x;
        this->position += this->velocity * dt;
        this->acceleration.y = 0;
        return this->position;
    }


protected:
    virtual inline void FindMaxVelocities() {
        if (this->mass == 0) { this->mass = 1.0f; }
        else { this->maxvelocity = this->velocity; }
    }
};
