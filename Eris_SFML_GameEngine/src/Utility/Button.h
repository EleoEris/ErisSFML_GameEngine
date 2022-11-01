#pragma once

namespace EGE {

class Button 
	: public WindowComponent {
public:		// constructors
	Button(sf::RenderWindow* rWindow, 
		   std::string text, int textSize, const sf::Font* font,
		   std::function<void()> func,
		   float x, float y, 
		   float width, float height,
		   sf::Color mainColor,
		   sf::Color textColor,
		   bool active = true, int zIndex = 100);
	~Button();

private:	// initializers

public:		// public methods
	void update(sf::Vector2f& mousePos);

	void render();
	inline void getPressed();
	inline void startHovering();
	inline void startIdling();

public:		// public members
	enum ButtonState : unsigned int { BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED }; // 0 means idle, might use as bool

public:		// accessors
	ButtonState inline getState() { return m_buttonState; };
	bool inline isPressed() { return m_buttonState == BTN_PRESSED; }
	void bindPressFunction(std::function<void()> func);

private:	// private members
	ButtonState m_buttonState;
	sf::RectangleShape m_body;
	const sf::Font* m_font;
	sf::Text m_text;
	std::function<void()> p_pressFunction;

	struct Colors {
		Colors() {}

		union {
			sf::Color colors[3];
			struct {
				sf::Color color_idle;
				sf::Color color_hover;
				sf::Color color_press;
			};
		};


		sf::Color& operator[] (const int state) {
			return colors[state];
		}
	} m_colors;

private:	// private methods
	void update_state(sf::Vector2f& mousePos);

};

}
