#include "Resources.h"

Resources::Resources(){
	if (!this->font.loadFromFile("Asset/Fonts/arial.ttf")) {
		std::cerr << " unable to load font from Assect/Fonts/arial.ttf  " << std::endl;
	}
}
