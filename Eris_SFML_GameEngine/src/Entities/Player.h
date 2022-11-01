#pragma once
#include "Character.h"

namespace EGE {

class Player : public Character {
public:		// constructors
	Player(sf::RenderWindow* rWindow, float x, float y, sf::Texture* textureSheet);
	~Player();

private:	// initializers

public:		// public methods
	void update();
	void render();

public:		// public members

public:		// accessors&mutators

private:	// private members


private:	// private methods
	inline void updatePhysics();

};

}
