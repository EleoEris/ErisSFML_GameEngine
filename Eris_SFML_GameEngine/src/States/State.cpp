#include "ege_pch.h"
#include "State.h"

namespace EGE {

State::State(sf::RenderWindow* rWindow, StatesEnum::StatesEnum id, bool active, bool rendering) 
	: id(id), WindowComponent(rWindow, active, 1000), m_rendering(rendering), m_inBackground(false)
	, m_nextState(StatesEnum::noChange) {
	PROFILE_HERE;
	initFonts();
	initTextures();

#	ifdef EGE_DEBUG
	D_initDebug();
#	endif
}

void State::initFonts() {
	addFont("medieval_elegant",		"assets/fonts/MedievalSharp/MedievalSharp-Regular.ttf");
	addFont("pen_elegant",			"assets/fonts/Dancing_Script/static/DancingScript-Regular.ttf");
	addFont("pen_firm",				"assets/fonts/Lobster_Two/LobsterTwo-Regular.ttf");
	addFont("pen_perky",			"assets/fonts/Niconne/Niconne-Regular.ttf");
	addFont("pen_child",			"assets/fonts/Reenie_Beanie/ReenieBeanie-Regular.ttf");
	addFont("paint_weak",			"assets/fonts/Amatic_SC/AmaticSC-Regular.ttf");
	addFont("paint_strong",			"assets/fonts/Permanent_Marker/PermanentMarker-Regular.ttf");
	addFont("ragged",				"assets/fonts/Fredericka_the_Great/FrederickatheGreat-Regular.ttf");
	addFont("monospace_pixel",		"assets/fonts/VT323/VT323-Regular.ttf");
	addFont("monospace_elegant",	"assets/fonts/Share_Tech_Mono/ShareTechMono-Regular.ttf");
}

void State::initTextures() {
	addTexture("player", "assets/sprites/characters/Valla/Valla.png");
}

void State::addFont(std::string name, std::string path) {
	LOG_ASSERT(!m_fonts[name].loadFromFile(path), "COULD NOT LOAD FONT!", "Font: %s,\nPath: %s", name.c_str(), path.c_str());
}

void State::addTexture(std::string name, std::string path) {
	LOG_ASSERT(!m_textures[name].loadFromFile(path), "COULD NOT LOAD TEXTURE!", "Texture: %s,\nPath: %s", name.c_str(), path.c_str());
}

inline void State::updateMousePos() {
	m_mousePosView = getWindow().mapPixelToCoords(sf::Mouse::getPosition(getWindow()));
	m_mousePosWin = sf::Mouse::getPosition(getWindow());
}

void State::updateButtons() {
	for (auto &button : m_buttons) {
		button.update(m_mousePosView);
	}
}

void State::renderButtons() {
	PROFILE_HERE;
	for (auto button : m_buttons) {
		button.render();
	}
}

}

