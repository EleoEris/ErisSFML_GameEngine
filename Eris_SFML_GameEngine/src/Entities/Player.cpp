#include "ege_pch.h"
#include "Player.h"

namespace EGE {

// constructors
Player::Player(sf::RenderWindow* rWindow, float x, float y, sf::Texture* textureSheet) 
	: Character(rWindow, x, y, textureSheet, true) {
	// init physics
	m_physics.setWalkAcceleration(100);
}

Player::~Player() {
}

void Player::update() {
	PROFILE_HERE;
	Character::update();
}

void Player::render() {
	PROFILE_HERE;
	Character::render();
}



inline void Player::updatePhysics() {
}


// initializers


// public methods


// accessors&mutators


// private methods

}
