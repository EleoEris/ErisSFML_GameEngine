#pragma once

#include "components/PhysicsComponent.h"
#include "components/AnimationComponent.h"

namespace EGE {

class Entity : public WindowComponent {
public:		// constructors
	Entity(sf::RenderWindow* rWindow, float x, float y, sf::Texture* textureSheet = nullptr, bool active = true);
	~Entity();

protected:	// initializers

public:		// public methods
	virtual void update();
	virtual void render();

public:		// public members

public:		// accessors&mutators
	void setPosition(const float& x, const float& y) { m_physics.setPosition(x, y); }

	void setTextureSheet(sf::Texture* textureSheet);

	virtual void walk(const float& mult_x, const float& mult_y);
protected:	// private members
	// sprite's movement is controlled by physics component through its pointer
	// the texture is controlled by animation component the same way
	sf::Sprite m_sprite; //+// need to have a meccanism that changes the AnimationComp speed by checking the physics speed
	AnimationComponent m_animations;
	PhysicsComponent m_physics;

protected:	// private methods
	virtual inline void updatePhysics() = 0;

};

}
