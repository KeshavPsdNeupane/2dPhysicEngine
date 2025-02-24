#include "ResourceManager.h"

Engine::ResourceManager::ResourceManager() {}

Engine::ResourceManager::~ResourceManager() {}

void Engine::ResourceManager::AddTexture(int id, std::string filePath, bool wantRepeated) {
	auto texture = std::make_unique<sf::Texture>();
	if (texture->loadFromFile(filePath)) {
		this->texture[id] = std::move(texture);
		this->texture[id]->setRepeated(wantRepeated);
	}
	else {
		std::cout << "Error: AssetMan::AddTexture for id  = " << id << std::endl;
	}
}

void Engine::ResourceManager::AddFont(int id, std::string filePath) {
	auto font = std::make_unique<sf::Font>();
	if (font->loadFromFile(filePath)) {
		this->font[id] = std::move(font);
	}
	else {
		std::cout << "Error: resourceManagerMan::AddTexture" << std::endl;
	}
}

const sf::Texture& Engine::ResourceManager::GetTexture(int id) const {
	return *this->texture.at(id);
}

const sf::Font& Engine::ResourceManager::GetFont(int id) const {
	return *this->font.at(id);
}
