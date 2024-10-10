#include "ContactMechanic.h"
#include"../PhysicUtility/Utility.h"
#include <algorithm>
#include"GameShapes.h"

ContactMech::ContactMech():
    horizontalOverlap(0.0f) , verticalOverlap(0.0f),
    eEffective(GMNumber::ZERO) , M1(GMNumber::ZERO) , M2(0.0f),
    gravity(0.0f) , frictionDeceleratedVelocity(0.0f){}


void ContactMech::CollsionDetection(std::shared_ptr<GameShape> playerShape,
    std::shared_ptr<GameShape> otherShape, ContactMech& contact) {
    sf::FloatRect playerBound = sf::FloatRect(playerShape->GetPosition(), playerShape->GetSize());
    sf::FloatRect otherBound = sf::FloatRect(otherShape->GetPosition(), otherShape->GetSize());
    if (playerBound.intersects(otherBound)) {
       otherShape->CollisionRedirection(playerShape, contact);
    }
}


void ContactMech::HeavyObjectCollisionHandle(std::shared_ptr<GameShape> playerShape,
    GameShape& otherShape){
    this->B1 = sf::FloatRect(playerShape->GetPosition(), playerShape->GetSize());
    this->B2 = sf::FloatRect(otherShape.GetPosition(), otherShape.GetSize());
    DirectionFinder();
    this->M1 = playerShape->GetMass();
    this->M2 = otherShape.GetMass();
    this->u1 = playerShape->GetVelocity();
    this->u2 = otherShape.GetVelocity();
    PenetrationResoluter(*playerShape,otherShape);
    EffectiveEFinder(*playerShape, otherShape);
    if (this->horizontalOverlap < this->verticalOverlap) {
        this->eEffective = e.x;
       // std::cout << "effective e H = " << eEffective << std::endl;
        if (M2 > GMNumber::MASS_THRESHOLD * M1 && std::abs(v2.x) < GMNumber::COLLISION_VELOCITY_THRESHOLD) {
            v1.x = -eEffective * u1.x; v2.x = 0.0f;
        }
        else if (M1 > GMNumber::MASS_THRESHOLD * M2 && std::abs(v1.x) < GMNumber::COLLISION_VELOCITY_THRESHOLD) {
            v2.x = -eEffective * u2.x; v1.x = 0.0f;
        }
        else {
            v1.x = ((M1 - eEffective * M2) * u1.x + (1 + eEffective) * M2 * u2.x) / (M1 + M2);
            v2.x = ((M2 - eEffective * M1) * u2.x + (1 + eEffective) * M1 * u1.x) / (M1 + M2);
        }
        v1.y = u1.y; v2.y = u2.y;
    }
    else {
        this->eEffective = e.y;
        //std::cout << "effective e V = " << e.y << std::endl;
        if (M2 > GMNumber::MASS_THRESHOLD * M1 && std::abs(v2.y) < GMNumber::COLLISION_VELOCITY_THRESHOLD) {
            v1.y = -eEffective * u1.y; v2.y = 0.0f;
        }
        else if (M1 > GMNumber::MASS_THRESHOLD * M2 && std::abs(v1.y) < GMNumber::COLLISION_VELOCITY_THRESHOLD) {
            v2.y = -eEffective * u2.y; v1.y = 0.0f;
        }
        else {
            v1.y = ((M1 - eEffective * M2) * u1.y + (1 + eEffective) * M2 * u2.y) / (M1 + M2);
            v2.y = ((M2 - eEffective * M1) * u2.y + (1 + eEffective) * M1 * u1.y) / (M1 + M2);
        }
        v1.x = u1.x; 
        v2.x = u2.x;
    }
    CollisionThreshold();
    playerShape->SetVelocity(v1);
    otherShape.SetVelocity(v2);
    ResetForNewCollision();
}

void ContactMech::LightObjectCollisionHandle(std::shared_ptr<GameShape> playerShape, GameShape& otherShape) {
    this->B1 = sf::FloatRect(playerShape->GetPosition(), playerShape->GetSize());
    this->B2 = sf::FloatRect(otherShape.GetPosition(), otherShape.GetSize());
    this->M1 = playerShape->GetMass();
    this->M2 = otherShape.GetMass();
    this->u1 = playerShape->GetVelocity();
    this->u2 = otherShape.GetVelocity();
    PenetrationResoluter(*playerShape, otherShape);
    EffectiveEFinder(*playerShape, otherShape);

    v1.x = ((M1 - eEffective * M2) * u1.x + (1 + e.x) * M2 * u2.x) / (M1 + M2);
    v1.y = ((M1 - eEffective * M2) * u1.y + (1 + e.y) * M2 * u2.y) / (M1 + M2);

    v2.x = ((M2 - eEffective * M1) * u2.x + (1 + eEffective) * M1 * u1.x) / (M1 + M2);
    v2.y = ((M2 - eEffective * M1) * u2.y + (1 + eEffective) * M1 * u1.y) / (M1 + M2);

    CollisionThreshold();
    playerShape->SetVelocity(v1);
    otherShape.SetVelocity(v2);
    ResetForNewCollision();

}


void ContactMech::ApplyFriction(std::shared_ptr<GameShape> playerShape, std::shared_ptr<GameShape> otherShape, const float& dt){
    this->B1 = sf::FloatRect(playerShape->GetPosition(), playerShape->GetSize());
    this->B2 = sf::FloatRect(otherShape->GetPosition(), otherShape->GetSize());
    if (B1.intersects(B2)) {
        this->coeffOfFriction = otherShape->GetCoefficientOfFriction();
        this->u1 = playerShape->GetVelocity();
        this->Vunit = VectorOperation::Normalize(u1);
        gravity = GMNumber::GRAVITY;
        DirectionFinder();
        if (this->horizontalOverlap > this->verticalOverlap) {
            this->frictionDeceleratedVelocity = -this->coeffOfFriction.x * gravity * this->Vunit.x * dt;
            if (std::abs(this->u1.x) < GMNumber::COLLISION_VELOCITY_THRESHOLD) { this->u1.x = GMNumber::ZERO; }
            this->u1 += { this->frictionDeceleratedVelocity, 0.0f};
        }
        else {
            this->frictionDeceleratedVelocity = -this->coeffOfFriction.y * gravity * this->Vunit.y * dt/2.0f;  
                                                                                // 2.0F IS NEEDED FOR LIMITING FRICTION
            if (std::abs(this->u1.y) < GMNumber::COLLISION_VELOCITY_THRESHOLD) { this->u1.y = GMNumber::ZERO; }
            this->u1 += {GMNumber::ZERO, this->frictionDeceleratedVelocity };
        }
        playerShape->SetVelocity(this->u1);
    }
}


void ContactMech::ResetForNewCollision() {  // LEAVING 0 AS IT IS ,SINCE IT WILL BE CALLED AND
    // ASKING VALUE FROM GMNUMBER MIGHT BE LONGER FOR PROCRSSING
    v1 = { 0.0f,0.0f }; v2 = { 0.0f,0.0f };
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
        this->resolution.x = 1.5 * (B1.left < B2.left)
            ? -horizontalOverlap : horizontalOverlap;
    }
    else {
        this->resolution.y = 1.5 * (B1.top < B2.top)
            ? - verticalOverlap : verticalOverlap;
    }
    if (this->M1 * 1000 < this->M2) { F1.SetPosition(F1.GetPosition() + this->resolution) ; }
    else if (this->M1 > 1000 * this->M2) { F2.SetPosition(F2.GetPosition() - this->resolution); }
    else {
        F1.SetPosition(F1.GetPosition() + this->resolution * (this->M2 / (this->M1 + this->M2)));
        F2.SetPosition(F2.GetPosition() - this->resolution * (this->M1 / (this->M1 + this->M2)));
    }
}

void ContactMech::EffectiveEFinder(RigidBody& F1, RigidBody& F2){
   this->e = { (F2.GetCoefficientOfRestitution().x + F1.GetCoefficientOfRestitution().x)/2 ,
        (F2.GetCoefficientOfRestitution().y + F1.GetCoefficientOfRestitution().y)/2 };
}

inline void ContactMech::CollisionThreshold(){
    if (std::abs(v1.x) < GMNumber::COLLISION_VELOCITY_THRESHOLD) v1.x = 0.0f;
    if (std::abs(v1.y) < GMNumber::COLLISION_VELOCITY_THRESHOLD) v1.y = 0.0f;
    if (std::abs(v2.x) < GMNumber::COLLISION_VELOCITY_THRESHOLD) v2.x = 0.0f;
    if (std::abs(v2.y) < GMNumber::COLLISION_VELOCITY_THRESHOLD) v2.y =  0.0f;
}


