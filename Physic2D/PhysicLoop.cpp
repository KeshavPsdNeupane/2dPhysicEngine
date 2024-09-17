#include "PhysicLoop.h"
#include"GameObjects.h"
PhysicLoop::PhysicLoop()
: window(std::make_shared<sf::RenderWindow>(sf::VideoMode(800,600), " Physic Engine")),
event(), clock(), DT(0.0f) {
	this->window->setFramerateLimit(120);
}

void PhysicLoop::RunPlysicLoop(){
	Load();
	while (window->isOpen()) {
		SFMLEvent();
		Update();
		window->clear();
		Draw();
		window->display();
	}
}

void PhysicLoop::SFMLEvent(){
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void PhysicLoop::Load(){
	gameObject.rectangle.Load();
	gameObject.path.Load();
}

void PhysicLoop::Update(){
	Deltatime();
	gameObject.rectangle.Update(this->DT);
}

void PhysicLoop::Draw(){
	gameObject.rectangle.Draw(window);
	gameObject.path.Draw(window);
}

void PhysicLoop::Deltatime(){
	this->DT = clock.restart().asSeconds();
}
