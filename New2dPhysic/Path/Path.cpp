#include "Path.h"
#include "../PhysicUtility/Utility.h"
#include "../GameObjects.h"

Path::Path(const int id, const float& mass, const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Vector2f& velocity,
    const sf::Vector2f& accleration)
    : GameShape(id, mass, pos, size, velocity, accleration,
        sf::Vector2f(GMNumber::COEFF_OF_RESTITUTION_PATH_X , GMNumber::COEFF_OF_RESTITUTION_PATH_Y),
        sf::Vector2f(GMNumber::COEFF_OF_FRICTION_PATH, GMNumber::COEFF_OF_FRICTION_PATH)) {
    this->shape->setPosition(this->position);
    this->shape->setSize(this->size);
    // gameObject.grid.AddObject(this->path ,this->ID);
}

void Path::Load() {
    this->shape->setFillColor(sf::Color::Blue);
}

void Path::Update(const float& dT) {
    if (this->velocity.x != 0 || this->velocity.y != 0) {
        this->shape->setPosition(this->NewPosition(dT));
    }
}

void Path::PathBasedCollisionHandle(sf::FloatRect& Bound1, RigidBody& F1, sf::FloatRect& Bound2, RigidBody& F2) {
    this->B1 = Bound1;
    this->B2 = Bound2;
    DirectionFinder();
    this->M1 = F1.GetMass();
    this->M2 = F2.GetMass();
    u1 = F1.GetVelocity();
    u2 = F2.GetVelocity();
    PenetrationResoluter(F1, F2);



    auto E1 = F1.GetCoefficientOfRestitution();
    auto E2 = F2.GetCoefficientOfRestitution();
    std::cout << " player e = " << E1.x << " " << E1.y << std::endl;
    std::cout << " other e = " << E2.x << " " << E2.y << std::endl;


    EffectiveEFinder(F1, F2);

    if (this->horizontalOverlap < this->verticalOverlap) {
        this->eEffective = e.x;
        std::cout << "effective e H = " << eEffective << std::endl;
        if (M2 > GMNumber::MASS_THRESHOLD * M1 && std::abs(v2.x) < GMNumber::COLLISION_VELOCITY_THRESHOLD) {
            v1.x = -eEffective * u1.x;
            v2.x = GMNumber::ZERO;
        }
        else if (M1 > GMNumber::MASS_THRESHOLD * M2 && std::abs(v1.x) < GMNumber::COLLISION_VELOCITY_THRESHOLD) {
            v2.x = -eEffective * u2.x;
            v1.x = GMNumber::ZERO;
        }
        else {
            v1.x = ((M1 - eEffective * M2) * u1.x + (1 + eEffective) * M2 * u2.x) / (M1 + M2);
            v2.x = ((M2 - eEffective * M1) * u2.x + (1 + eEffective) * M1 * u1.x) / (M1 + M2);
        }
        v1.y = u1.y;
        v2.y = u2.y;
    }
    else {
        this->eEffective = e.y;
        std::cout << "effective e V = " << eEffective << std::endl;
        if (M2 > GMNumber::MASS_THRESHOLD * M1 && std::abs(v2.y) < GMNumber::COLLISION_VELOCITY_THRESHOLD) {
            v1.y = -eEffective * u1.y;
            v2.y = GMNumber::ZERO;
        }
        else if (M1 > GMNumber::MASS_THRESHOLD * M2 && std::abs(v1.y) < GMNumber::COLLISION_VELOCITY_THRESHOLD) {
            v2.y = -eEffective * u2.y;
            v1.y = GMNumber::ZERO;
        }
        else {
            v1.y = ((M1 - eEffective * M2) * u1.y + (1 + eEffective) * M2 * u2.y) / (M1 + M2);
            v2.y = ((M2 - eEffective * M1) * u2.y + (1 + eEffective) * M1 * u1.y) / (M1 + M2);
        }
        v1.x = u1.x;
        v2.x = u2.x;
    }
    std::cout << std::endl;
    CollisionThreshold();
    F1.SetVelocity(v1);
    F2.SetVelocity(v2);
    ResetForNewCollision();
}

void Path::CollisionRedirection(std::shared_ptr<GameShape> playerShape,
    std::shared_ptr<GameShape> otherShape, ContactMech& contact) {
    contact.PathCollsionHandleWithShape(playerShape, otherShape);
}

void Path::Draw(std::shared_ptr<sf::RenderWindow>window) {
    window->draw(*this->shape);
}

inline void Path::FindMaxVelocities() {
    if (this->mass == 0) {
        this->mass = 1.0f;
    }
    this->maxvelocity = this->velocity;
}
