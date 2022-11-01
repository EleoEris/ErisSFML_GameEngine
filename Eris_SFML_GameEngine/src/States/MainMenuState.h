#pragma once

namespace EGE {

class MainMenuState
	: public State {
public:		// constructors
	MainMenuState(sf::RenderWindow* rWindow, bool active = false, bool rendering = false);
	virtual ~MainMenuState();

	void init();
private:	// initializers
	static void initFonts();
	void initTextures();
	void initBackground();
	void initButtons();

public:		// operators

public:		// public methods
	void setBackgroundActive(bool state = false);
	inline void updateWindowSettings();

	void update();
	void render() override;


	void activateState();
	void deactivateState();

public:		// public members

public:		// accessors&mutators

private:	// private members
	bool m_bgActive;
	sf::RectangleShape m_background;
	sf::Color m_background_fade_color;

private:	// private methods
	inline void updateInput() override;
};

}
