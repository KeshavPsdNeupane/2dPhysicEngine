#include "LevelSelect.h"
#include"../../World/Level.h"

LevelSelect::LevelSelect(std::shared_ptr<StateData> stateData) :
	stateData(stateData),event(),
	IsSetectedIndex(0), IsPressedIndex(-1), texts() {}

LevelSelect::~LevelSelect() {}

void LevelSelect::Load() {
	// main menu game title
	const sf::Font& font = this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT);
	sf::Vector2u pos = this->stateData->window->getSize();
	sf::Vector2f half(pos.x * 0.5f, pos.y * 0.5f);
	sf::FloatRect bound;

	this->gameMenuTitle.setFont(font);
	this->gameMenuTitle.setString("Level Select");
	this->gameMenuTitle.setCharacterSize(35);
	bound = this->gameMenuTitle.getLocalBounds();
	this->gameMenuTitle.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
	this->gameMenuTitle.setPosition(half.x , half.y * 0.5f);


	for (unsigned int i = 0; i < texts.size(); ++i) {
		auto& level = this->texts[i];
		level.setFont(font);
		if (i != texts.size() - 1) {
			level.setString("Level" + std::to_string(i + 1) + " ");
		}
		else {
			level.setString("Exit");
		}
		level.setCharacterSize(24);
		bound = level.getLocalBounds();
		level.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
		level.setPosition(half.x, half.y - 25.0f + 2 * level.getCharacterSize() * i);
	}

}

void LevelSelect::ProcessInput() {
	while (this->stateData->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->stateData->window->close();
		}
		else if (this->event.type == sf::Event::KeyPressed) {
			switch (this->event.key.code) {
			case sf::Keyboard::Up:
			case sf::Keyboard::W:
				this->IsSetectedIndex = VectorOperation::Clamp(this->IsSetectedIndex - 1, 0, (int)(this->texts.size() - 1));
				break;

			case sf::Keyboard::Down:
			case sf::Keyboard::S:
				this->IsSetectedIndex = VectorOperation::Clamp(this->IsSetectedIndex + 1, 0, (int)(this->texts.size() - 1));
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

void LevelSelect::Update(const float& dt) {

	for (unsigned int i = 0; i < texts.size(); i++) {
		if (i != this->IsSetectedIndex) {
			this->texts[i].setFillColor(sf::Color::White);
		}
		else {
			this->texts[i].setFillColor(sf::Color::Red);
		}
	}

	if (this->IsPressedIndex > -1) {
		if (this->IsPressedIndex != texts.size() - 1) {
			std::string path("Asset/Maps/Level" + std::to_string(this->IsPressedIndex + 1) + ".txt");
			this->stateData->stateManager->AddState(std::make_unique<Level>(this->stateData, path), true);
		}
		else {
			this->stateData->window->close();
		}
	}
}

void LevelSelect::Draw() {
	this->stateData->window->clear(sf::Color::Black);
	this->stateData->window->draw(this->gameMenuTitle);
	for (auto& text : texts) {
		this->stateData->window->draw(text);
	}
	this->stateData->window->display();

}
