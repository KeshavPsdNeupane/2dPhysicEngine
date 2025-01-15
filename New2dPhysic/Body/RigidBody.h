#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "../PhysicUtility/Utility.h"
#include<cmath>
class RigidBody {
protected:
    float mass;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f coefficientOfRestitution;
    sf::Vector2f ceofficientOfFriction;
    sf::Vector2f maxVelocity;
    sf::Vector2f oldPosition;
    float gravity;
public:
    RigidBody()
        : position(0.0f, 0.0f),
        velocity(0.0f, 0.0f),
        acceleration(0.0f, 0.0f),
        mass(1.0f), size(0.0f, 0.0f),
        coefficientOfRestitution(0.0f, 0.0f),
        ceofficientOfFriction(0.0f, 0.0f),
        maxVelocity(0, 0), gravity(GMNumber::GRAVITY) {}

    RigidBody(const float& mass, const sf::Vector2f& position, const sf::Vector2f& size,
        const sf::Vector2f& velocity, const sf::Vector2f& acceleration,
        const sf::Vector2f& coefficientOfRestitution, const sf::Vector2f& ceofficientOfFriction)
        :mass(mass),
        position(position),
        oldPosition(position),
        size(size),
        velocity(velocity),
        acceleration(acceleration),
        coefficientOfRestitution(coefficientOfRestitution),
        ceofficientOfFriction(ceofficientOfFriction),
        gravity(GMNumber::GRAVITY){}
    virtual ~RigidBody(){}


public:
    inline void SetMass(const float mass) { this->mass = mass; }
    virtual inline void SetPosition(const sf::Vector2f position) { this->position = position; }
    virtual inline void SetSize(const sf::Vector2f size) { this->size = size; }
    inline void SetVelocity(const sf::Vector2f velocity) { this->velocity = velocity; }
    inline void SetAcceleration(const sf::Vector2f accleration) { this->acceleration = accleration; }
    inline void SetCoefficientOfRestitution(const sf::Vector2f E) { this->coefficientOfRestitution = E; }
    inline void SetCoefficientOfFriction(const sf::Vector2f u) { this->ceofficientOfFriction = u; }

    const inline float& GetMass() const { return this->mass; }
    const inline sf::Vector2f& GetPosition()const { return this->position; }  
    const inline sf::Vector2f& GetSize() const { return this->size; }
    const inline sf::Vector2f& GetVelocity() const { return this->velocity; }
    const inline sf::Vector2f& GetAcceleration() const { return this->acceleration; }
    const inline sf::Vector2f& GetCoefficientOfRestitution() const { return this->coefficientOfRestitution; }
    const inline sf::Vector2f& GetCoefficientOfFriction() const { return this->ceofficientOfFriction; }
    const inline sf::Vector2f& GetOldPosition()const { return this->oldPosition; }

public:
    inline void ApplyForce(const sf::Vector2f& force) {
        if (mass != 0) {
            this->acceleration += force / this->mass;
            sf::Vector2f abs_acclleration(GMNumber::ABSOLUTE_ACCLERATION_FOR_PLAYER);
			VectorOperation::ClampForVector(this->acceleration, -abs_acclleration, abs_acclleration);
        }
    }

    inline void AddAcceleration(const sf::Vector2f& acc) {
        this->acceleration += acc;
        sf::Vector2f abs_acclleration(GMNumber::ABSOLUTE_ACCLERATION_FOR_PLAYER);
        VectorOperation::ClampForVector(this->acceleration, -abs_acclleration, abs_acclleration);
    }


    //inline void AddVelocity(const sf::Vector2f& deltaVelocity) { velocity += deltaVelocity; }

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
		VectorOperation::ClampForVector(this->velocity, -maxVelocity, maxVelocity);
        this->oldPosition = this->position;
        this->position += this->velocity * dt;
        this->acceleration.y = 0;
        return this->position;
    }

protected:
    virtual inline void FindMaxVelocities() {
        if (this->mass == 0) { this->mass = 1.0f; }
        this->maxVelocity = this->velocity;
    }
};
