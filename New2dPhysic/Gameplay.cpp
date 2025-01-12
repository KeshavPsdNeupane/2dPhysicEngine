#include "Gameplay.h"
#include"States/MenuState/PauseState.h"

Gameplay::Gameplay(std::shared_ptr<StateData> state):
	isPaused(false),
	stateData(state),
	event(),
	updateDrawResultFromGrid(),
	collisionResultFromGrid(),
	text(), 
	DT(0.0f), entityIdCounter(0){	
	// for player  this is a temp   sf::Vector2f(410.0f, 200.0f)
	auto size = GMNumber::SMALL_BALL_SIZE;
	sf::Vector2f nil = sf::Vector2f(0.0f, 0.0f);
	this->rectangle = std::make_shared<Rect>(++this->entityIdCounter, CollisionId::PlayerId, 60.0f,
		sf::Vector2f(160.0f, 300.0f), sf::Vector2f(size , size),
		GMNumber::COEFF_OF_RESTITUTION_OBJECT,
		sf::Vector2f(GMNumber::COEFF_OF_FRICTION_OBJECT, GMNumber::COEFF_OF_FRICTION_OBJECT),
		this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT)
	);


	// for paths
	sf::Vector2f blockSize{ 60.0f , 45.0f };
	float mass = 400000.0f;
	//sf::Vector2f E = sf::Vector2f(GMNumber::COEFF_OF_RESTITUTION_PATH_X, GMNumber::COEFF_OF_RESTITUTION_PATH_Y);
	sf::Vector2f E = GMNumber::COEFF_OF_RESTITUTION_PATH;
	sf::Vector2f u = sf::Vector2f(GMNumber::COEFF_OF_FRICTION_PATH, GMNumber::COEFF_OF_FRICTION_PATH);


	this->path.push_back(std::make_shared<Path>(++this->entityIdCounter, CollisionId::HeavyPathId, mass,
		sf::Vector2f(blockSize.x, 505.0f), blockSize,E, u));
	this->path.push_back(std::make_shared<Path>(++this->entityIdCounter, CollisionId::HeavyPathId, mass,
		sf::Vector2f(660.0f, 505.0f), blockSize,E, u));

	for (int i = 0; i < 11; ++i) {
		this->path.push_back(std::make_shared<Path>(++this->entityIdCounter, CollisionId::HeavyPathId, mass,
			sf::Vector2f(blockSize.x * (i + 1), 550.0f),blockSize,E, u));
	}

	//--------------------------
	this->inflator = std::make_shared<Inflator>(++this->entityIdCounter, CollisionId::InflatorId, mass,
		sf::Vector2f(120.0f, 504.0f), sf::Vector2f(25.0f, 50.0f),E, u);

	this->deflator = std::make_shared<Deflator>(++this->entityIdCounter, CollisionId::DeflatorId, mass,
		sf::Vector2f(250.0f, 504.0f), sf::Vector2f(25.0f, 50.0f), E, u);

	this->bouncyPath = std::make_shared<BouncyPath>(++this->entityIdCounter, CollisionId::HeavyPathId, mass,
		sf::Vector2f(350.0f, 540.0f), sf::Vector2f(70.0f, 10.0f),sf::Vector2f(0.4f,2.1f), u);

	for (int i = 0; i < 5; ++i) {
		this->collectable.push_back(std::make_shared<Collectable>(++this->entityIdCounter,
			CollisionId::CollectableId, 1.0f, 10 , sf::Vector2f(400.0f + 50.0f * i, 400.0f),
			sf::Vector2f(20.0f, 20.0f)));
	}
	
	this->text.setFont(this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT));
	this->text.setPosition({ 250.0f,10.0f });
	this->text.setCharacterSize(15);
	this->text2.setFont(this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT));
	this->text2.setPosition({ 550.0f,10.0f });
	this->text2.setCharacterSize(30);
}

Gameplay::~Gameplay(){}



void Gameplay::Load(){
	this->rectangle->Load(this->stateData->resourceManager);
	this->grid.AddObject(this->rectangle, false);


	for (int i = 0; i < this->path.size(); ++i) {
		this->path[i]->Load(this->stateData->resourceManager);
		this->grid.AddObject(this->path[i] , true);
	}
	for (int i = 0; i < this->collectable.size(); ++i) {
		this->collectable[i]->Load(this->stateData->resourceManager);
		this->grid.AddObject(this->collectable[i], true);
	}

	this->inflator->Load(this->stateData->resourceManager);
	this->grid.AddObject(this->inflator, true);

	this->deflator->Load(this->stateData->resourceManager);
	this->grid.AddObject(this->deflator, true);

	this->bouncyPath->Load(this->stateData->resourceManager);
	this->grid.AddObject(this->bouncyPath, true);
}


void Gameplay::ProcessInput(){
	while (this->stateData->window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			this->stateData->window->close();
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				this->stateData->stateManager->AddState(
					std::make_unique<PauseState>(this->stateData), false);
			}
		}
	}
}

void Gameplay::Update(const float& dt){
	if (!this->isPaused) {
		this->DT = dt;
		this->updateDrawResultFromGrid =
			this->grid.FindUpdatableAndDrawableBlock(this->rectangle);
		collisionResultFromGrid = this->grid.PotentialCollision(this->rectangle);
		for (int i = 0; i < updateDrawResultFromGrid.dynamicResult.size(); ++i) {
			this->updateDrawResultFromGrid.dynamicResult[i]->Update(DT);
		}


		for (auto& obj : this->updateDrawResultFromGrid.staticResult) {
			this->stateData->contactMechanic->ApplyFriction(this->rectangle, obj, this->DT);
			this->stateData->contactMechanic->CollsionDetection(this->rectangle, obj);
		}

		for (auto& obj : this->collisionResultFromGrid.dynamicResult) {
			this->stateData->contactMechanic->CollsionDetection(this->rectangle, obj);
		}

		this->rectangle->ReCentered();

		for (auto& obj : updateDrawResultFromGrid.dynamicResult) {
			this->grid.MoveObject(obj);
		}

		DisplayStats();
		this->rectangle->DisplayPositionAndVelocity();
		DeleteUnwanted();
	}
}


void Gameplay::Draw() {
	if (!isPaused) {
		auto& window = this->stateData->window;
		window->clear();

		if(GMNumber::IS_PADDING){ this->grid.Draw(window); }

		for (auto& obj : this->updateDrawResultFromGrid.staticResult) {
			obj->Draw(window);
		}
		for (auto& obj : this->updateDrawResultFromGrid.dynamicResult) {
			obj->Draw(window);
		}
		window->draw(text);
		window->draw(text2);


		window->display();
}

}

void Gameplay::Pause(){this->isPaused = true;}

void Gameplay::Start(){this->isPaused = false;}

void Gameplay::DisplayStats(){
	int maxsize = (int)this->path.size() + (int)this->collectable.size() + 3 +1;
	// 3 for the object bouncy pad, inflator, deflator , 1 for player
	this->text.setString(
		"Objects Updated & Rendered: "
		+ std::to_string((int)(updateDrawResultFromGrid.dynamicResult.size()
			+ updateDrawResultFromGrid.staticResult.size()))
		+ " / " + std::to_string(maxsize) + "\n" +
		"Objects for Collision Checking: "
		+ std::to_string((int)(collisionResultFromGrid.dynamicResult.size()
			+ collisionResultFromGrid.staticResult.size()))
		+ " / " + std::to_string(maxsize - 1)  // -1 since player will not collide with itself
	);
	this->text2.setString("Points = " + std::to_string(this->rectangle->GetPoints()));
}

void Gameplay::DeleteUnwanted() {
	auto& collectables = this->collectable;
	for (auto it = collectables.begin(); it != collectables.end(); ) {
		if ((*it)->GetCanBeDeleted()) {
			this->grid.RemoveObject(*it, true);
			it = collectables.erase(it);
		}
		else{++it;}
	}
}


