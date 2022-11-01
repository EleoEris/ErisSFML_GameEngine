#include "ege_pch.h"
#include "Character.h"

namespace EGE {

// constructors
Character::Character(sf::RenderWindow* rWindow, float x, float y, sf::Texture* textureSheet, bool active) 
	: Entity(rWindow, x, y, textureSheet, active) {
	initPhysics();
	initAnimations();
	m_physics.updateHitbox();
}

Character::~Character() {
}

inline void Character::initPhysics() {
	m_physics.setMovable(true);
}

inline void Character::initAnimations() {
	sf::Vector2i size(42, 56);
	int offsety = 65;
	int offsetaddy = 4;
	int offsetaddx = 4;
	int offsetxx = 61;
	int offsetx = 40;

	m_animations.addAnimation("WALK_NW", 5, 262,
							  size.x, size.y, 51, 0,
							  4, 10, 2);
	m_animations.addAnimation("WALK_SW", 5, 333,
							  size.x, size.y, offsetxx, 0,
							  4, 10, 2);
	m_animations.addAnimation("WALK_NE", 5, 406,
							  size.x, size.y, 51, 0,
							  4, 10, 20);
	m_animations.addAnimation("WALK_SE", 5, 478,
							  size.x, size.y, offsetxx, 0,
							  4, 10, 2);
	m_animations.addAnimation("WALK_N", 891, 262,
							  size.x, size.y, 51, 0,
							  4, 10, 2);
	m_animations.addAnimation("WALK_W", 891, 333,
							  size.x, size.y, offsetxx, 0,
							  4, 10, 2);
	m_animations.addAnimation("WALK_E", 891, 406,
							  size.x, size.y, 51, 0,
							  4, 10, 2);
	m_animations.addAnimation("WALK_S", 891, 478,
							  size.x, size.y, offsetxx, 0,
							  4, 10, 2);



	m_animations.addAnimation("IDLE_NW", 5, 5,
							  size.x, size.y, offsetxx, 0,
							  4, 10, 2);
	m_animations.addAnimation("IDLE_SW", 5, 70,
							  size.x, size.y, offsetx, 0,
							  4, 10, 2);
	m_animations.addAnimation("IDLE_NE", 5, 134,
							  size.x, size.y, offsetxx, 0,
							  4, 10, 2);
	m_animations.addAnimation("IDLE_SE", 5, 199,
							  size.x, size.y, offsetx, 0,
							  4, 10, 2);

	m_animations.addAnimation("IDLE_N", 891, 5,
							  size.x, size.y, offsetxx, 0,
							  4, 10, 2);
	m_animations.addAnimation("IDLE_W", 891, 70,
							  size.x, size.y, offsetx, 0,
							  4, 10, 2);
	m_animations.addAnimation("IDLE_E", 891, 134,
							  size.x, size.y, offsetxx, 0,
							  4, 10, 2);
	m_animations.addAnimation("IDLE_S", 891, 199,
							  size.x, size.y, offsetxx, 0,
							  4, 10, 2);

	m_animations.setCurrent("IDLE_S");
}


// initializers


// public methods

void Character::walk(const float & mult_x, const float & mult_y) {
	Entity::walk(m_nowAction.walking.x, m_nowAction.walking.y);
	m_nowAction.walking.x = mult_x;
	m_nowAction.walking.y = mult_y;
}

void Character::update() {
	Entity::update();
}

void Character::render() {

	if (isActive()) {
		Entity::render();
		t_facingDir[4] = t_facingDir[3];
		t_facingDir[3] = t_facingDir[2];
		t_facingDir[2] = t_facingDir[1];
		t_facingDir[1] = t_facingDir[0];
		t_facingDir[0].x = MATH::sgn(m_nowAction.walking.x);
		t_facingDir[0].y = MATH::sgn(m_nowAction.walking.y);

		checkAnimChange();
		m_animations.playCurrent();
	}

	getWindow().draw(m_sprite);
}

inline void Character::checkAnimChange() {
	int frames4idle = 1;
	if (t_facingDir[0] != t_facingDir[frames4idle]) {			// if direction changed in the last frames4idle frames
		m_animations.resetCurrent();

		if (t_facingDir[0].x == 0 && t_facingDir[0].y == 0) { // idling
			if (!t_facingDir[frames4idle].y) {				// previously idled on Y
				if (t_facingDir[frames4idle].x == 1) {		// previously went east
					m_animations.setCurrent("IDLE_E");
				} else if (t_facingDir[frames4idle].x == -1) {// previously went west
					m_animations.setCurrent("IDLE_W");
				}
			} else if (t_facingDir[frames4idle].y == 1) {		// previously went south
				if (t_facingDir[frames4idle].x == 1) {			// previously went east
					m_animations.setCurrent("IDLE_SE");
				} else if (t_facingDir[frames4idle].x == -1) {	// previously went west
					m_animations.setCurrent("IDLE_SW");
				} else if (!t_facingDir[frames4idle].x) {		// idled on X
					m_animations.setCurrent("IDLE_S");
				}
			} else if (t_facingDir[frames4idle].y == -1) {	// previously went north
				if (t_facingDir[frames4idle].x == 1) {		// previously went east
					m_animations.setCurrent("IDLE_NE");
				} else if (t_facingDir[frames4idle].x == -1) {// previously went west
					m_animations.setCurrent("IDLE_NW");
				} else if (!t_facingDir[frames4idle].x) {		// idled on X
					m_animations.setCurrent("IDLE_N");
				}
			}
		} else if (!t_facingDir[0].y) {				// idling on Y
			if (t_facingDir[0].x == 1) {			// going east
				m_animations.setCurrent("WALK_E");
			} else if (t_facingDir[0].x == -1) {	// going west
				m_animations.setCurrent("WALK_W");
			}
		} else if (t_facingDir[0].y == 1) {			// going south
			if (t_facingDir[0].x == 1) {			// going east
				m_animations.setCurrent("WALK_SE");
			} else if (t_facingDir[0].x == 1) {		// going west
				m_animations.setCurrent("WALK_SW");
			} else if (!t_facingDir[0].x) {			// idling on X
				m_animations.setCurrent("WALK_S");
			}
		} else if (t_facingDir[0].y == -1) {		// going north
			if (t_facingDir[0].x == 1) {			// going east
				m_animations.setCurrent("WALK_NE");
			} else if (t_facingDir[0].x == -1) {	// going west
				m_animations.setCurrent("WALK_NW");
			} else if (!t_facingDir[0].x) {			// idling on X
				m_animations.setCurrent("WALK_N");
			}
		}
	}
}

// accessors


// private methods

}
