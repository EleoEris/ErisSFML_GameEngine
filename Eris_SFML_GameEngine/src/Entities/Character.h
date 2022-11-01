#pragma once
#include "Entity.h"

namespace EGE {

class Character : public Entity {
public:		// constructors
	Character(sf::RenderWindow* rWindow, float x, float y, sf::Texture* textureSheet = nullptr, bool active = false);
	~Character();

private:	// initializers
	inline void initPhysics();
	inline void initAnimations();

public:		// public methods
	virtual void walk(const float& mult_x, const float& mult_y);
	virtual void update();
	virtual void render();

public:		// public members

public:		// accessors

private:	// private members
	struct Traits {
		// intelligence, charisma and other personality traits are up to the player's choices
		// warrior
		int strength		= 5; // +++swing force, ++health, +stamina, + size
		int endurance		= 5; // +++size, ++health, ++stamina
		int bulk			= 5; // +++mass, +size

		// thief
		int dextrierity		= 5; // weapon feints, crit possibility, +health, ++stamina
		int agility			= 5; // ++speed, ++dodge
		int engineering		= 5; // ++ability to use contraptions
		
		// mage
		int impulse_control	= 5; // speed and versatility of manifestation
		int focus			= 5; // density of manifestation
		int arcane			= 5; // amount of manifestations

		//misc
		int luck			= 5; // ++++favorability of Tyche
	} m_traits;
	struct Action {
		sf::Vector2f walking = sf::Vector2f(0, 0);
	};
	Action m_futureAction;
	Action m_nowAction;

	sf::Vector2i t_facingDir[5] = {};

private:	// private methods
	inline void checkAnimChange();
};

}
