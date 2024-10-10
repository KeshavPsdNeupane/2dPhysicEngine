#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "../PhysicUtility/Utility.h"
#include<cmath>
#include"../PhysicUtility/Utility.h"
class RigidBody {
protected:
    int ID;
    float mass;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f coefficientOfRestitution;
    sf::Vector2f ceofficientOfFriction;
    sf::Vector2f maxvelocity;
    sf::Vector2f oldPosition;
public:
    RigidBody()
        : position(0.0f, 0.0f),
        velocity(0.0f, 0.0f),
        acceleration(0.0f, 0.0f),
        mass(1.0f), ID(-1), size(0.0f,0.0f),
        coefficientOfRestitution(0.0f, 0.0f),
        ceofficientOfFriction( 0.0f, 0.0f), 
        maxvelocity(0,0) {}

    RigidBody(const int& id, const float& mass, const sf::Vector2f& position, const sf::Vector2f& size,
        const sf::Vector2f& velocity, const sf::Vector2f& acceleration,
        const sf::Vector2f& coefficientOfRestitution, const sf::Vector2f& ceofficientOfFriction)
        :ID(id), mass(mass),
        position(position),
        size(size),
        velocity(velocity),
        acceleration(acceleration), 
        coefficientOfRestitution(coefficientOfRestitution),
        ceofficientOfFriction(ceofficientOfFriction) {}



public:
    inline void SetIndex(const int& index) { this->ID = index; }
    inline void SetMass(const float& mass) { this->mass = mass; }
    inline void SetPosition(const sf::Vector2f& position) { this->position = position; }
    inline void SetSize(const sf::Vector2f& size) { this->size = size; }
    inline void SetVelocity(const sf::Vector2f& velocity) { this->velocity = velocity; }
    inline void SetAcceleration(const sf::Vector2f& accleration) { this->acceleration = accleration; }
    inline void SetCoefficientOfRestitution(const sf::Vector2f& E) { this->coefficientOfRestitution = E; }
    inline void SetCoefficientOfFriction(const sf::Vector2f& u) { this->ceofficientOfFriction = u; }


   const inline int& GetIndex() const { return this->ID; }
   const inline float& GetMass() const { return this->mass; }
   const inline sf::Vector2f& GetPosition() const { return this->position; }
   const inline sf::Vector2f& GetSize() const { return this->size; }
   const inline sf::Vector2f& GetVelocity() const { return this->velocity; }
   const inline sf::Vector2f& GetAcceleration() const { return this->acceleration; }
   const inline sf::Vector2f& GetCoefficientOfRestitution() const { return this->coefficientOfRestitution; }
   const inline sf::Vector2f& GetCoefficientOfFriction() const { return this->ceofficientOfFriction; }
   const inline sf::Vector2f& GetOldPosition()const { return this->oldPosition;}

public:
    inline void ApplyForce(const sf::Vector2f& force) {
        if (mass != 0) {
            //LEAVE IT MIGHT BE NEEDED 
            //if ((force.x > 0 && velocity.x < maxvelocity.x) || (force.x < 0 && velocity.x > -maxvelocity.x)) {
            //    acceleration.x += force.x / mass;
            //}
            //else if ((force.x < 0 && velocity.x >= 0) || (force.x > 0 && velocity.x <= 0)) {
            //    acceleration.x += force.x / mass;      // Allow instant change in direction
            //}
            //if ((force.y > 0 && velocity.y < maxvelocity.y) || (force.y < 0 && velocity.y > -maxvelocity.y)) {
            //    acceleration.y += force.y / mass;      // Calculate the force in y direction
            //}
            //else if ((force.y < 0 && velocity.y >= 0) || (force.y > 0 && velocity.y <= 0)) {
            //    acceleration.y += force.y / mass;       // Allow instant change in direction
            //}
            this->acceleration += force / this->mass;
            if (acceleration.x > GMNumber::ABSOLUTE_ACCLERATION_FOR_PLAYER_X) {
                acceleration.x = GMNumber::ABSOLUTE_ACCLERATION_FOR_PLAYER_X;
            }
            else if (acceleration.x < -GMNumber::ABSOLUTE_ACCLERATION_FOR_PLAYER_X) {
                acceleration.x = -GMNumber::ABSOLUTE_ACCLERATION_FOR_PLAYER_X;
            }
            if (acceleration.y > GMNumber::ABSOLUTE_ACCLERATION_FOR_PLAYER_X) {
                acceleration.y = GMNumber::ABSOLUTE_ACCLERATION_FOR_PLAYER_X;
            }
            else if (acceleration.y < -GMNumber::ABSOLUTE_ACCLERATION_FOR_PLAYER_X) {
                acceleration.y = -GMNumber::ABSOLUTE_ACCLERATION_FOR_PLAYER_X;
            }
        }
    }




    inline void AddAcceleration(const sf::Vector2f& acceleration) { this->acceleration += acceleration; }
    inline void AddVelocity(const sf::Vector2f& deltaVelocity) { velocity += deltaVelocity; }

    virtual inline sf::Vector2f& NewPosition(const float& dt) {
        /**
         * @brief Updates the position based on the current velocity and acceleration.
         *
         * @param dt Time delta for position update.
         *
         * @warning Don't forget to do this->oldPosition = this->position; before changing position!
         *
         * @return Reference to the updated position.
         */
        this->velocity += this->acceleration * dt;
        if (this->velocity.y > maxvelocity.y) this->velocity.y = maxvelocity.y;
        if (this->velocity.y < -maxvelocity.y) this->velocity.y = -maxvelocity.y;
        if (this->velocity.x > maxvelocity.x) this->velocity.x = maxvelocity.x;
        if (this->velocity.x < -maxvelocity.x) this->velocity.x = -maxvelocity.x;
        this->oldPosition = this->position;
        this->position += this->velocity * dt;
        this->acceleration.y = 0;
        return this->position;
    }
protected:
    virtual inline void FindMaxVelocities() {
        if (this->mass == 0) { this->mass = 1.0f; }
        this->maxvelocity = this->velocity; 
    }
};
