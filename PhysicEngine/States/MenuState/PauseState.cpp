#include "PauseState.h"
#include"LevelSelect.h"

PauseState::PauseState(std::shared_ptr<StateData> stateData) :
	stateData(stateData), texts(),
	event(), isEscPressed(false),IsSetectedIndex(0), IsPressedIndex(-1) {}

PauseState::~PauseState() {}

void PauseState::Load() {
	// main menu game title
	const sf::Font& font = this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT);
	sf::Vector2u pos = this->stateData->window->getSize();
	sf::Vector2f half(pos.x * 0.5f, pos.y * 0.5f);
	sf::FloatRect bound;


	this->gameMenuTitle.setFont(font);
	this->gameMenuTitle.setString("PAUSE MENU");
	this->gameMenuTitle.setCharacterSize(35);
	bound = this->gameMenuTitle.getLocalBounds();
	this->gameMenuTitle.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
	this->gameMenuTitle.setPosition(half.x, half.y * 0.5f);

	for (unsigned int i = 0; i < texts.size(); ++i) {
		auto& text = this->texts[i];
		text.setFont(font);
		text.setCharacterSize(24);
		if (i == 0) text.setString("Resume");
		else if (i == 1) text.setString("Level Select");
		else if (i == 2) text.setString("Exit");
		else text.setString("none");
		bound = text.getLocalBounds();
		text.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
		text.setPosition(half.x, half.y + 2 * text.getCharacterSize() * i - 25.0f);
	}
}

void PauseState::ProcessInput() {
	while (this->stateData->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->stateData->window->close();
		}
		else if (this->event.type == sf::Event::KeyPressed) {
			switch (this->event.key.code) {
			case sf::Keyboard::Up:
			case sf::Keyboard::W:
				this->IsSetectedIndex = VectorOperation::Clamp(this->IsSetectedIndex - 1, 0, (int)this->texts.size());
				break;

			case sf::Keyboard::Down:
			case sf::Keyboard::S:
				this->IsSetectedIndex = VectorOperation::Clamp(this->IsSetectedIndex + 1, 0, (int)this->texts.size());
				break;

			case sf::Keyboard::Return:
				this->IsPressedIndex = this->IsSetectedIndex;
				break;

			case sf::Keyboard::Escape:
				this->isEscPressed = true;
				break;

			default:
				break;
			}
		}

	}
}

void PauseState::Update(const float& dt) {
	if (isEscPressed) {
		this->stateData->stateManager->RemoveState();
		return;
	}
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
			this->stateData->stateManager->RemoveState();
		}
		else if (this->IsPressedIndex == 1) {
			this->stateData->stateManager->AddState(std::make_unique<LevelSelect>(this->stateData), true);
		}
		else if (this->IsPressedIndex == 2) {
			this->stateData->window->close();
		}
	}
}

void PauseState::Draw() {
    this->stateData->window->clear(sf::Color::Black);

	this->stateData->window->draw(this->gameMenuTitle);
	for (auto& text : texts) {
		this->stateData->window->draw(text);
	}

	this->stateData->window->display();
}
