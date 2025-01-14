#include "ContactMechanic.h"
#include"../PhysicUtility/Utility.h"
#include<algorithm>
#include<cmath>
#include"GameShapes.h"
#include"../Objects/Rect.h"
#include"../Objects/Collectable.h"
#include"../Objects/Rect.h"

ContactMech::ContactMech():
    horizontalOverlap(0.0f), verticalOverlap(0.0f),
    M1(0.0f) , M2(0.0f),
    gravity(0.0f) , frictionDeceleratedVelocity(0.0f){
}


void ContactMech::CollsionDetection(std::shared_ptr<GameShape> playerShape,
    std::shared_ptr<GameShape> otherShape) {
    auto player = sf::FloatRect(playerShape->GetPosition(), playerShape->GetSize());
    auto other = sf::FloatRect(otherShape->GetPosition(), otherShape->GetSize());

    if (CollisionBetweenCircleAndRectangle(player, other)) {
        CollisionDetermination(playerShape, otherShape);
    }
}

void ContactMech::ApplyFriction(std::shared_ptr<GameShape> playerShape, std::shared_ptr<GameShape> otherShape, const float& dt) {
    auto player = sf::FloatRect(playerShape->GetPosition(), playerShape->GetSize());
    auto other = sf::FloatRect(otherShape->GetPosition(), otherShape->GetSize());

    if (CollisionBetweenCircleAndRectangle(player, other)) {
        this->coeffOfFriction = otherShape->GetCoefficientOfFriction();
        this->u1 = playerShape->GetVelocity();
        this->Vunit = VectorOperation::Normalize(u1);
        gravity = GMNumber::GRAVITY;
        Direction direction = CollisionDirectionFinder(playerShape, otherShape);
        //  INCASE OF FRICTION THE DIRECTION IS REVERSED VERTICAL DIRECTION GIVES
       //  HORIZONTAL FRICTION AND HORIZONTAL DIRECTION GIVES VERTICAL FRICTION
        if (direction == Right || direction == Left) {
            this->frictionDeceleratedVelocity = -this->coeffOfFriction.y * gravity * this->Vunit.y * dt;
            if (std::abs(this->u1.y) < GMNumber::LOWEST_VELOCITY_THRESHOLD) { this->u1.y = 0.0f; }
            this->u1 += {0.0f, this->frictionDeceleratedVelocity};
        }
        else if (direction == Bottom || direction == Top) {
            this->frictionDeceleratedVelocity = -this->coeffOfFriction.x * gravity * this->Vunit.x * dt;
            if (std::abs(this->u1.x) < GMNumber::LOWEST_VELOCITY_THRESHOLD) { this->u1.x = 0.0f; }
            this->u1 += {this->frictionDeceleratedVelocity, 0.0f};
        }
        playerShape->SetVelocity(this->u1);
    }
}


bool ContactMech::CollisionBetweenCircleAndRectangle(sf::FloatRect& B1, sf::FloatRect& B2) {
    float radius = (B1.width -.01f) * 0.5f;  // DONT KNOW WHY AFTER SUBTRACTING 0.01f THERE THE COLLISION DETECTION WORK
    // SO I AM GOING TO LEAVE IT AS IT IS FOR NOW , I WILL FIND THE REASON FOR THIS IF I GOT ANY TIME
    // I KNOW I AM NEVER GOING TO FIND THE REASON "IF IT WORKS SO DONT TOUCH IT"
    float distX = std::abs(B1.left + radius - (B2.left + B2.width / 2.0f));
    float distY = std::abs(B1.top + radius - (B2.top + B2.height / 2.0f));
    if (distX > (B2.width / 2.0f + radius)) return false;
    if (distY > (B2.height / 2.0f + radius)) return false;
    if (distX <= (B2.width / 2.0f)) return true;
    if (distY <= (B2.height / 2.0f)) return true;
    float dx = distX - B2.width / 2.0f;
    float dy = distY - B2.height / 2.0f;
    return (dx * dx + dy * dy) <= (radius * radius);
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
    case CollisionId::InflatorId:
        InflatorCollisionHandle(playerShape, otherShape);
        break;
    case CollisionId::DeflatorId:
        DeflatorCollisionHandle(playerShape, otherShape);
		break;
	case CollisionId::CollectableId:
		CollectableCollisionHandle(playerShape, otherShape);
    default:
        break;
    }
}






Direction ContactMech::HeavyObjectCollisionHandle(std::shared_ptr<GameShape> playerShape,
    std::shared_ptr<GameShape> otherShape) {

    if (!playerRefenceBools.canJumping) {playerRefenceBools.canJumping = true;}

    Direction collisionDirection = CollisionDirectionFinder(playerShape, otherShape);

    this->M1 = playerShape->GetMass();
    this->M2 = otherShape->GetMass();
    this->u1 = playerShape->GetVelocity();
    this->u2 = otherShape->GetVelocity();
    NewPenetrationResoluter(*playerShape, *otherShape , collisionDirection);
    EffectiveEFinder(*playerShape, *otherShape);
    switch (collisionDirection) {
    case Right:
    case Left:
        if (std::abs(playerShape->GetVelocity().x) > GMNumber::COlliSION_VELOCITY_THRESHOLD.x) {
			CalculateVelocity(v1.x, v2.x, u1.x, u2.x, M1, M2, e.x);
			v1.y = u1.y;
			v2.y = u2.y;
		}
		else {
            v1 = {0.0f , u1.y};
			v2 = u2;
        }
        break;

    case Bottom:
    case Top:
		if (std::abs(playerShape->GetVelocity().y) > GMNumber::COlliSION_VELOCITY_THRESHOLD.x) {
			CalculateVelocity(v1.y, v2.y, u1.y, u2.y, M1, M2, e.y);
			v1.x = u1.x;
			v2.x = u2.x;
		}
		else {
            v1 = { u1.x , 0.0f};
            v2 = u2;
		}
        break;

    default:
        break;
    }
   CollisionThreshold();
    playerShape->SetVelocity(v1);
    otherShape->SetVelocity(v2);
    ResetForNewCollision();
    return collisionDirection;
}



void ContactMech::LightObjectCollisionHandle(std::shared_ptr<GameShape> playerShape,
    std::shared_ptr<GameShape> otherShape) {
    // GETTING THE VARIABLES
	Direction collisionDirection = CollisionDirectionFinder(playerShape, otherShape);
    this->M1 = playerShape->GetMass();
    this->M2 = otherShape->GetMass();
    this->u1 = playerShape->GetVelocity();
    this->u2 = otherShape->GetVelocity();

    PenetrationResoluter(*playerShape, *otherShape , collisionDirection);
    EffectiveEFinder(*playerShape, *otherShape);
    v1.x = ((M1 - e.x * M2) * u1.x + (1 + e.x) * M2 * u2.x) / (M1 + M2);
    v1.y = ((M1 - e.y * M2) * u1.y + (1 + e.y) * M2 * u2.y) / (M1 + M2);
    v2.x = ((M2 - e.x * M1) * u2.x + (1 + e.x) * M1 * u1.x) / (M1 + M2);
    v2.y = ((M2 - e.y * M1) * u2.y + (1 + e.y) * M1 * u1.y) / (M1 + M2);
    CollisionThreshold();
    playerShape->SetVelocity(v1);
    otherShape->SetVelocity(v2);
    ResetForNewCollision();

}



void ContactMech::InflatorCollisionHandle(std::shared_ptr<GameShape> playerShape, std::shared_ptr<GameShape> otherShape){
	Direction direction = HeavyObjectCollisionHandle(playerShape, otherShape);

    const float& referenceSize = GMNumber::BIG_BALL_SIZE;
	if (playerShape->GetSize().x == referenceSize ) { return; }

    float reAdjust = GMNumber::READJUST_SIZE;
	sf::Vector2f positionAdjust(0.0f, 0.0f);
	switch (direction) {
	case Right:
    case Bottom:
		break;
	case Left:
        positionAdjust = { - reAdjust , - reAdjust };
		break;
	case Top:
        positionAdjust = {0.0f , - reAdjust };
		break;
	default:
		break;
	}
	playerShape->SetPosition(playerShape->GetPosition() + positionAdjust);
	playerShape->SetSize({ referenceSize, referenceSize });
}




void ContactMech::DeflatorCollisionHandle(std::shared_ptr<GameShape> playerShape, std::shared_ptr<GameShape> otherShape){
    HeavyObjectCollisionHandle(playerShape, otherShape);
	const float& referenceSize = GMNumber::SMALL_BALL_SIZE;
	if (playerShape->GetSize().x != referenceSize) {
		playerShape->SetSize({ referenceSize,referenceSize });
	}
}

void ContactMech::CollectableCollisionHandle(std::shared_ptr<GameShape> playerShape,
    std::shared_ptr<GameShape> otherShape) {
    std::shared_ptr<Rect> player = std::dynamic_pointer_cast<Rect>(playerShape);
    if (!player) {return;}
    std::shared_ptr<Collectable> collectable = std::dynamic_pointer_cast<Collectable>(otherShape);
    if (!collectable) {return;}
    player->SetPoints(player->GetPoints() + collectable->GetPoint());
    collectable->SetCanBeDeleted(true);
}






Direction ContactMech::CollisionDirectionFinder(std::shared_ptr<GameShape> playerShape,
    std::shared_ptr<GameShape> otherShape) {
    const auto& playerPos = playerShape->GetPosition();
    const auto& playerSize = playerShape->GetSize();
    const auto& otherPos = otherShape->GetPosition();
    const auto& otherSize = otherShape->GetSize();

  	this->horizontalOverlap = std::min(playerPos.x + playerSize.x, otherPos.x + otherSize.x) - std::max(playerPos.x, otherPos.x);
	this->verticalOverlap = std::min(playerPos.y + playerSize.y, otherPos.y + otherSize.y) - std::max(playerPos.y, otherPos.y);

	if (this->horizontalOverlap < this->verticalOverlap) {
		if (playerPos.x + playerSize.x > otherPos.x + otherSize.x) { return Direction::Right; }
		else { return Direction::Left; }
	}
	else {
		if (playerPos.y + playerSize.y > otherPos.y + otherSize.y) { return Direction::Bottom; }
		else { return Direction::Top; }
	}

}


void ContactMech::ResetForNewCollision() {
    v1 = { 0.0f,0.0f }; v2 = { 0.0f,0.0f };
    resolution = { 0.0f, 0.0f };
}

void ContactMech::PenetrationResoluter(GameShape& player,GameShape& other,
    Direction direction){
	this->resolution = { 0.0f, 0.0f };
	auto& playerPos = player.GetPosition();
	auto& otherPos = other.GetPosition();
	switch (direction) {
	case Right:
        resolution.x = horizontalOverlap;
        break;
	case Left:
        resolution.x = -horizontalOverlap;
		break;
	case Bottom:
		resolution.y = verticalOverlap;
		break;
	case Top:
        resolution.y = -verticalOverlap;
		break;
	default:
		break;
	}
	// RESOLVING THE PENETRATION BASED ON THEIR MASSES
    player.SetPosition(playerPos + resolution);
}

void ContactMech::NewPenetrationResoluter(GameShape& player,
    GameShape& other, Direction direction){

	const auto& playersize = player.GetSize() * 0.5f;
    const auto& circleCentre = player.GetPosition() + playersize;
	const auto& top = other.GetPosition();
    const auto& bottom = top + other.GetSize();
	sf::Vector2f closestPoint(0.0f, 0.0f);
    this->resolution = { 0.0f,0.0f };

    closestPoint.x = std::max(top.x, std::min(bottom.x, circleCentre.x));
	closestPoint.y = std::max(top.y, std::min(bottom.y, circleCentre.y));
	sf::Vector2f normal = closestPoint - circleCentre;

	float magnitude = VectorOperation::Magnitude(normal);
	if (magnitude == 0.0f) {
        std::cout << "zero " << "\n";
        magnitude = 1.0f; 
    }

	float overlap = playersize.x  - magnitude;
    normal = normal / magnitude;


    switch (direction){
    case Right:
    case Left:
		this->resolution.x = -normal.x * overlap;
        break;
    case Top:
    case Bottom:
		this->resolution.y = -normal.y * overlap  - 0.16755f * Sign(normal.y);
        // LEAVE 0.16755f*SIGN(NORMAL.Y) AS IT IS SINCE IT HELP TO REMOVE
		// FLOAT ERROR OTHERWISE FUNCTION WILL NOT WORK AS INTENDED
        // THINK IT AS WE R TRUNCATING DECIMALS
        break;
    default:
        break;
    }
	player.SetPosition(circleCentre + resolution - playersize);
}


void ContactMech::EffectiveEFinder(RigidBody& F1, RigidBody& F2){
   this->e = { (F2.GetCoefficientOfRestitution().x + F1.GetCoefficientOfRestitution().x)/2 ,
        (F2.GetCoefficientOfRestitution().y + F1.GetCoefficientOfRestitution().y)/2 };
}

inline void ContactMech::CollisionThreshold(){
    const auto& Threshold = GMNumber::COlliSION_VELOCITY_THRESHOLD;
    if (std::abs(v1.x) <= Threshold.x) { v1.x = 0.0f; }
    if (std::abs(v1.y) <= Threshold.y) { v1.y = 0.0f; }
    if (std::abs(v2.x) <= Threshold.x) { v2.x = 0.0f; }
    if (std::abs(v2.y) <= Threshold.y) { v2.y = 0.0f; }
}





void ContactMech::CalculateVelocity(float& v1, float& v2, float u1, float u2, float M1, float M2, float eEffective) {
	const float& Mthe = GMNumber::MASS_THRESHOLD;
	const float& Vthe = GMNumber::LOWEST_VELOCITY_THRESHOLD;
    if (M2 > Mthe * M1 && std::abs(v2) < Vthe) {
        v1 = -eEffective * u1;
        v2 = 0.0f;
    }
    else if (M1 > Mthe * M2 && std::abs(v1) < Vthe) {
        v2 = -eEffective * u2;
        v1 = 0.0f;
    }
    else {
        v1 = ((M1 - eEffective * M2) * u1 + (1 + eEffective) * M2 * u2) / (M1 + M2);
        v2 = ((M2 - eEffective * M1) * u2 + (1 + eEffective) * M1 * u1) / (M1 + M2);
    }
}

float ContactMech::Sign(float& num){
    if (num < 0.0f) { return -1.0f; }
    else if (num == 0.0f) { return 0.0f; }
    else { return 1.0f; }
}

