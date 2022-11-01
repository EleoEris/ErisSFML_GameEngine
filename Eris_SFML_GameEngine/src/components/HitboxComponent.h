#pragma once

namespace EGE {

struct HitboxComponent : public Core {
	HitboxComponent();
	~HitboxComponent();

	void setRect(sf::FloatRect& rect);
	void setRect(const float& left, const float& top, const float& width, const float& height);
	
	void update();
	void move(const sf::Vector2f& vel) { m_rect.move(vel); }

	sf::RectangleShape& rect() { return m_rect; }
	void setOutlineColor(sf::Color& color) { m_rect.setOutlineColor(color); }
	bool checkIntersect(const sf::FloatRect& collisionRect);
private:
	sf::RectangleShape m_rect;
};

} // namespace EGE
