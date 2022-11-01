#include "ege_pch.h"
#include "EditorState.h"

namespace EGE {

// constructors
EditorState::EditorState(sf::RenderWindow* rWindow, bool active, bool rendering)
	: State(rWindow, StatesEnum::menu, active, rendering)  {
	initFonts();
	initTextures();
}

EditorState::~EditorState() {
    
}

void EditorState::init() { }

void EditorState::initFonts() { }

void EditorState::initTextures() { }


// initializers


// public methods

inline void EditorState::updateWindowSettings() { }

void EditorState::update() {
	PROFILE_HERE;
	updateInput();
	updateButtons();
}

void EditorState::render() {
	PROFILE_HERE;
		
	renderButtons();

#	ifdef EGE_DEBUG
	D_renderDebug();
#	endif
}

void EditorState::activateState() {
	LOG_SUCC("ACTIVATING STATE", "Activating EditorState");
	m_active = true;
	m_rendering = true;
}

void EditorState::deactivateState() {
	LOG_WARN("DEACTIVATING STATE", "Deactivating EditorState");
	m_rendering = false;
	m_active = false;
}

inline void EditorState::updateInput() {

	// mouse
	updateMousePos();

	// keys
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(getKeyBind("escape")))) {
		State::deactivateState(StatesEnum::menu);
	}
}

// accessors&mutators


// private methods

} // namespace EGE
