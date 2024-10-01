#include "PhysicLoop.h"
#include"GameObjects.h"
PhysicLoop::PhysicLoop()
: window(std::make_shared<sf::RenderWindow>(sf::VideoMode(static_cast<int>(GMNumber::WINDOW_WIDTH),
	static_cast<int>(GMNumber::WINDOW_HEIGHT)),
	" Physic Engine")),
event(), clock(), DT(0.0f) {
	this->window->setFramerateLimit(GMNumber::MAX_FRAME_RATE);
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
	//gameObject.path.Load();
	for (int i = 0; i < gameObject.path.size(); ++i) {
		gameObject.path[i].Load();
	}
}

void PhysicLoop::Update() {
	Deltatime();
	gameObject.rectangle.Update(this->DT);
	for (int i = 0; i < gameObject.path.size(); ++i) {
		gameObject.path[i].Update(DT);
		gameObject.rectangle.CollisionUpdate(*gameObject.path[i].GetShape(),
			gameObject.path[i].GetFrame(), gameObject.path[i].GetContactHandler());
	}
}

void PhysicLoop::Draw(){
	gameObject.rectangle.Draw(window);
	//gameObject.path.Draw(window);
	for (int i = 0; i < gameObject.path.size(); ++i) {
		gameObject.path[i].Draw(window);
	}
	gameObject.grid.Draw(window);
}

void PhysicLoop::Deltatime(){
	this->DT = clock.restart().asSeconds();
}
