#include "ege_pch.h"
#include "GameEngine.h"

namespace EGE {

float*										Core::p_dt			= nullptr;
std::unordered_map<std::string, int16_t>*	State::p_keyBinds	= nullptr;

// constructors/destructors
GameEngine::GameEngine()
	: window(sf::VideoMode(640, 320), "Made by Eris")
	, m_state_game(&window)
	, m_state_menu(&window)
	, m_state_editor(&window) { // be sure to update window settings for states since the definition order is undefined behavior in current cpp //C+++//check if this is solved

	Core::setDtPtr(&m_dt);

	initWindow();
	initKeys();
	initStates();
}

GameEngine::~GameEngine() {
}

// initializers
void GameEngine::initWindow() {
	std::unordered_map<std::string, std::string> settings = EUfuncs::mapFromIni(m_settings.win_configFile);

	LOG_ASSERT(settings["INTERNAL_ERROR"] != "", settings["INTERNAL_ERROR"], "Please check the file " + m_settings.win_configFile);
	settings.erase("INTERNAL_ERROR");

	// in case m_settings already has values, it needs to swap before merging for it to update
	// due to precedence rules
	m_settings.win_ini.swap(settings);
	m_settings.win_ini.merge(settings);

	m_settings.win_contextSettings.antialiasingLevel = std::stoi(m_settings.win_ini["antialiasing"]);

	m_settings.win_title = "Eria";
	m_settings.changeVideomode(std::stoi(m_settings.win_ini["window_width"]), std::stoi(m_settings.win_ini["window_height"]));

	window.create(
		m_settings.win_videoMode,
		m_settings.win_title,
		sf::Style::Titlebar | sf::Style::Close | (EUfuncs::str2bool(m_settings.win_ini["fullscreen"]) ? sf::Style::Fullscreen : NULL),
		m_settings.win_contextSettings
	);

	window.setFramerateLimit(std::stoi(m_settings.win_ini["fps_limit"]));
	window.setVerticalSyncEnabled(EUfuncs::str2bool(m_settings.win_ini["vsync"]));
}

void GameEngine::initKeys() {
	std::unordered_map<std::string, std::string> keysIni = EUfuncs::mapFromIni(m_settings.keyBinds_configFile);

	LOG_ASSERT(keysIni["INTERNAL_ERROR"] != "", keysIni["INTERNAL_ERROR"], "Please check the file " + m_settings.keyBinds_configFile);
	keysIni.erase("INTERNAL_ERROR");

	for (auto pair : keysIni) {
		m_settings.keyBinds_map[pair.first] = std::stoi(pair.second);
	}
}

void GameEngine::initStates() {
	State::setKeyBindsPtr(&m_settings.keyBinds_map);

	m_state_menu.init();
	m_state_game.init();
	m_state_editor.init();

	m_state_current = &m_state_menu;
	m_state_current->activateState();
}

// public methods
void GameEngine::run() {
	PROFILE_HERE;
	float frame = 0;
	while (window.isOpen()) {
		update();
		frame += m_dt;
		if (frame > 1 / m_settings.fps) {
			render();
			frame = 0;
		}
	}
}

// private methods
void GameEngine::update() {
	PROFILE_HERE;
	update_dt();

	if (m_state_current->isActive()) {		// if state is active
		m_state_current->update();
	} else {								// else change state
		switch (m_state_current->getNextState()) { // reminder: same computation for each case
		// the m_state_menu will load the settings for each state change
		case StatesEnum::menu:
			m_state_menu.activateState();
			m_state_current = &m_state_menu;
			break;
		case StatesEnum::game:
			m_state_menu.setBackgroundActive(false);
			m_state_game.activateState();
			m_state_current = &m_state_game;
			break;
		case StatesEnum::editor:
			m_state_game.setRendering(false);
			m_state_editor.activateState();
			m_state_current = &m_state_editor;
			break;
		case StatesEnum::extraMenu:
			break;
		case StatesEnum::quit:
			exitGame();
			break;
		}
	}

	update_SFMLEvents();
}

inline void GameEngine::update_dt() {
	m_dt = m_dtClock.restart().asSeconds();
}

void GameEngine::update_SFMLEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_state_current->deactivateState();
			exitGame();
		}
	}
}

void GameEngine::render() {
	PROFILE_HERE;
	window.clear();

	if (m_state_game.isRendering()) {
		m_state_game.render();
	}
	if (m_state_menu.isRendering()) {
		m_state_menu.render();
	}

	window.display();
}

void GameEngine::exitGame() {
	window.close();
	m_state_current = nullptr;
}

} // namespace EGE
