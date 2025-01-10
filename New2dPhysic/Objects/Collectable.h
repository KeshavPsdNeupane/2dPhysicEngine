#pragma once
#include"../Body/GameShapes.h"

class Collectable :public GameShape {
    unsigned int point;
	bool canBeDeleted;
public:
    Collectable() = default;
    Collectable(const int id, const int colid, const float mass,const unsigned int points,
        const sf::Vector2f pos,const sf::Vector2f size);
    ~Collectable();
public:
	inline void SetPoint(const unsigned int point) { this->point = point; }
    inline unsigned int GetPoint() const { return this->point; }
	inline void SetCanBeDeleted(const bool canBeDeleted) {this->canBeDeleted = canBeDeleted;}
    inline bool GetCanBeDeleted() const { return this->canBeDeleted; }
public:
    void Load(std::shared_ptr<Engine::ResourceManager> resources) override;
    void Update(const float& dt) override;
    void Draw(std::shared_ptr<sf::RenderWindow>window) override;

private:
    inline void FindMaxVelocities() override;
};