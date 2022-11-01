#include "ege_pch.h"
#include "HitboxComponent.h"

namespace EGE {

// constructors
HitboxComponent::HitboxComponent() {
	m_rect.setOutlineColor(sf::Color::Green);
	m_rect.setOutlineThickness(2.f);
	m_rect.setFillColor(sf::Color::Transparent);
}

HitboxComponent::~HitboxComponent() {
    
}

void HitboxComponent::setRect(sf::FloatRect& rect) {
	m_rect.setPosition(rect.left, rect.top);
	m_rect.setSize(sf::Vector2f(rect.width, rect.height));
}

void HitboxComponent::setRect(const float & left, const float & top, const float & width, const float & height) {
	m_rect.setPosition(left, top);
	m_rect.setSize(sf::Vector2f(width, height));
}

void HitboxComponent::update() { }

bool HitboxComponent::checkIntersect(const sf::FloatRect & collisionRect) {
	return m_rect.getGlobalBounds().intersects(collisionRect);
}


// initializers


// public methods


// accessors&mutators


// private methods

} // namespace EGE
