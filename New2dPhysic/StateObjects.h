#pragma once
#include<SFML/Graphics.hpp>
#include"States/StateManager.h"
#include"Resources/ResourceManager.h"
#include"Body/ContactMechanic.h"

struct StateData {
	std::shared_ptr<Engine::StateManager> stateManager;
	std::shared_ptr<Engine::ResourceManager> resourceManager;
	std::shared_ptr<ContactMech> contactMechanic;
	std::shared_ptr<sf::RenderWindow> window;

	StateData() {
		stateManager = std::make_shared<Engine::StateManager>();
		resourceManager = std::make_shared<Engine::ResourceManager>();
		contactMechanic = std::make_shared<ContactMech>();
		window = std::make_shared<sf::RenderWindow>();
	}
};