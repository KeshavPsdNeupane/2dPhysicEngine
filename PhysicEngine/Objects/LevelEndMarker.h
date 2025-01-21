#pragma once
#include<SFML/Graphics.hpp>
#include"../Body/GameShapes.h"


class LevelEndMarker :public GameShape {
    int textureId;
    sf::Sprite sprite;
public:
    LevelEndMarker() = default;
    LevelEndMarker(const int id, const int colid, const int textureId,
        const sf::Vector2f pos, const sf::Vector2f size);
    ~LevelEndMarker();
public:
    void Load(std::shared_ptr<Engine::ResourceManager> resources) override;
    void Update(const float& dt) override;
    void Draw(std::shared_ptr<sf::RenderWindow>window) override;

};