#include "ege_pch.h"
#include "GameState.h"

namespace EGE {

// constructors
GameState::GameState(sf::RenderWindow* rWindow, bool active, bool rendering) 
	: State(rWindow, StatesEnum::game, active, rendering)
	, m_player(rWindow, 200, 200, (sf::Texture*)&getTexture("player")) {
	initFonts();
	initTextures();
}

GameState::~GameState() {
}

void GameState::init() {
}

void GameState::initFonts() {
}

void GameState::initTextures() {
}



// public methods
void GameState::updateWindowSettings() {
	LOG_INFO("UPDATED WINDOW SETTINGS!", "Updated window settings for GameState");
} 

void GameState::update() {
	PROFILE_HERE;
	updateInput();
	m_player.update();
}

void GameState::render() {
	PROFILE_HERE;
	m_player.render();

	if (!m_inBackground) {
#		ifdef EGE_DEBUG
		D_renderDebug();
#		endif
	}
}

void GameState::activateState() {
	LOG_SUCC("ACTIVATING STATE", "Activating GameState");
	m_inBackground = false;
	m_active = true;
	m_rendering = true;
	m_player.setActive(true);
}

void GameState::deactivateState() {
	LOG_WARN("DEACTIVATING STATE", "Deactivating GameState");
	m_active = false;
	m_inBackground = true;
	m_player.setActive(false);
}

// accessors


// private methods
//inline void GameState::updateInput() { //+// set to inline
void GameState::updateInput() {
	PROFILE_HERE;
	// mouse
	updateMousePos();

	// keys
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("escape")))) {
		State::deactivateState(StatesEnum::menu);
	}

	// movement

	// running
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("mod_run")))) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("up")))) {				// N_
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("left")))) {		// NW
				m_player.walk(-2, -2);
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("right")))) {// NE
				m_player.walk(2, -2);
			} else {																		// N
				m_player.walk(0, -2);
			}
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("down")))) {		// S_
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("left")))) {		// SW
				m_player.walk(-2, 2);
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("right")))) {// SE
				m_player.walk(2, 2);
			} else {																		// S
				m_player.walk(0, 2);
			}
		} else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("left")))) {		// W
				m_player.walk(-2, 0);
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("right")))) {		// E
				m_player.walk(2, 0);
			} else {
				m_player.walk(0, 0);
			}
		}
	} 
	// walking
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("up")))) {				// N_
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("left")))) {		// NW
				m_player.walk(-1, -1);
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("right")))) {// NE
				m_player.walk(1, -1);
			} else {																		// N
				m_player.walk(0, -1);
			}
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("down")))) {		// S_
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("left")))) {		// SW
				m_player.walk(-1, 1);
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("right")))) {// SE
				m_player.walk(1, 1);
			} else {																		// S
				m_player.walk(0, 1);
			}
		} else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("left")))) {		// W
				m_player.walk(-1, 0);
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("right")))) {		// E
				m_player.walk(1, 0);
			} else {
				m_player.walk(0, 0);
			}
		}
	}
}

} // namespace EGE
