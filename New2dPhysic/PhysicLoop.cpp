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
	text(),
	DT(0.0f), entityIdCounter(0){
	this->window->setFramerateLimit(GMNumber::MAX_FRAME_RATE);

	// for player  this is a temp   sf::Vector2f(410.0f, 200.0f)
	auto size = GMNumber::BIG_BALL_SIZE;
	sf::Vector2f nil = sf::Vector2f(0.0f, 0.0f);
	gameObject.rectangle = std::make_shared<Rect>(++this->entityIdCounter, CollisionId::PlayerId, 60.0f,
		sf::Vector2f(590.0f, 300.0f), sf::Vector2f(size , size),
		sf::Vector2f(GMNumber::COEFF_OF_RESTITUTION_OBJECT_X, GMNumber::COEFF_OF_RESTITUTION_OBJECT_Y),
		sf::Vector2f(GMNumber::COEFF_OF_FRICTION_OBJECT, GMNumber::COEFF_OF_FRICTION_OBJECT)
	);


	// for paths
	sf::Vector2f blockSize{ 60.0f , 45.0f };
	float mass = 400000.0f;
	sf::Vector2f E = sf::Vector2f(GMNumber::COEFF_OF_RESTITUTION_PATH_X, GMNumber::COEFF_OF_RESTITUTION_PATH_Y);
	sf::Vector2f u = sf::Vector2f(GMNumber::COEFF_OF_FRICTION_PATH, GMNumber::COEFF_OF_FRICTION_PATH);


	gameObject.path.push_back(std::make_shared<Path>(++this->entityIdCounter, CollisionId::HeavyPathId, mass,
		sf::Vector2f(blockSize.x, 504.0f), blockSize,E, u));
	gameObject.path.push_back(std::make_shared<Path>(++this->entityIdCounter, CollisionId::HeavyPathId, mass,
		sf::Vector2f(660.0f, 504.0f), blockSize,E, u));

	for (int i = 0; i < 11; ++i) {
		gameObject.path.push_back(std::make_shared<Path>(++this->entityIdCounter, CollisionId::HeavyPathId, mass,
			sf::Vector2f(blockSize.x * (i + 1), 550.0f),blockSize,E, u));
	}

	//--------------------------
	gameObject.inflator = std::make_shared<Inflator>(++this->entityIdCounter, CollisionId::InflatorId, mass,
		sf::Vector2f(500.0f, 504.0f), sf::Vector2f(25.0f, 50.0f),E, u);

	gameObject.deflator = std::make_shared<Deflator>(++this->entityIdCounter, CollisionId::DeflatorId, mass,
		sf::Vector2f(280.0f, 504.0f), sf::Vector2f(25.0f, 50.0f), E, u);

	gameObject.bouncyPath = std::make_shared<BouncyPath>(++this->entityIdCounter, CollisionId::HeavyPathId, mass,
		sf::Vector2f(350.0f, 540.0f), sf::Vector2f(70.0f, 10.0f),sf::Vector2f(0.4f,2.1f), u);

	for (int i = 0; i < 5; ++i) {
		gameObject.collectable.push_back(std::make_shared<Collectable>(++this->entityIdCounter,
			CollisionId::CollectableId, 1.0f, 10.0f , sf::Vector2f(300.0f + 50.0f * i, 400.0f),
			sf::Vector2f(20.0f, 20.0f)));
	}
	
	this->text.setFont(gameObject.resource.GetFont());
	this->text.setPosition({ 250.0f,10.0f });
	this->text.setCharacterSize(15);
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
	gameObject.deflator->Load();	
	gameObject.inflator->Load();	
	gameObject.bouncyPath->Load();
	

	gameObject.grid.AddObject(gameObject.rectangle , false);
	for (int i = 0; i < gameObject.path.size(); ++i) {
		gameObject.path[i]->Load();
		gameObject.grid.AddObject(gameObject.path[i] , true);
	}
	for (int i = 0; i < gameObject.collectable.size(); ++i) {
		gameObject.collectable[i]->Load();
		gameObject.grid.AddObject(gameObject.collectable[i], true);
	}

	gameObject.grid.AddObject(gameObject.inflator, true);
	gameObject.grid.AddObject(gameObject.deflator, true);
	gameObject.grid.AddObject(gameObject.bouncyPath, true);
}

void PhysicLoop::Update() {
	this->DT = clock.restart().asSeconds();
	this->updateDrawResultFromGrid = gameObject.grid.FindUpdatableAndDrawableBlock(gameObject.rectangle);
	collisionResultFromGrid = gameObject.grid.PotentialCollision(gameObject.rectangle);


	for (int i = 0; i < updateDrawResultFromGrid.dynamicResult.size(); ++i) {
		this->updateDrawResultFromGrid.dynamicResult[i]->Update(DT);
	}


	for (auto& obj : this->updateDrawResultFromGrid.staticResult) {
		this->collisionAndFriction.ApplyFriction(gameObject.rectangle, obj, this->DT);
		collisionAndFriction.CollsionDetection(gameObject.rectangle, obj);
	}

	for (auto& obj : this->collisionResultFromGrid.dynamicResult) {
		this->collisionAndFriction.CollsionDetection(gameObject.rectangle, obj);
	}

	gameObject.rectangle->ReCentered();

	for (auto& obj : updateDrawResultFromGrid.dynamicResult) {
		gameObject.grid.MoveObject(obj);
	}

	DisplayStats();
	gameObject.rectangle->DisplayPositionAndVelocity();
	DeleteUnwanted();
}

void PhysicLoop::Draw() {
	gameObject.grid.Draw(window);
	for (auto& obj : this->updateDrawResultFromGrid.staticResult) {
		obj->Draw(window);
	}
	for (auto& obj : this->updateDrawResultFromGrid.dynamicResult) {
		obj->Draw(window);
	}
	window->draw(text);
}

void PhysicLoop::DisplayStats(){
	int maxsize = gameObject.path.size() + gameObject.collectable.size() +2 + 3;
	this->text.setString(
		"Objects Updated & Rendered: "
		+ std::to_string((int)(updateDrawResultFromGrid.dynamicResult.size()
			+ updateDrawResultFromGrid.staticResult.size()))
		+ " / " + std::to_string(maxsize) + "\n" +
		"Objects for Collision Checking: "
		+ std::to_string((int)(collisionResultFromGrid.dynamicResult.size()
			+ collisionResultFromGrid.staticResult.size()))
		+ " / " + std::to_string(maxsize) +
		"          Points = " + std::to_string(gameObject.rectangle->GetPoints())
	);
}

void PhysicLoop::DeleteUnwanted() {
	auto& collectables = gameObject.collectable;
	for (auto it = collectables.begin(); it != collectables.end(); ) {
		if ((*it)->GetCanBeDeleted()) {
			gameObject.grid.RemoveObject(*it, true);
			it = collectables.erase(it);
		}
		else{++it;}
	}
}


