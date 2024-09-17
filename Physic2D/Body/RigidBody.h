#pragma once

#include <SFML/Graphics.hpp>
#include "../PhysicUtility/Utility.h"


class RigidBody {
public:
    int index;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f coefficientOfRestitution;
    float mass;

public:
    RigidBody()
        : position(0,0), velocity(1,1), acceleration(0,0), mass(1.0f) , index() , coefficientOfRestitution(){}

    RigidBody( const int& id,const float& mass, const sf::Vector2f& position, 
        const sf::Vector2f& velocity, const sf::Vector2f& acceleration ,
        const sf::Vector2f& coefficientOfRestitution)
        : mass(mass), position(position), velocity(velocity),
        acceleration(acceleration),
        coefficientOfRestitution(coefficientOfRestitution)
    {
        std::cout << "Mass = " << this->mass << std::endl;
        std::cout << "position = " << this->position.x <<" "<< this->position.y << std::endl;
        std::cout << "velocity = " << this->velocity.x << " " << this->velocity.y << std::endl;
        std::cout << "acceleration = " << this->acceleration.x << " " << this->acceleration.y << std::endl;
        index = 0;
    }

public:
    inline  sf::Vector2f& ApplyForce(const sf::Vector2f& force , const float& dt) {
        if (mass != 0) { 
            acceleration += force / mass; 
            return NewPositionA(acceleration, dt);
        }
    }


    inline sf::Vector2f& NewPositionA(const sf::Vector2f& acceleration, const float& dt) {
        velocity += acceleration * (dt/2.0f);
        if (velocity.y > 250.0f) { velocity.y = 250.0f; return NewPositionV(velocity, dt); }
        return  NewPositionV(velocity, dt);
    
    }
    inline sf::Vector2f& NewPositionV(const sf::Vector2f& velocity, const float dt) {
       this->position += velocity * dt; 
        return position;
    }
};
