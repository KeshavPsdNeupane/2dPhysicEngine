#include "Level1.h"
#include "../States/MenuState/PauseState.h"
#include "../States/MenuState/GameOver.h"

Level1::Level1(std::shared_ptr<StateData> state) :
    WorldSuperClass(state), contactMechanic(*this),
    isPaused(false), event(),
    updateDrawResultFromGrid(),
    collisionResultFromGrid(),
    text(), DT(0.0f),
    entityIdCounter(0) { 
	TileResource tile;
	std::string path = "Asset/Maps/TestMap2.txt";
	TotalTileData& data = tile.ListTheEntity(path);
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
    this->checkPointPosition = positionForPlayer;
    this->text.setFont(this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT));
    this->text.setPosition({ 250.0f,10.0f });
    this->text.setCharacterSize(15);
    this->text2.setFont(this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT));
    this->text2.setPosition({ 550.0f,10.0f });
    this->text2.setCharacterSize(30);

}

Level1::~Level1() {}



void Level1::Load() {
    this->rectangle->Load(this->stateData->resourceManager);
    this->grid.AddObject(this->rectangle, false);

    for (int i = 0; i < this->path.size(); ++i) {
        this->path[i]->Load(this->stateData->resourceManager);
        this->grid.AddObject(this->path[i], true);
    }
	for (int i = 0; i < inflator.size(); ++i) {
		this->inflator[i]->Load(this->stateData->resourceManager);
		this->grid.AddObject(this->inflator[i], true);
	}
    for (int i = 0; i < deflator.size(); ++i) {
        this->deflator[i]->Load(this->stateData->resourceManager);
        this->grid.AddObject(this->deflator[i], true);
    }
	for (int i = 0; i < this->bouncyPath.size(); ++i) {
		this->bouncyPath[i]->Load(this->stateData->resourceManager);
		this->grid.AddObject(this->bouncyPath[i], true);
	}
    for (int i = 0; i < this->collectable.size(); ++i) {
        this->collectable[i]->Load(this->stateData->resourceManager);
        this->grid.AddObject(this->collectable[i], true);
    }
    for (int i = 0; i < this->staticEnemy.size(); ++i) {
        this->staticEnemy[i]->Load(this->stateData->resourceManager);
        this->grid.AddObject(this->staticEnemy[i], true);
    }
    for (int i = 0; i < this->checkPoint.size(); ++i) {
        this->checkPoint[i]->Load(this->stateData->resourceManager);
        this->grid.AddObject(this->checkPoint[i], true);
    }
}


void Level1::ProcessInput() {
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

void Level1::Update(const float& dt) {
    if (this->life < 1) {
        this->stateData->stateManager->AddState(
            std::make_unique<GameOver>(this->stateData));
        return;
    }

    if (!this->isPaused) {
        this->DT = dt;
        this->updateDrawResultFromGrid =
            this->grid.FindUpdatableAndDrawableBlock(this->rectangle);
        collisionResultFromGrid = this->grid.PotentialCollision(this->rectangle);

        for (int i = 0; i < updateDrawResultFromGrid.dynamicResult.size(); ++i) {
            this->updateDrawResultFromGrid.dynamicResult[i]->Update(DT);
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
    }
}


void Level1::Draw() {
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

void Level1::CreateViewBasedOnPlayer(std::shared_ptr<sf::RenderWindow> window) {
    const float Width = (float)window->getSize().x;
    const float Height = (float)window->getSize().y;
    const float halfWidth = Width * 0.5f;
    const float halfHeight = Height * 0.5f;
    sf::Vector2f playerPosition = this->rectangle->GetPosition();
    this->worldView.setSize(Width, Height);
    float clampedX = VectorOperation::Clamp(playerPosition.x, halfWidth, GMNumber::WORLD_SIZE_X - halfWidth);
    float clampedY = VectorOperation::Clamp(playerPosition.y, halfHeight, GMNumber::WORLD_SIZE_Y - halfHeight);
    this->worldView.setCenter({ clampedX, clampedY });

}

void Level1::DrawDefaulView(std::shared_ptr<sf::RenderWindow>window) {
    window->setView(window->getDefaultView());

    window->draw(text);
    window->draw(text2);
    this->rectangle->DrawStats(window);
}

void Level1::Pause() { this->isPaused = true; }

void Level1::Start() { this->isPaused = false; }

void Level1::DisplayStats() {
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

void Level1::DeleteUnwanted() {
    auto& collectables = this->collectable;
    for (auto it = collectables.begin(); it != collectables.end(); ) {
        if ((*it)->GetCanBeDeleted()) {
            this->grid.RemoveObject(*it, true);
            it = collectables.erase(it);
        }
        else { ++it; }
    }
}

void Level1::CreatePath(TotalTileData& data){
    sf::Vector2f nil = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f blockSize{ 64.0f , 64.0f };
    float mass = 400000.0f;
    sf::Vector2f E = GMNumber::COEFF_OF_RESTITUTION_PATH;
    float u = GMNumber::COEFF_OF_FRICTION_PATH;

	const auto& pathData = data.loadEntity[EntityId::path];
    for (int i = 0; i < pathData.size(); ++i) {
        this->path.push_back(std::make_shared<Path>(++this->entityIdCounter, CollisionId::HeavyPathId, mass,
            sf::Vector2f(pathData[i].pixelX, pathData[i].pixelY), blockSize, E, u));
    }

}

void Level1::CreateInflator(TotalTileData& data){
	sf::Vector2f nil = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f blockSize{ 64.0f , 64.0f };
	float mass = 400000.0f;
	sf::Vector2f E = GMNumber::COEFF_OF_RESTITUTION_PATH;
	float u = GMNumber::COEFF_OF_FRICTION_PATH;
	const auto& inflatorData = data.loadEntity[EntityId::inflator];
	for (int i = 0; i < inflatorData.size(); ++i) {
		this->inflator.push_back(std::make_shared<Inflator>(++this->entityIdCounter, CollisionId::InflatorId, mass,
			sf::Vector2f(inflatorData[i].pixelX, inflatorData[i].pixelY), blockSize, E, u));
	}
}

void Level1::CreateDeflator(TotalTileData& data){
	sf::Vector2f nil = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f blockSize{ 64.0f , 64.0f };
	float mass = 400000.0f;
	sf::Vector2f E = GMNumber::COEFF_OF_RESTITUTION_PATH;
	float u = GMNumber::COEFF_OF_FRICTION_PATH;
	const auto& deflatorData = data.loadEntity[EntityId::deflator];
	for (int i = 0; i < deflatorData.size(); ++i) {
		this->deflator.push_back(std::make_shared<Deflator>(++this->entityIdCounter, CollisionId::DeflatorId, mass,
			sf::Vector2f(deflatorData[i].pixelX, deflatorData[i].pixelY), blockSize, E, u));
	}
}

void Level1::CreateBouncyPath(TotalTileData& data){
	sf::Vector2f nil = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f blockSize{ 64.0f , 64.0f };
	float mass = 400000.0f;
	sf::Vector2f E = GMNumber::COEFF_OF_RESTITUTION_PATH;
	float u = GMNumber::COEFF_OF_FRICTION_PATH;
	const auto& bouncyPathData = data.loadEntity[EntityId::bouncypad];
	for (int i = 0; i < bouncyPathData.size(); ++i) {
		this->bouncyPath.push_back(std::make_shared<BouncyPath>(++this->entityIdCounter, CollisionId::HeavyPathId, mass,
			sf::Vector2f(bouncyPathData[i].pixelX, bouncyPathData[i].pixelY), blockSize, sf::Vector2f(0.4f, 2.1f), u));
	}
}

void Level1::CreateCollectable(TotalTileData& data){
	sf::Vector2f nil = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f blockSize{ 64.0f , 64.0f };
	float mass = 400000.0f;
	sf::Vector2f E = GMNumber::COEFF_OF_RESTITUTION_PATH;
	float u = GMNumber::COEFF_OF_FRICTION_PATH;
	const auto& collectableData = data.loadEntity[EntityId::collectable];
	for (int i = 0; i < collectableData.size(); ++i) {
		this->collectable.push_back(std::make_shared<Collectable>(++this->entityIdCounter,
			CollisionId::CollectableId, 1.0f, 10, sf::Vector2f(collectableData[i].pixelX, collectableData[i].pixelY),
			sf::Vector2f(48.0f, 48.0f)));
	}
}

void Level1::CreateStaticEnemy(TotalTileData& data){
	sf::Vector2f nil = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f blockSize{ 64.0f , 64.0f };
	float mass = 400000.0f;
	sf::Vector2f E = GMNumber::COEFF_OF_RESTITUTION_PATH;
	float u = GMNumber::COEFF_OF_FRICTION_PATH;
	const auto& staticEnemyData = data.loadEntity[EntityId::staticEnemy];
	for (int i = 0; i < staticEnemyData.size(); ++i) {
		this->staticEnemy.push_back(std::make_shared<StaticEnemy>(++this->entityIdCounter, CollisionId::StaticEnemyId, mass,
			sf::Vector2f(staticEnemyData[i].pixelX, staticEnemyData[i].pixelY), blockSize, E, u));
	}
}

void Level1::CreateCheckPoint(TotalTileData& data){
	sf::Vector2f nil = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f blockSize{ 64.0f , 64.0f };
	float mass = 400000.0f;
	sf::Vector2f E = GMNumber::COEFF_OF_RESTITUTION_PATH;
	float u = GMNumber::COEFF_OF_FRICTION_PATH;
	const auto& checkPointData = data.loadEntity[EntityId::checkPoint];
	for (int i = 0; i < checkPointData.size(); ++i) {
		this->checkPoint.push_back(std::make_shared<CheckPoint>(++this->entityIdCounter, CollisionId::CheckPointId,
			sf::Vector2f(checkPointData[i].pixelX, checkPointData[i].pixelY), sf::Vector2f(50.0f, 50.0f)));
	}
}
