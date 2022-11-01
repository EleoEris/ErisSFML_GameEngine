#include "ege_pch.h"
#include "PhysicsComponent.h"

namespace EGE {

PhysicsComponent::PhysicsComponent() {
	initVariables();
}

PhysicsComponent::PhysicsComponent(sf::Sprite * sprite) {
	initVariables();
	p_sprite = sprite;
}

PhysicsComponent::~PhysicsComponent() {
}

inline void PhysicsComponent::initVariables() {
	m_movable			= false;
	m_deccelFunc		= [](sf::Vector2f& movement) { return movement * 0.5f; }; // you can calculate max_velocity by doing a derivative of mov function
	m_mass				= 1; //+// change this value to 999 after testing
	m_dragAirCoeff		= 0.5; // A little more than a sphere
	p_dragGround		= nullptr;
	m_velocity			= sf::Vector2f(0, 0);
	m_acceleration		= sf::Vector2f(0, 0);
	m_maxWalkVelocity	= 2;
	m_walkAcceleration	= 1;

	m_hitbox.setOutlineColor(sf::Color(0, 255, 0));

	p_sprite			= nullptr;
}

void PhysicsComponent::updateHitbox() { // call after animation init
	m_hitbox.setRect(
		p_sprite->getGlobalBounds().left + m_hitboxOffset.left,
		p_sprite->getGlobalBounds().top + m_hitboxOffset.top,
		p_sprite->getGlobalBounds().width + m_hitboxOffset.width,
		p_sprite->getGlobalBounds().height + m_hitboxOffset.height
	);
}

void PhysicsComponent::update() {
	PROFILE_HERE;
	if (isMovable())
		updateMovement();
	m_hitbox.update();
}

inline void PhysicsComponent::updateMovement() {
	m_velocity = m_deccelFunc(m_velocity);
	if (p_dragGround)
		m_velocity *= m_mass * *p_dragGround;
	m_velocity += m_acceleration;

	p_sprite->move(m_velocity);
	m_hitbox.move(m_velocity);
}

void PhysicsComponent::walkX(const float& mult_x) {
	m_velocity.x += mult_x * m_walkAcceleration * dt();
}

void PhysicsComponent::walkY(const float& mult_y) {
	m_velocity.y += mult_y * m_walkAcceleration * dt();
}

void PhysicsComponent::walk(const float& mult_x, const float& mult_y) {
	m_velocity.x += mult_x * m_walkAcceleration * dt();
	m_velocity.y += mult_y * m_walkAcceleration * dt();
}

void PhysicsComponent::push(const float& dir_x, const float& dir_y) {
	if (m_mass < 9000) {
		m_velocity.x += dir_x / m_mass;
		m_velocity.y += dir_y / m_mass;
	}
}

void PhysicsComponent::push(sf::Vector2f & direction) {
	if (m_mass < 9000) {
		m_velocity += direction / m_mass;
	}
}

}
