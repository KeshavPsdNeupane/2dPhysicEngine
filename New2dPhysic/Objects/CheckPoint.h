#pragma once
#include<SFML/Graphics.hpp>
#include"../Body/GameShapes.h"


class CheckPoint : public GameShape{
    bool isFound;
public:
    CheckPoint() = default;
    CheckPoint(const int id, const int colid,const sf::Vector2f pos,const sf::Vector2f size);
    ~CheckPoint();
public:
	void SetIsFound(bool isFound = true ) { this->isFound = isFound; }
	const bool& GetIsFound()const  { return this->isFound;}

public:
    void Load(std::shared_ptr<Engine::ResourceManager> resources) override;
    void Update(const float& dt) override;
    void Draw(std::shared_ptr<sf::RenderWindow>window) override;
};