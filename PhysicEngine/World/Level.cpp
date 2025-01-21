#include "Level.h"
#include "../States/MenuState/PauseState.h"
#include "../States/MenuState/GameOver.h"

Level::Level(std::shared_ptr<StateData> state) :
    WorldSuperClass(state), contactMechanic(*this),
    isPaused(false), event(),
    updateDrawResultFromGrid(),
    collisionResultFromGrid(),
    text(), DT(0.0f),
    entityIdCounter(0) {

    TileResource tile;
    std::string path = "Asset/Maps/Level1Gameplay.txt";
    TotalTileData& data = tile.ListTheEntity(path);
    this->worldSize = sf::Vector2f((float)data.worldWidth, (float)data.worldHeight);
	this->tileSize = sf::Vector2f((float)data.tileWidth, (float)data.tileHeight);

    grid.InitializeGameGrid(data.worldWidth, data.worldHeight, data.tileWidth, data.tileHeight);

    this->totalCoinCount.x =  data.loadEntity[EntityId::collectable].size();
	this->totalCoinCount.y = (int)(0.85f * this->totalCoinCount.x  + 1);

    float mass = 400000.0f;
    sf::Vector2f E = GMNumber::COEFF_OF_RESTITUTION_PATH;
    float u = GMNumber::COEFF_OF_FRICTION_PATH;
   
    CreatePath(data, mass, E, u);
    CreateInflator(data, mass, E, u);
    CreateDeflator(data, mass, E, u);
    CreateBouncyPath(data, mass, E, u);
    CreateCollectable(data);
    CreateStaticEnemy(data, mass, E, u);
	CreateStaticSEnemy(data, mass, E, u);
    CreateCheckPoint(data);
	CreateDynamicEnemy(data);   
	CreateInvisibleEnemy(data);
	CreateEndGameMarker(data);

    const auto&temep = data.loadEntity[EntityId::player][0];

    sf::Vector2f positionForPlayer((float)temep.pixelX, (float)temep.pixelY);
    auto size = GMNumber::SMALL_BALL_SIZE;
    this->rectangle = std::make_shared<Rect>(++this->entityIdCounter, CollisionId::PlayerId, 60.0f,
        positionForPlayer, sf::Vector2f(size, size),
        GMNumber::COEFF_OF_RESTITUTION_OBJECT,
        GMNumber::COEFF_OF_FRICTION_OBJECT
    );

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
    for (unsigned int i = 0; i < this->staticEnemyS.size(); ++i) {
        this->staticEnemyS[i]->Load(this->stateData->resourceManager);
        this->grid.AddObject(this->staticEnemyS[i], true);
    }
	for (unsigned int i = 0; i < this->dynamicEnemy.size(); ++i) {
		this->dynamicEnemy[i]->Load(this->stateData->resourceManager);
		this->grid.AddObject(this->dynamicEnemy[i], false);
	}
	for (unsigned int i = 0; i < this->invisibleEnemy.size(); ++i) {
		this->invisibleEnemy[i]->Load(this->stateData->resourceManager);
		this->grid.AddObject(this->invisibleEnemy[i], true);
	}
	for (unsigned int i = 0; i < this->inflator.size(); ++i) {
		this->inflator[i]->Load(this->stateData->resourceManager);
		this->grid.AddObject(this->inflator[i], true);
	}

    for (unsigned int i = 0; i < this->checkPoint.size(); ++i) {
        this->checkPoint[i]->Load(this->stateData->resourceManager);
        this->grid.AddObject(this->checkPoint[i], true);
    }

    this->levelEndMarker->Load(this->stateData->resourceManager);
	this->grid.AddObject(this->levelEndMarker, true);

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
        this->updateDrawResultFromGrid = this->grid.FindUpdatableAndDrawableBlock(this->rectangle);
        this->collisionResultFromGrid = this->grid.PotentialCollision(this->rectangle);

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
        "\nLife = " + std::to_string(this->life) + 
        "\nCoinCount =" + std::to_string(this->totalCoinCount.x));
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

void Level::CreatePath(const TotalTileData& data, const float& mass,
    const sf::Vector2f& cowffOfRest, const float& coeffOfFriection){
	const auto& pathData = data.loadEntity[EntityId::path];
	this->path.reserve(pathData.size());   
    for ( unsigned int i = 0; i < pathData.size(); ++i) {
        this->path.push_back(std::make_shared<Path>(++this->entityIdCounter,
			CollisionId::HeavyPathId, mass, pathData[i].textureIndex,
            sf::Vector2f((float)pathData[i].pixelX, (float)pathData[i].pixelY),
            this->tileSize, cowffOfRest, coeffOfFriection));
    }

}

void Level::CreateInflator(const TotalTileData& data, const float& mass,
    const sf::Vector2f& cowffOfRest, const float& coeffOfFriection){
	const auto& inflatorData = data.loadEntity[EntityId::inflator];
	this->inflator.reserve(inflatorData.size());
	for (unsigned int i = 0; i < inflatorData.size(); ++i) {
		this->inflator.push_back(std::make_shared<Inflator>(++this->entityIdCounter, 
			CollisionId::InflatorId, mass, inflatorData[i].textureIndex,
			sf::Vector2f((float)inflatorData[i].pixelX, (float)inflatorData[i].pixelY),
            this->tileSize, cowffOfRest, coeffOfFriection));
	}
}

void Level::CreateDeflator(const TotalTileData& data, const float& mass,
    const sf::Vector2f& cowffOfRest, const float& coeffOfFriection){
	const auto& deflatorData = data.loadEntity[EntityId::deflator];
	this->deflator.reserve(deflatorData.size());
	for ( unsigned int i = 0; i < deflatorData.size(); ++i) {
		this->deflator.push_back(std::make_shared<Deflator>(++this->entityIdCounter, 
			CollisionId::DeflatorId, mass, deflatorData[i].textureIndex,
			sf::Vector2f((float)deflatorData[i].pixelX, (float)deflatorData[i].pixelY),
            this->tileSize, cowffOfRest, coeffOfFriection));
	}
}

void Level::CreateBouncyPath(const TotalTileData& data, const float& mass, 
    const sf::Vector2f& cowffOfRest, const float& coeffOfFriection){
    	const auto& bouncyPathData = data.loadEntity[EntityId::bouncypad];
		this->bouncyPath.reserve(bouncyPathData.size());
        for (unsigned int i = 0; i < bouncyPathData.size(); ++i) {
            this->bouncyPath.push_back(std::make_shared<BouncyPath>(++this->entityIdCounter,
                CollisionId::HeavyPathId, mass, bouncyPathData[i].textureIndex,
                sf::Vector2f((float)bouncyPathData[i].pixelX, (float)bouncyPathData[i].pixelY),
                this->tileSize, sf::Vector2f(cowffOfRest.x, 4.5f), coeffOfFriection));
        }
}


void Level::CreateCollectable(const TotalTileData& data){
	const auto& collectableData = data.loadEntity[EntityId::collectable];
	this->collectable.reserve(collectableData.size());
	for (unsigned int i = 0; i < collectableData.size(); ++i) {
		this->collectable.push_back(std::make_shared<Collectable>(++this->entityIdCounter,
			CollisionId::CollectableId, 1.0f, 10, collectableData[i].textureIndex,
            sf::Vector2f((float)collectableData[i].pixelX, (float)collectableData[i].pixelY),
			this->tileSize));
	}
}

void Level::CreateStaticEnemy(const TotalTileData& data, const float& mass,
    const sf::Vector2f& cowffOfRest, const float& coeffOfFriection){
	const auto& staticEnemyData = data.loadEntity[EntityId::staticEnemy];
	this->staticEnemy.reserve(staticEnemyData.size());
	for (unsigned  int i = 0; i < staticEnemyData.size(); ++i) {
		this->staticEnemy.push_back(std::make_shared<StaticEnemy>(++this->entityIdCounter, 
			CollisionId::StaticEnemyId, mass, staticEnemyData[i].textureIndex,
			sf::Vector2f((float)staticEnemyData[i].pixelX, (float)staticEnemyData[i].pixelY),
            this->tileSize, cowffOfRest, coeffOfFriection));
	}
}

void Level::CreateStaticSEnemy(const TotalTileData& data, const float& mass,
    const sf::Vector2f& cowffOfRest, const float& coeffOfFriection){
	const auto& staticEnemySData = data.loadEntity[EntityId::staticEnemyS];
	this->staticEnemyS.reserve(staticEnemySData.size());
	for (unsigned int i = 0; i < staticEnemySData.size(); ++i) {
		this->staticEnemyS.push_back(std::make_shared<StaticEnemyS>(++this->entityIdCounter,
			CollisionId::StaticEnemyIdS, mass, staticEnemySData[i].textureIndex,
            sf::Vector2f((float)staticEnemySData[i].pixelX,(float)staticEnemySData[i].pixelY),
            this->tileSize, cowffOfRest, coeffOfFriection));
	}
}

void Level::CreateDynamicEnemy(const TotalTileData& data){
	const auto& dynamicEnemyData = data.loadEntity[EntityId::dynamicEnemy];
	this->dynamicEnemy.reserve(dynamicEnemyData.size());
	for (unsigned int i = 0; i < dynamicEnemyData.size(); ++i) {
		this->dynamicEnemy.push_back(std::make_shared<DynamicEnemy>(++this->entityIdCounter,
			CollisionId::InvisibleEnemyId, 10.0f, dynamicEnemyData[i].textureIndex,
            sf::Vector2f((float)dynamicEnemyData[i].pixelX,
				(float)dynamicEnemyData[i].pixelY), this->tileSize, sf::Vector2f(0.0f, 64.0f)));
	}
}

void Level::CreateInvisibleEnemy(const TotalTileData& data){
	const auto& invisibleEnemyData = data.loadEntity[EntityId::invisibleEnemy];
	this->invisibleEnemy.reserve(invisibleEnemyData.size());
	for (unsigned int i = 0; i < invisibleEnemyData.size(); ++i) {
		this->invisibleEnemy.push_back(std::make_shared<InvisibleEnemy>(++this->entityIdCounter,
			CollisionId::InvisibleEnemyId, sf::Vector2f((float)invisibleEnemyData[i].pixelX,
				(float)invisibleEnemyData[i].pixelY), this->tileSize));
	}
}

void Level::CreateCheckPoint(const TotalTileData& data){
	const auto& checkPointData = data.loadEntity[EntityId::checkPoint];
	this->checkPoint.reserve(checkPointData.size());
	for ( unsigned int i = 0; i < checkPointData.size(); ++i) {
		this->checkPoint.push_back(std::make_shared<CheckPoint>(++this->entityIdCounter, 
			CollisionId::CheckPointId, checkPointData[i].textureIndex,  
			sf::Vector2f((float)checkPointData[i].pixelX, (float)checkPointData[i].pixelY ),
            this->tileSize));
	}
}

void Level::CreateEndGameMarker(const TotalTileData& data){
    const auto& endData = data.loadEntity[EntityId::EndGameMarker][0];
    this->levelEndMarker = std::make_shared<LevelEndMarker>(++this->entityIdCounter,
        CollisionId::EndGameMarkerId, endData.textureIndex,
        sf::Vector2f((float)endData.pixelX, (float)endData.pixelY), this->tileSize);
}

void Level::EndLevel(){
    if (this->life < 1) {
        PushGameOverState();
        return;
    }
}

