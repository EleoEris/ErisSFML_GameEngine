#pragma once

#include "core/Core.h"
#include "HitboxComponent.h"

namespace EGE {

class PhysicsComponent : public Core {
public:		// constructors
	PhysicsComponent(sf::Sprite* sprite);
	PhysicsComponent();
	~PhysicsComponent();

private:	// initializers
	inline void initVariables();

public:		// public methods
	void update();
	void updateMovement();
	void updateHitbox(); // call after animation init

	void walk(const float& mult_x, const float& mult_y);
	void walkX(const float& mult_x);
	void walkY(const float& mult_y);

	void push(const float& dir_x, const float& dir_y);
	void push(sf::Vector2f& direction);

public:		// accessors&mutators
	void bindGroundDrag(const float* groundDrag) { p_dragGround = groundDrag; }
	inline const sf::Sprite& getDrawable() const {return *p_sprite;}
	inline const sf::Vector2f& getVelocity() const { return m_velocity; }
	inline const float& getWalkVelocity() const { return m_walkAcceleration; }
	inline const bool isMovable() const { return m_movable; }
	inline void setMovable(bool toggle) { m_movable = toggle; }

	void setHitboxOffset(const sf::FloatRect& offset) { m_hitboxOffset = offset; updateHitbox(); }
	inline HitboxComponent& getHitbox() { return m_hitbox; }

	inline void	setWalkAcceleration(const float& accel) { m_walkAcceleration = accel; }

	inline void setAcceleration(const float& acceleration) { m_acceleration.x = acceleration; m_acceleration.y = acceleration; }
	inline void setAcceleration(const sf::Vector2f& acceleration) { m_acceleration = acceleration; }
	inline void setAccelerationFunc(sf::Vector2f(*func)(sf::Vector2f& acceleration)) { m_deccelFunc = func; }

	inline void setPosition(const float& x, const float& y) { if (p_sprite) p_sprite->setPosition(sf::Vector2f(x, y)); m_hitbox.rect().setPosition(sf::Vector2f(x, y)); }
	inline void setPosition(const sf::Vector2f pos) { if (p_sprite) p_sprite->setPosition(pos); m_hitbox.rect().setPosition(pos); }
	
	inline void setRect(const float& x, const float& y, const float& width, const float& height) {
		setPosition(x, y);
		m_hitbox.setRect(sf::FloatRect(x, y, width, height));
	}

	inline void setSprite(sf::Sprite* sprite) {
		p_sprite = sprite;
		m_hitbox.rect().setTextureRect(p_sprite->getTextureRect());
	}

private:	// private members
	sf::Vector2f (*m_deccelFunc)(sf::Vector2f& acceleration);
	sf::Sprite* p_sprite;
	sf::RenderWindow p_rWindow;
	HitboxComponent m_hitbox;
	float m_walkAcceleration;
	float m_maxWalkVelocity;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	sf::FloatRect m_hitboxOffset;

	const float* p_dragGround;	// this will be taken from the ground tiles
	float m_dragAirCoeff;
	float m_mass;				// if m_mass > 9000 the object is immovable

	float m_temperature;

	bool m_movable;
};

}
