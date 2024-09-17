#include "Collision.h"
#include"../PhysicUtility/Utility.h"
#include <algorithm>
const float VELOCITY_THRESHOLD = 10.0f;

void Collision::CollisionDetection(sf::RectangleShape& R1, RigidBody& F1,
    sf::RectangleShape& R2, RigidBody& F2) {
    this->B1 = R1.getGlobalBounds();
    this->B2 = R2.getGlobalBounds();

    if (B1.intersects(B2)) {
        DirectionFinder();
        this->M1 = F1.mass;
        this->M2 = F2.mass;
        PenetrationResoluter(F1, F2);
        EffectiveEFinder(F1, F2);
        //formula
        v1 = ((M1 - eEffective * M2) * u1 + (1 + eEffective) * M2 * u2) / (M1 + M2);
        v2 = ((M2 - eEffective * M1) * u2 + (1 + eEffective) * M1 * u1) / (M1 + M2);
        u1 = v1; u2 = v2;
        CollisionThreshold();
        F1.velocity = v1;  F2.velocity = v2;
        ResetForNewCollision();
    }
}


void Collision::ResetForNewCollision() {
    resolution = { 0.0f, 0.0f };
    horizontalOverlap = 0.0f;
    verticalOverlap = 0.0f;
    eEffective = 0.0f;
}



inline void Collision::DirectionFinder(){
    this->horizontalOverlap = std::min(B1.left + B1.width, B2.left + B2.width) - std::max(B1.left, B2.left);
    this->verticalOverlap = std::min(B1.top + B1.height, B2.top + B2.height) - std::max(B1.top, B2.top);
}

void Collision::PenetrationResoluter(RigidBody& F1, RigidBody& F2) {
    if (this->horizontalOverlap < this->verticalOverlap) {
        this->resolution.x = (B1.left < B2.left)
            ? -horizontalOverlap : horizontalOverlap;
    }
    else {
        this->resolution.y = (B1.top < B2.top)
            ? -verticalOverlap : verticalOverlap;
    }
    if (this->M1 * 1000 < this->M2) { F1.position += this->resolution; }
    else if (this->M1 > 1000 * this->M2) { F2.position -= this->resolution; }
    else {
        F1.position += this->resolution * (this->M2 / (this->M1 + this->M2));
        F2.position -= this->resolution * (this->M1 / (this->M1 + this->M2));
    }
}

void Collision::EffectiveEFinder(RigidBody& F1, RigidBody& F2){
    this->u1 = F1.velocity;
    this->u2 = F2.velocity;
    this->Vrelative = u1 - u2;
    this->Vunit = VectorOperation::Normalize(this->Vrelative);
    this->v1 = { 0, 0 };
    this->v2 = { 0, 0 };

    this->e = { (F2.coefficientOfRestitution.x + F1.coefficientOfRestitution.x) / 2 ,
        (F2.coefficientOfRestitution.y + F1.coefficientOfRestitution.y) / 2 };
    eEffective = VectorOperation::DotProduct(this->Vunit, this->e);
}

inline void Collision::CollisionThreshold(){
    if (std::abs(v1.x) < VELOCITY_THRESHOLD) v1.x = 0;
    if (std::abs(v1.y) < VELOCITY_THRESHOLD) v1.y = 0;
    if (std::abs(v2.x) < VELOCITY_THRESHOLD) v2.x = 0;
    if (std::abs(v2.y) < VELOCITY_THRESHOLD) v2.y = 0;
    //std::cout << "  u1  - " << v1.x << " " << v1.y << std::endl;
    //std::cout << "  u2  - " << v2.x << " " << v2.y << std::endl << std::endl;
}


