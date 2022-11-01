#pragma once

namespace EGE {

class GameEngine {
public:		// constructors/destructors
	GameEngine();
	~GameEngine();
private:	// initializers
	inline void initWindow();
	inline void initKeys();
	inline void initStates();

public:		// public methods

	void run();

public:		// accessors

public:		// public members

private:	// private methods
	void update();
	inline void update_dt();
	void update_SFMLEvents();
	void render();
	void exitGame();
	//void push_state(std::string template_path);


private:	// private 
	struct Settings {
		// window settings
		float fps;
		std::unordered_map<std::string, std::string> win_ini;	//s// user input might be stored in ini file, be careful when using m_settings
		std::string win_configFile = "config/window_settings.ini";
		sf::VideoMode win_videoMode;
		sf::ContextSettings win_contextSettings;
		std::string win_title;
		sf::Uint32 win_style;
		
		std::unordered_map<std::string, int16_t> keyBinds_map;		//>// don't like string here, try to change to const char* later (it's not trivial)
		std::string keyBinds_configFile = "config/keys.ini";

		void changeVideomode(int width, int height) {
			for (sf::VideoMode preset : sf::VideoMode::getFullscreenModes()) {
				if (preset.height == height && preset.width == width) {
					win_videoMode = preset;
					return;
				}
			}
			LOG_ERR("Video mode not found!", (std::string)"Videomode dimensions: " + std::to_string(width) + ", " + std::to_string(height) + ".");
			win_videoMode = sf::VideoMode::getDesktopMode();
		}
	} m_settings;

	sf::RenderWindow window;
	sf::Clock m_dtClock;
	float m_dt;	// as seconds


	State* m_state_current;	//>// should be faster without this pointer, try to recreate loops without m_state_current
	GameState m_state_game;
	MainMenuState m_state_menu;
	EditorState m_state_editor;
};

}
