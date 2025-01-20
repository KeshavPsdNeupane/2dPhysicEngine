#include "Level.h"
#include "../States/MenuState/PauseState.h"
#include "../States/MenuState/GameOver.h"

Level::Level(std::shared_ptr<StateData> state) :
    WorldSuperClass(state), contactMechanic(*this),
    isPaused(false), event(), worldSize(),
    updateDrawResultFromGrid(),
    collisionResultFromGrid(),
    text(), DT(0.0f),
    entityIdCounter(0) {
    TileResource tile;
    std::string path = "Asset/Maps/TestMap3.txt";
    TotalTileData& data = tile.ListTheEntity(path);
    this->worldSize = sf::Vector2f((float)data.worldWidth, (float)data.worldHeight);
    grid.InitializeGameGrid(data.worldWidth, data.worldHeight, data.tileWidth, data.tileHeight);
    CreatePath(data);
    CreateInflator(data);
    CreateDeflator(data);
    CreateBouncyPath(data);
    CreateCollectable(data);
    CreateStaticEnemy(data);
    CreateCheckPoint(data);
    sf::Vector2f positionForPlayer = this->checkPoint[0]->GetPosition();
    auto size = GMNumber::SMALL_BALL_SIZE;
    this->rectangle = std::make_shared<Rect>(++this->entityIdCounter, CollisionId::PlayerId, 60.0f,
        positionForPlayer, sf::Vector2f(size, size),
        GMNumber::COEFF_OF_RESTITUTION_OBJECT,
        GMNumber::COEFF_OF_FRICTION_OBJECT
    );

    this->invisibleEnemy = std::make_shared<InvisibleEnemy>(++this->entityIdCounter,
        CollisionId::StaticEnemyId, 400000.0f, sf::Vector2f(320.0f, 250.0f),sf::Vector2f(64.0f,64.0f));

	this->staticEnemyS = std::make_shared<StaticEnemyS>(++this->entityIdCounter,
		CollisionId::StaticEnemyIdS, 400000.0f,43,sf::Vector2f(350.0f, 350.0f), sf::Vector2f(64.0f, 64.0f),
		GMNumber::COEFF_OF_RESTITUTION_PATH, GMNumber::COEFF_OF_FRICTION_PATH);

    this->dynamicEnemy = std::make_shared<DynamicEnemy>(++this->entityIdCounter,
        CollisionId::StaticEnemyId, 400000.f,43, sf::Vector2f(150.0f, 150.0f),
        sf::Vector2f(64.0f, 64.0f), sf::Vector2f(0.0f, 64.0f));



    this->checkPointPosition = positionForPlayer;
    this->text.setFont(this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT));
    this->text.setPosition({ 250.0f,10.0f });
    this->text.setCharacterSize(15);
    this->text2.setFont(this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT));
    this->text2.setPosition({ 550.0f,10.0f });
    this->text2.setCharacterSize(30);

}

Level::~Level() {}



void Level::Load() {
    this->rectangle->Load(this->stateData->resourceManager);
    this->grid.AddObject(this->rectangle, false);

    for (unsigned int i = 0; i < this->path.size(); ++i) {
        this->path[i]->Load(this->stateData->resourceManager);
        this->grid.AddObject(this->path[i], true);
    }
	for (unsigned int i = 0; i < inflator.size(); ++i) {
		this->inflator[i]->Load(this->stateData->resourceManager);
		this->grid.AddObject(this->inflator[i], true);
	}
    for (unsigned int i = 0; i < deflator.size(); ++i) {
        this->deflator[i]->Load(this->stateData->resourceManager);
        this->grid.AddObject(this->deflator[i], true);
    }
	for (unsigned int i = 0; i < this->bouncyPath.size(); ++i) {
		this->bouncyPath[i]->Load(this->stateData->resourceManager);
		this->grid.AddObject(this->bouncyPath[i], true);
	}
    //REMEMBER IF U MAKING COLLECTABLE STATIC ENTITY THEM
	// MAKE SURE TO UPDATE THE DELETEUNWANTED FUNCTION BOOL TO BE TRUE
	//OTHERWISE IT WILL NOT DELETE THE OBJECT
    for (unsigned int i = 0; i < this->collectable.size(); ++i) {
        this->collectable[i]->Load(this->stateData->resourceManager);
        this->grid.AddObject(this->collectable[i],false);
    }
    for (unsigned int i = 0; i < this->staticEnemy.size(); ++i) {
        this->staticEnemy[i]->Load(this->stateData->resourceManager);
        this->grid.AddObject(this->staticEnemy[i], true);
    }
    for (unsigned int i = 0; i < this->checkPoint.size(); ++i) {
        this->checkPoint[i]->Load(this->stateData->resourceManager);
        this->grid.AddObject(this->checkPoint[i], true);
    }


	this->invisibleEnemy->Load(this->stateData->resourceManager);
	this->grid.AddObject(this->invisibleEnemy, true);
    this->staticEnemyS->Load(this->stateData->resourceManager);
    this->grid.AddObject(this->staticEnemyS, true);

    this->dynamicEnemy->Load(this->stateData->resourceManager);
    this->grid.AddObject(this->dynamicEnemy, false);

}


void Level::ProcessInput() {
    while (this->stateData->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            this->stateData->window->close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                this->stateData->stateManager->AddState(
                    std::make_unique<PauseState>(this->stateData), false);
            }
            if (event.key.code == sf::Keyboard::Period) {
                IncrementLife();
            }
            else if (event.key.code == sf::Keyboard::Comma) {
                DecrementLife();
            }
            else if (event.key.code == sf::Keyboard::P) {
                this->rectangle->SetPosition(this->checkPointPosition);
                this->rectangle->SetVelocity(sf::Vector2f(0.0f, 0.0f));
                this->grid.MoveObject(this->rectangle);
            }

        }
    }
}

void Level::Update(const float& dt) {
    if (!this->isPaused) {
        this->DT = dt;
        this->updateDrawResultFromGrid =
            this->grid.FindUpdatableAndDrawableBlock(this->rectangle);
        collisionResultFromGrid = this->grid.PotentialCollision(this->rectangle);

        for (auto obj: updateDrawResultFromGrid.dynamicResult) {
            obj->Update(this->DT);
        }

        for (auto& obj : this->updateDrawResultFromGrid.staticResult) {
            this->contactMechanic.ApplyFriction(this->rectangle, obj, this->DT);
            this->contactMechanic.CollsionDetection(this->rectangle, obj);
        }

        for (auto& obj : this->collisionResultFromGrid.dynamicResult) {
		    this->contactMechanic.CollsionDetection(this->rectangle, obj);
        }



        for (auto& obj : updateDrawResultFromGrid.dynamicResult) {
            this->grid.MoveObject(obj);
        }

        DisplayStats();
        this->rectangle->DisplayPositionAndVelocity();
        DeleteUnwanted();
        EndLevel();
    }
}


void Level::Draw() {
    if (!isPaused) {
        auto& window = this->stateData->window;
        window->clear();
        CreateViewBasedOnPlayer(window);
        window->setView(this->worldView);

        for (auto& obj : this->updateDrawResultFromGrid.staticResult) {
            obj->Draw(window);
        }
        for (auto& obj : this->updateDrawResultFromGrid.dynamicResult) {
            obj->Draw(window);
        }

        if (GMNumber::IS_PADDING) {
            this->grid.Draw(window);
        }
        DrawDefaulView(window);
        window->display();
    }
}

void Level::CreateViewBasedOnPlayer(std::shared_ptr<sf::RenderWindow> window) {
    const float Width = (float)window->getSize().x;
    const float Height = (float)window->getSize().y;
    const float halfWidth = Width * 0.5f;
    const float halfHeight = Height * 0.5f;
    sf::Vector2f playerPosition = this->rectangle->GetPosition();
    this->worldView.setSize(Width, Height);
    float clampedX = VectorOperation::Clamp(playerPosition.x, halfWidth, this->worldSize.x- halfWidth);
    float clampedY = VectorOperation::Clamp(playerPosition.y, halfHeight, this->worldSize.y - halfHeight);
    this->worldView.setCenter({ clampedX, clampedY });

}

void Level::DrawDefaulView(std::shared_ptr<sf::RenderWindow>window) {
    window->setView(window->getDefaultView());

    window->draw(text);
    window->draw(text2);
    this->rectangle->DrawStats(window);
}

void Level::Pause() { this->isPaused = true; }

void Level::Start() { this->isPaused = false; }

void Level::DisplayStats() {
    int maxsize = (int)this->path.size() + (int)this->collectable.size() + 3 + 1;
    // 3 for the object bouncy pad, inflator, deflator , 1 for player
    //this->text.setString(
    //    "Objects Updated & Rendered: "
    //    + std::to_string((int)(updateDrawResultFromGrid.dynamicResult.size()
    //        + updateDrawResultFromGrid.staticResult.size()))
    //    + " / " + std::to_string(maxsize) + "\n" +
    //    "Objects for Collision Checking: "
    //    + std::to_string((int)(collisionResultFromGrid.dynamicResult.size()
    //        + collisionResultFromGrid.staticResult.size()))
    //    + " / " + std::to_string(maxsize - 1)  // -1 since player will not collide with itself
    //);
    this->text2.setString("Points = " + std::to_string(this->points) +
        "\nLife = " + std::to_string(this->life));
}

void Level::DeleteUnwanted() {
    auto& collectables = this->collectable;
    for (auto it = collectables.begin(); it != collectables.end(); ) {
        if ((*it)->GetCanBeDeleted()) {
            this->grid.RemoveObject(*it, false);
            it = collectables.erase(it);
        }
        else { ++it; }
    }
}

void Level::CreatePath(TotalTileData& data){
    sf::Vector2f nil = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f blockSize{ 64.0f , 64.0f };
    float mass = 400000.0f;
    sf::Vector2f E = GMNumber::COEFF_OF_RESTITUTION_PATH;
    float u = GMNumber::COEFF_OF_FRICTION_PATH;

	const auto& pathData = data.loadEntity[EntityId::path];
    for ( unsigned int i = 0; i < pathData.size(); ++i) {
        this->path.push_back(std::make_shared<Path>(++this->entityIdCounter,
			CollisionId::HeavyPathId, mass, pathData[i].textureIndex,
            sf::Vector2f((float)pathData[i].pixelX, (float)pathData[i].pixelY),
            blockSize, E, u));
    }

}

void Level::CreateInflator(TotalTileData& data){
	sf::Vector2f nil = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f blockSize{ 64.0f , 64.0f };
	float mass = 400000.0f;
	sf::Vector2f E = GMNumber::COEFF_OF_RESTITUTION_PATH;
	float u = GMNumber::COEFF_OF_FRICTION_PATH;
	const auto& inflatorData = data.loadEntity[EntityId::inflator];
	for (unsigned int i = 0; i < inflatorData.size(); ++i) {
		this->inflator.push_back(std::make_shared<Inflator>(++this->entityIdCounter, 
			CollisionId::InflatorId, mass, inflatorData[i].textureIndex,
			sf::Vector2f((float)inflatorData[i].pixelX, (float)inflatorData[i].pixelY),
            blockSize, E, u));
	}
}

void Level::CreateDeflator(TotalTileData& data){
	sf::Vector2f nil = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f blockSize{ 64.0f , 64.0f };
	float mass = 400000.0f;
	sf::Vector2f E = GMNumber::COEFF_OF_RESTITUTION_PATH;
	float u = GMNumber::COEFF_OF_FRICTION_PATH;
	const auto& deflatorData = data.loadEntity[EntityId::deflator];
	for ( unsigned int i = 0; i < deflatorData.size(); ++i) {
		this->deflator.push_back(std::make_shared<Deflator>(++this->entityIdCounter, 
			CollisionId::DeflatorId, mass, deflatorData[i].textureIndex,
			sf::Vector2f((float)deflatorData[i].pixelX, (float)deflatorData[i].pixelY),
            blockSize, E, u));
	}
}

void Level::CreateBouncyPath(TotalTileData& data){
	sf::Vector2f blockSize{ 64.0f , 64.0f };
	float mass = 400000.0f;
	sf::Vector2f E = GMNumber::COEFF_OF_RESTITUTION_PATH;
	float u = GMNumber::COEFF_OF_FRICTION_PATH;
	const auto& bouncyPathData = data.loadEntity[EntityId::bouncypad];
	for (unsigned int i = 0; i < bouncyPathData.size(); ++i) {
		this->bouncyPath.push_back(std::make_shared<BouncyPath>(++this->entityIdCounter, 
			CollisionId::HeavyPathId, mass, bouncyPathData[i].textureIndex,
			sf::Vector2f((float)bouncyPathData[i].pixelX, (float)bouncyPathData[i].pixelY), blockSize,
            sf::Vector2f(0.4f, 2.1f), u));
	}
}

void Level::CreateCollectable(TotalTileData& data){
	sf::Vector2f blockSize{ 64.0f , 64.0f };
	float mass = 400000.0f;
	sf::Vector2f E = GMNumber::COEFF_OF_RESTITUTION_PATH;
	float u = GMNumber::COEFF_OF_FRICTION_PATH;
	const auto& collectableData = data.loadEntity[EntityId::collectable];
	for (unsigned int i = 0; i < collectableData.size(); ++i) {
		this->collectable.push_back(std::make_shared<Collectable>(++this->entityIdCounter,
			CollisionId::CollectableId, 1.0f, 10, collectableData[i].textureIndex,
            sf::Vector2f((float)collectableData[i].pixelX, (float)collectableData[i].pixelY),
			sf::Vector2f(48.0f, 48.0f)));
	}
}

void Level::CreateStaticEnemy(TotalTileData& data){
	sf::Vector2f blockSize{ 64.0f , 64.0f };
	float mass = 400000.0f;
	sf::Vector2f E = GMNumber::COEFF_OF_RESTITUTION_PATH;
	float u = GMNumber::COEFF_OF_FRICTION_PATH;
	const auto& staticEnemyData = data.loadEntity[EntityId::staticEnemy];
	for (unsigned  int i = 0; i < staticEnemyData.size(); ++i) {
		this->staticEnemy.push_back(std::make_shared<StaticEnemy>(++this->entityIdCounter, 
			CollisionId::StaticEnemyId, mass, staticEnemyData[i].textureIndex,
			sf::Vector2f((float)staticEnemyData[i].pixelX,
                (float)staticEnemyData[i].pixelY), blockSize, E, u));
	}
}

void Level::CreateCheckPoint(TotalTileData& data){
	sf::Vector2f blockSize{ 64.0f , 64.0f };
	float mass = 400000.0f;
	sf::Vector2f E = GMNumber::COEFF_OF_RESTITUTION_PATH;
	float u = GMNumber::COEFF_OF_FRICTION_PATH;
	const auto& checkPointData = data.loadEntity[EntityId::checkPoint];
	for ( unsigned int i = 0; i < checkPointData.size(); ++i) {
		this->checkPoint.push_back(std::make_shared<CheckPoint>(++this->entityIdCounter, 
			CollisionId::CheckPointId, checkPointData[i].textureIndex,  
			sf::Vector2f((float)checkPointData[i].pixelX, (float)checkPointData[i].pixelY),
            sf::Vector2f(50.0f, 50.0f)));
	}
}

void Level::EndLevel(){
    if (this->life < 1) {
        this->stateData->stateManager->AddState(
            std::make_unique<GameOver>(this->stateData));
        return;
    }
}

