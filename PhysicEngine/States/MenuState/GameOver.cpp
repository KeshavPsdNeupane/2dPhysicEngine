#include "GameOver.h"
#include"../../World/Level.h"
#include"LevelSelect.h"
GameOver::GameOver(std::shared_ptr<StateData> stateData, const std::string& previousLevelFilePath) :
	stateData(stateData) , previousLevelFilePath(previousLevelFilePath),
	event(), IsSetectedIndex(0), IsPressedIndex(-1) , texts() {
}
GameOver::~GameOver() {}

void GameOver::Load() {
	// main menu game title
	const sf::Font& font = this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT);
	sf::Vector2u pos = this->stateData->window->getSize();
	sf::Vector2f half(pos.x * 0.5f, pos.y * 0.5f);
	sf::FloatRect bound;

	this->gameMenuTitle.setFont(font);
	this->gameMenuTitle.setString("GAMEOVER");
	this->gameMenuTitle.setCharacterSize(35);
	bound = this->gameMenuTitle.getLocalBounds();
	this->gameMenuTitle.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
	this->gameMenuTitle.setPosition(half.x, half.y * 0.5f);

	for (unsigned int i = 0; i < texts.size(); ++i) {
		auto& text = this->texts[i];
		text.setFont(font);
		text.setCharacterSize(24);
		if (i == 0) text.setString("Replay");
		else if (i == 1) text.setString("Level Select");
		else if (i == 2) text.setString("Exit");
		else text.setString("none");
		bound = text.getLocalBounds();
		text.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
		text.setPosition(half.x, half.y + 2 * text.getCharacterSize() * i - 25.0f);
	}

}

void GameOver::ProcessInput() {
	while (this->stateData->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->stateData->window->close();
		}
		else if (this->event.type == sf::Event::KeyPressed) {
			switch (this->event.key.code) {
			case sf::Keyboard::Up:
			case sf::Keyboard::W:
				this->IsSetectedIndex = VectorOperation::Clamp(this->IsSetectedIndex - 1, 0,(int) this->texts.size()-1);
				break;

			case sf::Keyboard::Down:
			case sf::Keyboard::S:
				this->IsSetectedIndex = VectorOperation::Clamp(this->IsSetectedIndex + 1, 0,(int)this->texts.size() - 1);
				break;

			case sf::Keyboard::Return:
				this->IsPressedIndex = this->IsSetectedIndex;
				break;

			default:
				break;
			}
		}

	}
}

void GameOver::Update(const float& dt) {
	for (unsigned int i = 0; i < texts.size(); ++i) {
		if (i != this->IsSetectedIndex) {
			this->texts[i].setFillColor(sf::Color::White);
		}
		else {
			this->texts[i].setFillColor(sf::Color::Red);
		}
	}

	if (this->IsPressedIndex > -1) {
		if (this->IsPressedIndex == 0) {
			this->stateData->stateManager->AddState(std::make_unique<Level>(this->stateData, this->previousLevelFilePath), true);
		}
		else if (this->IsPressedIndex == 1) {
			this->stateData->stateManager->AddState(std::make_unique<LevelSelect>(this->stateData));
		}
		else if (this->IsPressedIndex == 2) {
			this->stateData->window->close();
		}

	}
}

void GameOver::Draw() {
	this->stateData->window->clear(sf::Color::Black);


	this->stateData->window->draw(this->gameMenuTitle);

	for (auto& text : texts) {
		this->stateData->window->draw(text);
	}

	this->stateData->window->display();
}
