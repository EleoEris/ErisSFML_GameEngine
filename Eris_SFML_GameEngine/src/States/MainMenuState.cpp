#include "ege_pch.h"
#include "MainMenuState.h"

namespace EGE {

// constructors
MainMenuState::MainMenuState(sf::RenderWindow* rWindow, bool active, bool rendering)
	: State(rWindow, StatesEnum::menu, active, rendering)
	, m_bgActive(true) {
	initFonts();
	initTextures();
}

MainMenuState::~MainMenuState() {
}


// initializers
void MainMenuState::init() {
	initBackground();
	initButtons();
}

void MainMenuState::initFonts() {
}

void MainMenuState::initTextures() {
	State::addTexture("mainmenu_background", "assets/backgrounds/mainmenu_bg.jpg");
}

inline void MainMenuState::initBackground() {
	m_background_fade_color = sf::Color(0, 0, 0, 128);
	m_background.setSize(sf::Vector2f(getWindow().getSize()));
	m_background.setTexture(&getTexture("mainmenu_background"));
}

void MainMenuState::initButtons() {
	float diff = 80;

	m_buttons.push_back(
		Button(
			&getWindow(),
			"START GAME", 20, &getFont("medieval_elegant"),
			[&]() {
				State::deactivateState(StatesEnum::game);
			},
			250, 100 + diff, 150, 50,
			sf::Color(63, 126, 179),
			sf::Color::Black
		)
	);

	m_buttons.push_back(
		Button(
			&getWindow(),
			"LOAD GAME", 20, &getFont("medieval_elegant"),
			[&]() {},
			250, 100 + diff * 2, 150, 50,
			sf::Color(63, 126, 179),
			sf::Color::Black
		)
	);

	m_buttons.push_back(
		Button(
			&getWindow(),
			"SETTINGS", 20, &getFont("medieval_elegant"),
			[&] () {},
			250, 100 + diff * 3, 150, 50,
			sf::Color(63, 126, 179),
			sf::Color::Black
		)
	);

	m_buttons.push_back(
		Button(
			&getWindow(),
			"EDITOR", 20, 
			&getFont("medieval_elegant"),
			[&]() {
				State::deactivateState(StatesEnum::editor);
			},
			250, 100 + diff * 4, 150, 50,
			sf::Color(63, 126, 179),
			sf::Color::Black
			)
	);

	m_buttons.push_back(
		Button(
			&getWindow(),
			"EXIT", 20, &getFont("medieval_elegant"),
			[&] () {
				State::deactivateState(StatesEnum::quit);
			},
			250, 100 + diff * 5, 150, 50,
			sf::Color(63, 126, 179),
			sf::Color::Black
			)
	);
}


// operators

void MainMenuState::setBackgroundActive(bool state) {
	if (state)
		m_background.setTexture(&getTexture("mainmenu_background"));
	else
		m_background.setFillColor(m_background_fade_color);
}

// public methods
void MainMenuState::updateWindowSettings() {
	LOG_INFO("UPDATED WINDOW SETTINGS!", "Updated window settings for MainMenuState");
	m_background.setSize(sf::Vector2f(getWindow().getSize()));
}


void MainMenuState::update() {
	PROFILE_HERE;
	updateInput();
	updateButtons();
}

void MainMenuState::render() {
	PROFILE_HERE;
	getWindow().draw(m_background);

	renderButtons();


#	ifdef EGE_DEBUG
	D_renderDebug();
#	endif
}

void MainMenuState::activateState() {
	LOG_SUCC("ACTIVATING STATE", "Activating MainMenuState");
	m_active = true;
	m_rendering = true;
}

void MainMenuState::deactivateState() {
	LOG_WARN("DEACTIVATING STATE", "Deactivating MainMenuState");
	m_rendering = false;
	m_active = false;
}


// accessors


// private methods
void MainMenuState::updateInput() {
	PROFILE_HERE;
	// keys
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(p_keyBinds->at("escape")))) {
	//	State::deactivateState(StatesEnum::quit);
	//}

	// mouse
	updateMousePos();
}

} // namespace EGE
