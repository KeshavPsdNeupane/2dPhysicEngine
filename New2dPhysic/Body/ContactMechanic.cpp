#include "ContactMechanic.h"
#include"../PhysicUtility/Utility.h"
#include <algorithm>
#include"GameShapes.h"
ContactMech::ContactMech():
    horizontalOverlap(GMNumber::ZERO) , verticalOverlap(GMNumber::ZERO),
    eEffective(GMNumber::ZERO) , M1(GMNumber::ZERO) , M2(GMNumber::ZERO),
    gravity(GMNumber::ZERO) , frictionDeceleratedVelocity(GMNumber::ZERO){}

void ContactMech::PlayerCollisionDetection(sf::RectangleShape& R1, RigidBody& F1, 
    sf::RectangleShape& R2, RigidBody& F2 , ContactMech& contact){
    this->B1 = R1.getGlobalBounds();
    this->B2 = R2.getGlobalBounds();
    if (B1.intersects(B2)) {
        contact.PathBasedCollisionHandle(B1,F1,B2,F2);
    }
}

void ContactMech::PLayerCollisionWIthShape(std::shared_ptr<GameShape> playerShape,
    std::shared_ptr<GameShape> otherShape, ContactMech& contact) {
    sf::FloatRect playerBound = sf::FloatRect(playerShape->GetPosition(), playerShape->GetSize());
    sf::FloatRect otherBound = sf::FloatRect(otherShape->GetPosition(), otherShape->GetSize());
    if (playerBound.intersects(otherBound)) {
       // std::cout << "boind intersect " << std::endl;
        otherShape->CollisionRedirection(playerShape, otherShape, contact);
    }
}

void ContactMech::PathCollsionHandleWithShape(std::shared_ptr<GameShape> playerShape,
    std::shared_ptr<GameShape> otherShape){
   // std::cout << "path col handle of " << otherShape->GetIndex() << std::endl;
    this->B1 = sf::FloatRect(playerShape->GetPosition(), playerShape->GetSize());
    this->B2 = sf::FloatRect(otherShape->GetPosition(), otherShape->GetSize());
    DirectionFinder();
    this->M1 = playerShape->GetMass();
    this->M2 = otherShape->GetMass();
    this->u1 = playerShape->GetVelocity();
    this->u2 = otherShape->GetVelocity();
    PenetrationResoluter( *playerShape, *otherShape);
    auto& E1 = playerShape->GetCoefficientOfRestitution();
    std::cout << "coff of player "<<E1.x << " " << E1.y << std::endl;

    this->e = { (playerShape->GetCoefficientOfRestitution().x + otherShape->GetCoefficientOfRestitution().x) / 2 ,
            (playerShape->GetCoefficientOfRestitution().y + otherShape->GetCoefficientOfRestitution().y) / 2 };



    if (this->horizontalOverlap < this->verticalOverlap) {
        this->eEffective = e.x;
        std::cout << "effective e H = " << eEffective << std::endl;
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
        std::cout << "effective e V = " << e.y << std::endl;
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
        v1.x = u1.x; v2.x = u2.x;
    }
    std::cout << std::endl;
    CollisionThreshold();
    playerShape->SetVelocity(v1);  otherShape->SetVelocity(v2);
    ResetForNewCollision();
}


void ContactMech::PathBasedCollisionHandle(sf::FloatRect& Bound1, RigidBody& F1
    , sf::FloatRect& Bound2, RigidBody& F2){     // THIS IS A DEFAULT IMPLEMENTATION FOR COLLISION BUT YOUR HAVE TO
    // OVERRITE TO EVERYPATH WITH UNIQUE PROPERTIES
    this->B1 = Bound1;  this->B2 = Bound2; 
    DirectionFinder();
    this->M1 = F1.GetMass();
    this->M2 = F2.GetMass();
    PenetrationResoluter(F1, F2);
    EffectiveEFinder(F1, F2);

    auto E1 = F1.GetCoefficientOfRestitution();
    auto E2 = F2.GetCoefficientOfRestitution();
    std::cout << " player e = " << E1.x << " " << E1.y << std::endl;
    std::cout << " other e = " << E2.x << " " << E2.y << std::endl;



    if (this->horizontalOverlap < this->verticalOverlap) {
        this->eEffective = e.x;
        std::cout << "effective e H = " << eEffective << std::endl;
        if (M2 > GMNumber::MASS_THRESHOLD * M1 && std::abs(v2.x) < GMNumber::COLLISION_VELOCITY_THRESHOLD) {
            v1.x = -eEffective * u1.x; v2.x = 0.0f ;
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
        std::cout << "effective e V = " << eEffective << std::endl;
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
        v1.x = u1.x; v2.x = u2.x;
    }
    CollisionThreshold();
    F1.SetVelocity(v1);  F2.SetVelocity(v2);
    ResetForNewCollision();
}

void ContactMech::CollisionDetection(sf::RectangleShape& R1, RigidBody& F1,
    sf::RectangleShape& R2, RigidBody& F2) {
    this->B1 = R1.getGlobalBounds();
    this->B2 = R2.getGlobalBounds();

    if (B1.intersects(B2)) {
        DirectionFinder();
        this->M1 = F1.GetMass();
        this->M2 = F2.GetMass();
        u1 = F1.GetVelocity();
        u2 = F2.GetVelocity();
        PenetrationResoluter(F1, F2);
        EffectiveEFinder(F1, F2);
        if (this->horizontalOverlap < this->verticalOverlap) {
            this->eEffective = e.x;
           //std::cout << "effective e H = " << eEffective << std::endl;
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
            //std::cout << "effective e V = " << eEffective << std::endl;
            if (M2 > GMNumber::MASS_THRESHOLD * M1 && std::abs(v2.y) < GMNumber::COLLISION_VELOCITY_THRESHOLD) {
                v1.y = -eEffective * u1.y; v2.y = 0.0f ;
            }
            else if (M1 > GMNumber::MASS_THRESHOLD * M2 && std::abs(v1.y) < GMNumber::COLLISION_VELOCITY_THRESHOLD) {
                v2.y = -eEffective * u2.y; v1.y = 0.0f;
            }
            else {
                v1.y = ((M1 - eEffective * M2) * u1.y + (1 + eEffective) * M2 * u2.y) / (M1 + M2);
                v2.y = ((M2 - eEffective * M1) * u2.y + (1 + eEffective) * M1 * u1.y) / (M1 + M2);
            }
            v1.x = u1.x; v2.x = u2.x;
        }
        CollisionThreshold();
        F1.SetVelocity(v1);  F2.SetVelocity(v2);
        ResetForNewCollision();
    }
}

void ContactMech::Friction(sf::RectangleShape& R1, RigidBody& F1, sf::RectangleShape& R2, RigidBody& F2, const float& dt){
    this->B1 = R1.getGlobalBounds();
    this->B2 = R2.getGlobalBounds();
    if (B1.intersects(B2)) {
        this->coeffOfFriction = F2.GetCoefficientOfFriction();
        this->u1 = F1.GetVelocity();
        this->Vunit = VectorOperation::Normalize(u1);
        gravity = std::abs(F1.GetAcceleration().y);
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
        F1.SetVelocity(this->u1);
    }
}




bool ContactMech::AABBIntersect(std::shared_ptr<GameShape> playerShape, std::shared_ptr<GameShape> otherShape) {
    sf::Vector2f playerPosition = playerShape->GetPosition();
    sf::Vector2f playerSize = playerShape->GetSize();
    sf::Vector2f otherPosition = otherShape->GetPosition();
    sf::Vector2f otherSize = otherShape->GetSize();

    float playerLeft = playerPosition.x;
    float playerRight = playerPosition.x + playerSize.x;
    float playerTop = playerPosition.y;
    float playerBottom = playerPosition.y + playerSize.y;
    float otherLeft = otherPosition.x;
    float otherRight = otherPosition.x + otherSize.x;
    float otherTop = otherPosition.y;
    float otherBottom = otherPosition.y + otherSize.y;
   // std::cout << "player pos  = " << playerLeft << " " << playerTop << std::endl;
    //std::cout << "other pos  = " << otherLeft << " " << otherTop << std::endl << std::endl;
    bool horizontalOverlap = (playerLeft < otherRight) && (playerRight > otherLeft);
    bool verticalOverlap = (playerTop < otherBottom) && (playerBottom > otherTop);
    return horizontalOverlap && verticalOverlap;
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
        this->resolution.x = (B1.left < B2.left)
            ? -horizontalOverlap : horizontalOverlap;
    }
    else {
        this->resolution.y = (B1.top < B2.top)
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
   //std::cout << "  v1  - " << v1.x << " " << v1.y << std::endl;
   //std::cout << "  v2  - " << v2.x << " " << v2.y << std::endl << std::endl;
}


