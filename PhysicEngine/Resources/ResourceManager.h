#pragma once
#include<iostream>
#include<map>
#include<memory>
#include<SFML/Graphics.hpp>
#include<string>

enum ResourceId {
	MAIN_FONT = 0,
	PLAYER_TEXTURE,
	PLAYER_FONT,
	ENEMY_FONT,
	TILE_TEXTURE,
};

namespace Engine {
	class ResourceManager {
	private:
		std::map<int, std::unique_ptr<sf::Texture>> texture;
		std::map<int, std::unique_ptr<sf::Font>> font;

	public:
		ResourceManager();
		~ResourceManager();
	public:
		void AddTexture(int id, std::string filePath, bool wantRepeated = false);
		void AddFont(int id, std::string filePath);

		const sf::Texture& GetTexture(int id) const;
		const sf::Font& GetFont(int id) const;

	};

}