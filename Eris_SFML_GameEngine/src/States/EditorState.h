#pragma once

namespace EGE {

class EditorState : public State {
public:		// constructors
	EditorState(sf::RenderWindow* rWindow, bool active = false, bool rendering = false);
	~EditorState();

	void init();
private:	// initializers
	static void initFonts();
	void initTextures();

public:		// operators

public:		// public methods
	inline void updateWindowSettings();

	void update();
	void render() override;


	void activateState();
	void deactivateState();

public:		// public members

public:		// accessors&mutators

private:	// private members
	bool m_bgActive;
	sf::RectangleShape m_background;
	sf::Color m_background_fade_color;

private:	// private methods
	inline void updateInput() override;
};

} // namespace EGE
