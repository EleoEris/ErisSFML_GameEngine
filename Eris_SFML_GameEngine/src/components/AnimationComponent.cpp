#include "ege_pch.h"
#include "AnimationComponent.h"

namespace EGE {

// constructors
AnimationComponent::AnimationComponent(sf::Sprite* sprite, sf::Texture* textureSheet) 
	: p_sprite(sprite), p_textureSheet(textureSheet) {
	p_sprite->setTexture(*p_textureSheet);
}

AnimationComponent::~AnimationComponent() {
}

void AnimationComponent::addAnimation(const std::string& key,
									  int start_x, int start_y,  int width, int height, int offset_x, int offset_y,
									  int frames, float animationSpeed, float animationDuration) {

	m_animationSheet[key] = Animation();
	m_animationSheet[key].initAnimation(p_sprite, 
										start_x, start_y, width, height, offset_x, offset_y,
										frames, animationSpeed, animationDuration);
	m_animation_current = &m_animationSheet[key];
}


// initializers


// public methods


// accessors&mutators


// private methods

} // namespace EGE
