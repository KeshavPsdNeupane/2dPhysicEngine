#include "ContactMechanic.h"
#include"../PhysicUtility/Utility.h"
#include <algorithm>

ContactMech::ContactMech():
    horizontalOverlap(GMNumber::ZERO) , verticalOverlap(GMNumber::ZERO),
    eEffective(GMNumber::ZERO) , M1(GMNumber::ZERO) , M2(GMNumber::ZERO),
    gravity(GMNumber::ZERO) , frictionDeceleratedVelocity(GMNumber::ZERO){}

void ContactMech::CollisionDetection(sf::RectangleShape& R1, RigidBody& F1,
    sf::RectangleShape& R2, RigidBody& F2) {
    this->B1 = R1.getGlobalBounds();
    this->B2 = R2.getGlobalBounds();

    if (B1.intersects(B2)) {
        DirectionFinder();
        this->M1 = F1.mass;
        this->M2 = F2.mass;
        PenetrationResoluter(F1, F2);
        EffectiveEFinder(F1, F2);
        if (this->horizontalOverlap < this->verticalOverlap) {
            this->eEffective = e.x;
           // std::cout << "effective e H = " << eEffective << std::endl;
            if (M2 > GMNumber::MASS_THRESHOLD * M1 && std::abs(v2.x) < GMNumber::COLLISION_VELOCITY_THRESHOLD) {
                v1.x = -eEffective * u1.x; v2.x = GMNumber::ZERO;
            }
            else if (M1 > GMNumber::MASS_THRESHOLD * M2 && std::abs(v1.x) < GMNumber::COLLISION_VELOCITY_THRESHOLD) {
                v2.x = -eEffective * u2.x; v1.x = GMNumber::ZERO;
            }
            else {
                v1.x = ((M1 - eEffective * M2) * u1.x + (1 + eEffective) * M2 * u2.x) / (M1 + M2);
                v2.x = ((M2 - eEffective * M1) * u2.x + (1 + eEffective) * M1 * u1.x) / (M1 + M2);
            }
            v1.y = u1.y; v2.y = u2.y;
        }
        else {
            this->eEffective = e.y;
           // std::cout << "effective e V = " << eEffective << std::endl;
            if (M2 > GMNumber::MASS_THRESHOLD * M1 && std::abs(v2.y) < GMNumber::COLLISION_VELOCITY_THRESHOLD) {
                v1.y = -eEffective * u1.y; v2.y = GMNumber::ZERO;
            }
            else if (M1 > GMNumber::MASS_THRESHOLD * M2 && std::abs(v1.y) < GMNumber::COLLISION_VELOCITY_THRESHOLD) {
                v2.y = -eEffective * u2.y; v1.y = GMNumber::ZERO;
            }
            else {
                v1.y = ((M1 - eEffective * M2) * u1.y + (1 + eEffective) * M2 * u2.y) / (M1 + M2);
                v2.y = ((M2 - eEffective * M1) * u2.y + (1 + eEffective) * M1 * u1.y) / (M1 + M2);
            }
            v1.x = u1.x; v2.x = u2.x;
        }
        CollisionThreshold();
        F1.velocity = v1;  F2.velocity = v2;

        ResetForNewCollision();
    }
}

void ContactMech::Friction(sf::RectangleShape& R1, RigidBody& F1, sf::RectangleShape& R2, RigidBody& F2, const float& dt){
    this->B1 = R1.getGlobalBounds();
    this->B2 = R2.getGlobalBounds();
    if (B1.intersects(B2)) {
        this->coeffOfFriction = F2.ceofficientOfFriction;
        this->u1 = F1.velocity;
        this->Vunit = VectorOperation::Normalize(u1);
        gravity = std::abs(F1.acceleration.y);
        DirectionFinder();
        if (this->horizontalOverlap > this->verticalOverlap) {
            this->frictionDeceleratedVelocity = -this->coeffOfFriction.x * gravity * this->Vunit.x * dt;
            if (std::abs(this->u1.x) < GMNumber::COLLISION_VELOCITY_THRESHOLD) { this->u1.x = GMNumber::ZERO; }
            this->u1 += { this->frictionDeceleratedVelocity, GMNumber::ZERO };
        }
        else {
            this->frictionDeceleratedVelocity = -this->coeffOfFriction.y * gravity * this->Vunit.y * dt/2.0f;  
                                                                                // 2.0F IS NEEDED FOR LIMITING FRICTION
            if (std::abs(this->u1.y) < GMNumber::COLLISION_VELOCITY_THRESHOLD) { this->u1.y = GMNumber::ZERO; }
            this->u1 += {GMNumber::ZERO, this->frictionDeceleratedVelocity };
        }
        F1.velocity = this->u1;
    }
}


void ContactMech::ResetForNewCollision() {  // LEAVING 0 AS IT IS ,SINCE IT WILL BE CALLSED AND
    // ASKING VALUE FROM GMNUMBER MIGHT BE LONGER
    v1 = { 0,0 }; v2 = { 0,0 };
    resolution = { 0.0f, 0.0f };
    horizontalOverlap = 0.0f;
    verticalOverlap = 0.0f;
    eEffective = 0.0f;
}



inline void ContactMech::DirectionFinder(){
    this->horizontalOverlap = std::min(B1.left + B1.width, B2.left + B2.width) - std::max(B1.left, B2.left);
    this->verticalOverlap = std::min(B1.top + B1.height, B2.top + B2.height) - std::max(B1.top, B2.top);
}

void ContactMech::PenetrationResoluter(RigidBody& F1, RigidBody& F2) {
    if (this->horizontalOverlap < this->verticalOverlap) {
        this->resolution.x = (B1.left < B2.left)
            ? -horizontalOverlap : horizontalOverlap;
    }
    else {
        this->resolution.y = (B1.top < B2.top)
            ? - verticalOverlap : verticalOverlap;
    }
    if (this->M1 * 1000 < this->M2) { F1.position += this->resolution; }
    else if (this->M1 > 1000 * this->M2) { F2.position -= this->resolution; }
    else {
        F1.position += this->resolution * (this->M2 / (this->M1 + this->M2));
        F2.position -= this->resolution * (this->M1 / (this->M1 + this->M2));
    }
}

void ContactMech::EffectiveEFinder(RigidBody& F1, RigidBody& F2){
    u1 = F1.velocity;
    u2 = F2.velocity;
    Vrelative = u2 - u1;
    Vunit = VectorOperation::Normalize(Vrelative);
    Vunit = { std::abs(Vunit.x) , std::abs(Vunit.y) };
   this->e = { (F2.coefficientOfRestitution.x + F1.coefficientOfRestitution.x) / 2 ,
        (F2.coefficientOfRestitution.y + F1.coefficientOfRestitution.y) / 2 };
}

inline void ContactMech::CollisionThreshold(){
    if (std::abs(v1.x) < GMNumber::COLLISION_VELOCITY_THRESHOLD) v1.x = GMNumber::ZERO;
    if (std::abs(v1.y) < GMNumber::COLLISION_VELOCITY_THRESHOLD) v1.y = GMNumber::ZERO;
    if (std::abs(v2.x) < GMNumber::COLLISION_VELOCITY_THRESHOLD) v2.x = GMNumber::ZERO;
    if (std::abs(v2.y) < GMNumber::COLLISION_VELOCITY_THRESHOLD) v2.y = GMNumber::ZERO;
   //std::cout << "  v1  - " << v1.x << " " << v1.y << std::endl;
   //std::cout << "  v2  - " << v2.x << " " << v2.y << std::endl << std::endl;
}


