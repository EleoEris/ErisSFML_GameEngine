#include "ege_pch.h"
#include "Button.h"

namespace EGE {

// constructors
Button::Button(sf::RenderWindow* rWindow, 
			   std::string text, int textSize, const sf::Font* font, 
			   std::function<void()> func,
			   float x, float y, 
			   float width, float height,
			   sf::Color mainColor,
			   sf::Color textColor, 
			   bool active, int zIndex) 
	: WindowComponent(rWindow, active, zIndex)
	, m_font(font) {

	bindPressFunction(func);
	m_buttonState = BTN_IDLE;
	m_body.setPosition(sf::Vector2f(x, y));
	m_body.setSize(sf::Vector2f(width, height));
	m_body.setFillColor(mainColor);


#	pragma warning( push )
#	pragma warning( disable : 4244 )	// C4244: possible loss of data
	m_colors[BTN_IDLE] = mainColor;
	m_colors[BTN_HOVER] = sf::Color(
		mainColor.r * 1.2f < 0xff ? mainColor.r * 1.2f : 0xff,
		mainColor.g * 1.2f < 0xff ? mainColor.g * 1.2f : 0xff,
		mainColor.b * 1.2f < 0xff ? mainColor.b * 1.2f : 0xff,
		mainColor.a
	);
	m_colors[BTN_PRESSED] = sf::Color(
		mainColor.r * 0.7f,
		mainColor.g * 0.7f,
		mainColor.b * 0.7f,
		mainColor.a
	);
#	pragma warning( pop )				// C4244: possible loss of data

	m_text.setFont(*m_font);
	m_text.setString(text);
	m_text.setFillColor(textColor);
	m_text.setCharacterSize(textSize);
	m_text.setPosition(
		m_body.getPosition().x + m_body.getGlobalBounds().width  / 2.f - m_text.getGlobalBounds().width  / 2.f,
		m_body.getPosition().y + m_body.getGlobalBounds().height / 2.f - m_text.getGlobalBounds().height / 2.f
	);
}

Button::~Button() {
    
}

void Button::update(sf::Vector2f& mousePos) {
	update_state(mousePos);
}

void Button::update_state(sf::Vector2f & mousePos) {
	if (m_body.getGlobalBounds().contains(mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (m_buttonState != BTN_PRESSED) {
				getPressed();
			}
			return;
		}
		if (m_buttonState != BTN_HOVER)
			startHovering();
	} else if (m_buttonState) {
		startIdling();
	}
}

void Button::render() {
	getWindow().draw(m_body);
	getWindow().draw(m_text);
}

void Button::getPressed() {
	m_buttonState = BTN_PRESSED;
	m_body.setFillColor(m_colors.color_press);
	p_pressFunction();
}

void Button::startHovering() {
	m_buttonState = BTN_HOVER;
	m_body.setFillColor(m_colors.color_hover);
}

void Button::startIdling() {
	m_buttonState = BTN_IDLE;
	m_body.setFillColor(m_colors.color_idle);
}

void Button::bindPressFunction(std::function<void()> func) {
	p_pressFunction = func;
}


// initializers


// public methods


// accessors


// private methods

}
