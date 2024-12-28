#include "ContactMechanic.h"
#include"../PhysicUtility/Utility.h"
#include<algorithm>
#include<cmath>
#include"GameShapes.h"
#include"../Objects/Rect.h"

ContactMech::ContactMech():
    horizontalOverlap(0.0f), verticalOverlap(0.0f),
    eEffective(0.0f) , M1(0.0f) , M2(0.0f),
    gravity(0.0f) , frictionDeceleratedVelocity(0.0f),
    isTop(false),isBottom(false),
    isLeft(false), isRight(false){

    std::cout << " col2 = " << GMNumber::COLLISION_VELOCITY_THRESHOLD_X << " " << GMNumber::COLLISION_VELOCITY_THRESHOLD_Y << std::endl;
}


void ContactMech::CollsionDetection(std::shared_ptr<GameShape> playerShape,
    std::shared_ptr<GameShape> otherShape) {
    auto player = sf::FloatRect(playerShape->GetPosition(), playerShape->GetSize());
    auto other= sf::FloatRect(otherShape->GetPosition(), otherShape->GetSize());
    if (player.intersects(other)) {
        CollisionDetermination(playerShape, otherShape);
    }
}




void ContactMech::ApplyFriction(std::shared_ptr<GameShape> playerShape, std::shared_ptr<GameShape> otherShape, const float& dt){
    this->B1 = sf::FloatRect(playerShape->GetPosition(), playerShape->GetSize());
    this->B2 = sf::FloatRect(otherShape->GetPosition(), otherShape->GetSize());
    if (B1.intersects(B2)) {
        this->coeffOfFriction = otherShape->GetCoefficientOfFriction();
        this->u1 = playerShape->GetVelocity();
        this->Vunit = VectorOperation::Normalize(u1);
        gravity = GMNumber::GRAVITY;
        if (HorizontalOrVerticalOverlapDirectionFinder()) { //vertical friction
            this->frictionDeceleratedVelocity = -this->coeffOfFriction.y * gravity * this->Vunit.y * dt;
            if (std::abs(this->u1.y) < GMNumber::LOWEST_VELOCITY_THRESHOLD) { this->u1.y = 0.0f; }
            this->u1 += {0.0f, this->frictionDeceleratedVelocity };
        }
        else { // horizontal friction
            this->frictionDeceleratedVelocity = -this->coeffOfFriction.x * gravity * this->Vunit.x * dt;
            if (std::abs(this->u1.x) < GMNumber::LOWEST_VELOCITY_THRESHOLD) { this->u1.x = 0.0f; }
            this->u1 += { this->frictionDeceleratedVelocity, 0.0f};
        }
        playerShape->SetVelocity(this->u1);
    }
}


void ContactMech::CollisionDetermination(std::shared_ptr<GameShape> playerShape,
    std::shared_ptr<GameShape> otherShape){
    switch (otherShape->GetCollisionId()) {
    case CollisionId::PlayerId:
        break;
    case CollisionId::HeavyPathId:
        HeavyObjectCollisionHandle(playerShape, otherShape);
        break;
    case CollisionId::LightPathId:
        LightObjectCollisionHandle(playerShape, otherShape);
        break;
    case CollisionId::InfilatorId:
        InflatorCollisionHandle(playerShape, otherShape);
        break;
    case CollisionId::DeflatorId:
        DeflatorCollisionHandle(playerShape, otherShape);
    default:
        break;
    }
}


void ContactMech::HeavyObjectCollisionHandle(std::shared_ptr<GameShape> playerShape,
    std::shared_ptr<GameShape> otherShape) {

    this->B1 = sf::FloatRect(playerShape->GetPosition(), playerShape->GetSize());
    this->B2 = sf::FloatRect(otherShape->GetPosition(), otherShape->GetSize());

    bool isHorizontal = HorizontalOrVerticalOverlapDirectionFinder();

    this->M1 = playerShape->GetMass();
    this->M2 = otherShape->GetMass();
    this->u1 = playerShape->GetVelocity();
    this->u2 = otherShape->GetVelocity();

    PenetrationResoluter(*playerShape, *otherShape);
    EffectiveEFinder(*playerShape, *otherShape);

    if (isHorizontal) { // Horizontal collision
        this->eEffective = e.x; 
        if (M2 > GMNumber::MASS_THRESHOLD * M1 && std::abs(v2.x) < GMNumber::LOWEST_VELOCITY_THRESHOLD) {
            v1.x = -eEffective * u1.x;
            v2.x = 0.0f;
        }
        else if (M1 > GMNumber::MASS_THRESHOLD * M2 && std::abs(v1.x) < GMNumber::LOWEST_VELOCITY_THRESHOLD) {
            v2.x = -eEffective * u2.x;
            v1.x = 0.0f;
        }
        else {
            v1.x = ((M1 - eEffective * M2) * u1.x + (1 + eEffective) * M2 * u2.x) / (M1 + M2);
            v2.x = ((M2 - eEffective * M1) * u2.x + (1 + eEffective) * M1 * u1.x) / (M1 + M2);
        }
        v1.y = u1.y;
        v2.y = u2.y;
    }
    else {  // Vertical collision
        this->eEffective = e.y; 
        if (M2 > GMNumber::MASS_THRESHOLD * M1 && std::abs(v2.y) < GMNumber::LOWEST_VELOCITY_THRESHOLD) {
            v1.y = -eEffective * u1.y;
            v2.y = 0.0f;
        }
        else if (M1 > GMNumber::MASS_THRESHOLD * M2 && std::abs(v1.y) < GMNumber::LOWEST_VELOCITY_THRESHOLD) {
            v2.y = -eEffective * u2.y;
            v1.y = 0.0f; 
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
    otherShape->SetVelocity(v2);
    ResetForNewCollision();
}



void ContactMech::LightObjectCollisionHandle(std::shared_ptr<GameShape> playerShape,
    std::shared_ptr<GameShape> otherShape) {
    // GETTING THE VARIABLES
    this->B1 = sf::FloatRect(playerShape->GetPosition(), playerShape->GetSize());
    this->B2 = sf::FloatRect(otherShape->GetPosition(), otherShape->GetSize());
    this->M1 = playerShape->GetMass();
    this->M2 = otherShape->GetMass();
    this->u1 = playerShape->GetVelocity();
    this->u2 = otherShape->GetVelocity();

    PenetrationResoluter(*playerShape, *otherShape);
    EffectiveEFinder(*playerShape, *otherShape);

    v1.x = ((M1 - eEffective * M2) * u1.x + (1 + e.x) * M2 * u2.x) / (M1 + M2);
    v1.y = ((M1 - eEffective * M2) * u1.y + (1 + e.y) * M2 * u2.y) / (M1 + M2);
    v2.x = ((M2 - eEffective * M1) * u2.x + (1 + eEffective) * M1 * u1.x) / (M1 + M2);
    v2.y = ((M2 - eEffective * M1) * u2.y + (1 + eEffective) * M1 * u1.y) / (M1 + M2);

    CollisionThreshold();
    playerShape->SetVelocity(v1);
    otherShape->SetVelocity(v2);
    ResetForNewCollision();

}

void ContactMech::InflatorCollisionHandle(std::shared_ptr<GameShape> playerShape,
    std::shared_ptr<GameShape> otherShape) {
    HeavyObjectCollisionHandle(playerShape, otherShape);
    this->v1 = playerShape->GetSize();
    float referenceSize = GMNumber::BIG_BALL_SIZE;

    if (v1.x == referenceSize) {
        return;
    }
    float reAdjust = GMNumber::SMALL_BALL_SIZE * (GMNumber::BIG_SMALL_BALL_RATIO - 1.0f);
    DirectionalCollisionChecker();
    sf::Vector2f positionAdjust(0.0f, 0.0f);

    if (this->isTop) {positionAdjust.y -= reAdjust;}
    else if (this->isBottom) {positionAdjust.y += reAdjust;}
    if (this->isLeft) {positionAdjust.x -= reAdjust; positionAdjust.y -= reAdjust;}
    else if (this->isRight) {positionAdjust.y -= reAdjust;}
    playerShape->SetPosition(playerShape->GetPosition() + positionAdjust);
    playerShape->SetSize({ referenceSize, referenceSize });
}


void ContactMech::DeflatorCollisionHandle(std::shared_ptr<GameShape> playerShape, std::shared_ptr<GameShape> otherShape){
    HeavyObjectCollisionHandle(playerShape, otherShape);
    this->v1 = playerShape->GetSize();
    float referenceSize = GMNumber::SMALL_BALL_SIZE;
    if (v1.x != referenceSize) {
        playerShape->SetSize({ referenceSize,referenceSize });
    }
}






void ContactMech::ResetForNewCollision() {  // LEAVING 0 AS IT IS ,SINCE IT WILL BE CALLED AND
    // ASKING VALUE FROM GMNUMBER MIGHT BE LONGER FOR PROCRSSING
    v1 = { 0.0f,0.0f }; v2 = { 0.0f,0.0f };
    resolution = { 0.0f, 0.0f };
    eEffective = 0.0f;
}



inline bool ContactMech::HorizontalOrVerticalOverlapDirectionFinder(){
    this->horizontalOverlap = std::min(B1.left + B1.width, B2.left + B2.width) - std::max(B1.left, B2.left);
    this->verticalOverlap = std::min(B1.top + B1.height, B2.top + B2.height) - std::max(B1.top, B2.top);
    if (this->horizontalOverlap < this->verticalOverlap) { return true; }
    else { return false; }

}

void ContactMech::DirectionalCollisionChecker()  {
    this->isTop = this->isBottom = this->isLeft = this->isRight = false;
    bool isHorizontal = HorizontalOrVerticalOverlapDirectionFinder();
    if (isHorizontal) {
        if (B1.left + B1.width > B2.left + B2.width) {
            this->isRight = true;
        }
        else {
            this->isLeft = true;
        }
    }
    else {
        if (B1.top + B1.height > B2.top + B2.height) {
            this->isBottom = true;
        }
        else {
            this->isTop = true;
        }
    }
}

void ContactMech::PenetrationResoluter(RigidBody& F1, RigidBody& F2) {
    if (this->horizontalOverlap < this->verticalOverlap) {
        this->resolution.x = (B1.left < B2.left)
            ? -horizontalOverlap : horizontalOverlap;
    }
    else {
        this->resolution.y =  (B1.top < B2.top)
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
    const float thresholdx = GMNumber::COLLISION_VELOCITY_THRESHOLD_X;
    const float thresholdy = GMNumber::COLLISION_VELOCITY_THRESHOLD_Y;

    if (std::abs(v1.x) <= thresholdx) { v1.x = 0.0f; }
    if (std::abs(v1.y) <= thresholdy) { v1.y = 0.0f; }
    if (std::abs(v2.x) <= thresholdx) { v2.x = 0.0f; }
    if (std::abs(v2.y) <= thresholdy) { v2.y = 0.0f; }

}


