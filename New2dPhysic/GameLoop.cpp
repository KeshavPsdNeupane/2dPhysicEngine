#include "GameLoop.h"
#include "States/MenuState/MainMenuState.h"

Gameloop::Gameloop():
stateData(std::make_shared<StateData>()),
DELTA_TIME(0.0f){
	this->stateData->window->create(sf::VideoMode(static_cast<int>(GMNumber::WINDOW_WIDTH),
		static_cast<int>(GMNumber::WINDOW_HEIGHT)),
		" Physic Engine" , sf::Style::Close);
	this->stateData->window->setFramerateLimit(GMNumber::MAX_FRAME_RATE);
	this->stateData->stateManager->AddState(
		std::make_unique<MainMenu>(this->stateData), true);
	LoadAllAssets();
}

Gameloop::~Gameloop(){}
void Gameloop::Run(){
    while (this->stateData->window->isOpen()){
		this->DELTA_TIME = clock.restart().asSeconds();
        this->stateData->stateManager->ProcessStateChanges();
		auto& currentState = this->stateData->stateManager->GetActiveState();

		currentState->ProcessInput();
		currentState->Update(DELTA_TIME);
        currentState->Draw();
    }
}

void Gameloop::LoadAllAssets(){
	auto& resource = this->stateData->resourceManager;
	resource->AddFont(ResourceId::MAIN_FONT, "Asset/Fonts/arial.ttf");
}
