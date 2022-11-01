#include "ege_pch.h"
#include "Entity.h"

namespace EGE {

// constructors
Entity::Entity(sf::RenderWindow* rWindow, float x, float y, sf::Texture* textureSheet, bool active)
	: WindowComponent(rWindow, active)
	, m_physics(PhysicsComponent(&m_sprite))
	, m_animations(AnimationComponent(&m_sprite, textureSheet)) {
	// init physics
	m_physics.setWalkAcceleration(10);
	this->setPosition(x, y);
	
	if (textureSheet)
		setTextureSheet(textureSheet);

	// init animations
}

Entity::~Entity() {
    
}

void Entity::update() {
	m_physics.update();
}

void Entity::render() {
#	if EGE_DEBUG
	window().draw(m_physics.getHitbox().rect());
#	endif
}

void Entity::setTextureSheet(sf::Texture* textureSheet) {
	m_sprite.setTexture(*textureSheet);
	m_animations.setTextureSheetPtr(textureSheet);
}

void Entity::walk(const float& mult_x, const float& mult_y) {
	m_physics.walk(mult_x, mult_y);
}

}
