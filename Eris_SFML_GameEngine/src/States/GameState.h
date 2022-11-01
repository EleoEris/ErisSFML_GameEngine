#pragma once
#include "State.h"
#include "Entities/Player.h"

namespace EGE {

// maybe rename to MainState since it'll swap between game and main menu

class GameState
	: public State {
public:		// constructors
	GameState(sf::RenderWindow* rWindow, bool active = false, bool rendering = false);
	~GameState();

	void init();
private:	// initializers
	static void initFonts();
	void initTextures();

public:		// operators

public:		// public methods
	void updateWindowSettings();

	void update();
	void render();

	inline void activateState();
	inline void deactivateState();

public:		// public members

public:		// accessors

private:	// private members
	Player m_player;
private:	// private methods
	void updateInput() override;
};

}
