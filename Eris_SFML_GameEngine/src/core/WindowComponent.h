#pragma once
#include "Core.h"
namespace EGE {

class WindowComponent : public Core {

public:		// constructors
	WindowComponent(sf::RenderWindow* rWindow, bool active = false, int zIndex = 0) 
		: p_rWindow(rWindow), m_active(active), m_zIndex(zIndex) {}

	virtual ~WindowComponent() {}

public:		// public methods
	virtual void render() = 0;

public:		// accessors
	inline bool isActive() const { return m_active; }
	inline void setActive(const bool state) { m_active = state; }

protected:
	int m_zIndex;
	bool m_active;

protected:
	inline sf::RenderWindow& getWindow() const { return *p_rWindow; }
	inline sf::RenderWindow& window() const { return *p_rWindow; }
private:
	sf::RenderWindow* p_rWindow;
};

}
