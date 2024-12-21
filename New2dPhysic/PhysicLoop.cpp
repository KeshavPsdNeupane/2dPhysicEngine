#include "PhysicLoop.h"
#include"GameObjects.h"
PhysicLoop::PhysicLoop()
: window(std::make_shared<sf::RenderWindow>(sf::VideoMode(static_cast<int>(GMNumber::WINDOW_WIDTH),
	static_cast<int>(GMNumber::WINDOW_HEIGHT)),
	" Physic Engine")),
event(), clock(),
collisionAndFriction(),
updateDrawResultFromGrid(),
collisionResultFromGrid(),
DT(0.0f) {
	this->window->setFramerateLimit(GMNumber::MAX_FRAME_RATE);

	// for player  this is a temp
	sf::Vector2f nil = sf::Vector2f(0.0f, 0.0f);
	gameObject.rectangle = std::make_shared<Rect>(1,CollisionId::PlayerId, 60.0f, sf::Vector2f(410.0f, 200.0f),
		sf::Vector2f(25.0f, 25.0f), nil, nil,
		sf::Vector2f(GMNumber::COEFF_OF_RESTITUTION_OBJECT_X, GMNumber::COEFF_OF_RESTITUTION_OBJECT_Y)
		, sf::Vector2f(GMNumber::COEFF_OF_FRICTION_OBJECT, GMNumber::COEFF_OF_FRICTION_OBJECT)
	);
	// for paths
	sf::Vector2f blockSize{ 60.0f , 45.0f };
	float mass = 4000000.0f;
	sf::Vector2f E = sf::Vector2f(GMNumber::COEFF_OF_RESTITUTION_PATH_X, GMNumber::COEFF_OF_RESTITUTION_PATH_Y);
	sf::Vector2f u = sf::Vector2f(GMNumber::COEFF_OF_FRICTION_PATH, GMNumber::COEFF_OF_FRICTION_PATH);

	gameObject.path.push_back(std::make_shared<Path>(2, CollisionId::HeavyPathId, mass, sf::Vector2f(blockSize.x, 504.0f), blockSize, nil, nil,
		E, u));
	gameObject.path.push_back(std::make_shared<Path>(3, CollisionId::HeavyPathId, mass, sf::Vector2f(660.0f, 504.0f), blockSize, nil, nil,
		E, u));
	for (int i = 0; i < 11; ++i) {
		gameObject.path.push_back(std::make_shared<Path>(4 + i, CollisionId::HeavyPathId, mass, sf::Vector2f( blockSize.x * (i+1) , 550.0f),
			blockSize, nil, nil, E, u));
	}
	

}

void PhysicLoop::RunPlysicLoop(){
	Load();
	auto& rect = gameObject.rectangle;
	while (window->isOpen()) {
		SFMLEvent();
		Update();
		window->clear();
		Draw();
		window->display();
	}
}

void PhysicLoop::SFMLEvent(){
	while (window->pollEvent(event)){
		if (event.type == sf::Event::Closed)
			window->close();
	}
}  

void PhysicLoop::Load(){
	gameObject.rectangle->Load();
	gameObject.grid.AddObject(gameObject.rectangle , false);
	for (int i = 0; i < gameObject.path.size(); ++i) {
		gameObject.path[i]->Load();
		gameObject.grid.AddObject(gameObject.path[i] , true);
	}
	gameObject.grid.ShowGirdObjectCound();
}

void PhysicLoop::Update() {
	this->DT = clock.restart().asSeconds();

	if (!GMNumber::USE_GRID) {
		gameObject.rectangle->Update(DT);
		gameObject.grid.MoveObject(gameObject.rectangle);
		for (int i = 0; i < gameObject.path.size(); ++i) {
			collisionAndFriction.ApplyFriction(gameObject.rectangle, gameObject.path[i], this->DT);
			collisionAndFriction.CollsionDetection(gameObject.rectangle, gameObject.path[i]);
		}

	}
	else {
		this->updateDrawResultFromGrid = gameObject.grid.FindUpdatableAndDrawableBlock(gameObject.rectangle);
		for (int i = 0; i < updateDrawResultFromGrid.dynamicResult.size(); ++i) {
			this->updateDrawResultFromGrid.dynamicResult[i]->Update(DT);
			gameObject.grid.MoveObject(this->updateDrawResultFromGrid.dynamicResult[i]);
		}
		collisionResultFromGrid = gameObject.grid.PotentialCollision(gameObject.rectangle);
		for (auto& obj : this->updateDrawResultFromGrid.dynamicResult) {
			this->collisionAndFriction.CollsionDetection(gameObject.rectangle, obj);
		}
		for (auto& obj : this->updateDrawResultFromGrid.staticResult) {
			this->collisionAndFriction.ApplyFriction(gameObject.rectangle, obj, this->DT);
			collisionAndFriction.CollsionDetection(gameObject.rectangle, obj);
		}
	}


	gameObject.rectangle->DisplayPositionAndVelocity();
}

void PhysicLoop::Draw(){
	if (!GMNumber::USE_GRID) {
		gameObject.rectangle->Draw(this->window);
		for (int i = 0; i < gameObject.path.size(); ++i) {
			gameObject.path[i]->Draw(this->window);
		}
	}
	else {
		for (auto& obj : this->updateDrawResultFromGrid.dynamicResult) {
			obj->Draw(window);
		}
		for (auto& obj : this->updateDrawResultFromGrid.staticResult) {
			obj->Draw(window);
		}
	}
	gameObject.grid.Draw(window);
}
