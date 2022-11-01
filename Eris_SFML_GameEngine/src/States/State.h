#pragma once
#include "EGE.h"
#include "Utility/Button.h"
#include "States/StatesEnum.h"

namespace EGE {

class State : public WindowComponent {
public:		// constructors
	State(sf::RenderWindow* rWindow, StatesEnum::StatesEnum id,
		  bool active = false, bool rendering = false);
	virtual ~State() {};

	static void setKeyBindsPtr(std::unordered_map<std::string, int16_t>* keybinds) {
		Log::Get().assert_(__FUNCTION__, __LOG_FILENAME__, __LINE__, p_keyBinds, "TRIED TO CHANGE DT POINTER"); 
		if (p_keyBinds) __debugbreak();
		p_keyBinds = keybinds;
	}
protected:	// initializers
	virtual void initFonts();
	virtual void initTextures();

public:		// operators

public:		// public methods
	virtual void update() = 0;
	virtual void updateWindowSettings() = 0;

	virtual inline void activateState() = 0;
	virtual inline void deactivateState() = 0;
	virtual inline void deactivateState(StatesEnum::StatesEnum nextState) {
		m_nextState = nextState; 
		deactivateState();
	}

public:		// public members
	const StatesEnum::StatesEnum id;
	
public:		// accessors&mutators
	inline bool isRendering() const { return m_rendering; }
	inline void setRendering(const bool& state) { m_rendering = false; }

	inline StatesEnum::StatesEnum getNextState() { return m_nextState; }

	inline const int16_t& getKeyBind(std::string key) const		{ return p_keyBinds->at(key); }
	inline const sf::Texture& getTexture(std::string key) const		{ return m_textures.at(key); }
	inline const sf::Font& getFont(std::string key) const			{ return m_fonts.at(key);}

protected:	// protected members
	StatesEnum::StatesEnum m_nextState;
	std::unordered_map<std::string, sf::Texture>& getTextures() { return m_textures; }
private:
	std::unordered_map<std::string, sf::Texture> m_textures; // contains the most basic textures, don't overuse!
	std::unordered_map<std::string, sf::Font> m_fonts;

protected:	// private members
	std::vector<Button> m_buttons;						//>// check if this is the best structure

	//sf::Vector2i m_mousePosScreen;
	sf::Vector2i m_mousePosWin;
	sf::Vector2f m_mousePosView;

	bool m_rendering;
	bool m_inBackground;
private:
	static std::unordered_map<std::string, int16_t>* p_keyBinds;	//>// Char array?

protected:	// private methods
	virtual void addFont(std::string name, std::string path) final;
	virtual void addTexture(std::string name, std::string path) final;

	virtual inline void updateInput() = 0;
	virtual inline void updateMousePos();
	virtual inline void updateButtons();

	virtual inline void renderButtons();



#	ifdef EGE_DEBUG
	sf::Text D_mousePosText;
	sf::Text D_fps;
	sf::Text D_ups; //updates per second
	void D_initDebug() {
		D_mousePosText.setFont(m_fonts["monospace_elegant"]);
		D_mousePosText.setCharacterSize(16);
		D_fps.setFont(m_fonts["monospace_elegant"]);
		D_fps.setCharacterSize(20);
		D_fps.setOutlineThickness(1);
		D_fps.setOutlineColor(sf::Color::Black);
		D_fps.setFillColor(sf::Color::Green);
		D_fps.setPosition(10, 10);
	}

	inline void D_showFps() {
		D_fps.setString(
			std::to_string(
				(int)(1/dt())
			)
		);
		getWindow().draw(D_fps);
	}

	inline void D_showUps() {
		D_fps.setString(
			std::to_string(
			(int)(1/dt())
			)
		);
		getWindow().draw(D_ups);
	}

	inline void D_showMousePos() {
		D_mousePosText.setPosition(
			m_mousePosView.x - D_mousePosText.getLocalBounds().width,
			m_mousePosView.y - D_mousePosText.getLocalBounds().height - 10
		);
		D_mousePosText.setString("(" + std::to_string((int)m_mousePosView.x) + ", " + std::to_string((int)m_mousePosView.y) + ")");
		getWindow().draw(D_mousePosText);
	}

	inline void D_renderDebug() {
		D_showFps();
		D_showMousePos();
	}
#	endif
};

}
