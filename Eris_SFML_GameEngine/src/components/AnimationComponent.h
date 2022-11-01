#pragma once

namespace EGE {

class AnimationComponent {
public:		// constructors
	AnimationComponent(sf::Sprite* sprite, sf::Texture* textureSheet);
	~AnimationComponent();

private:	// util
	struct Animation : public Core {
		Animation() {
		}

		void initAnimation(sf::Sprite* sprite, int start_x, int start_y, int width, int height, int offset_x, int offset_y, int frames, float animationSpeed, float animationDuration) {
			this->sprite = sprite;
			this->width = width;
			this->height = height;
			this->startRect = sf::IntRect(start_x, start_y, width, height);
			this->currentRect = startRect;
			this->offset = sf::Vector2i(offset_x, offset_y);
			this->totFrames = frames;
			this->rate = animationSpeed;
			this->animationDuration = animationDuration;
			this->sprite->setTextureRect(sf::IntRect(0, 0, width, height));
		}

		void setDuration(const float& time) { animationDuration = time; }
		void setRate(const float& time) { rate = time; }

		void play() {
			timer += rate * dt();
			if (timer >= animationDuration) {
				timer = 0.f;
				currentFrameNo++;
				if (currentFrameNo <= totFrames) {
					currentRect.left += offset.x;
					currentRect.top += offset.y;
				} else {
					currentFrameNo = 0;
					currentRect = startRect;
				}
				sprite->setTextureRect(currentRect);
			}
		}

		void reset() { currentRect = startRect; timer = 0.f; }

		sf::Sprite* sprite = nullptr;
		float animationDuration = 0;
		float timer = 0;
		float rate = 0;
		int width = 0; int height = 0;
		sf::Vector2i offset;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		int currentFrameNo = 0;
		int totFrames = 0;
	};

private:	// initializers

public:		// public methods
	void addAnimation(const std::string& key, int start_x, int start_y, int width, int height, int offset_x, int offset_y, int frames, float animationSpeed, float animationDuration); // addAnimation should be used only in itializers

	inline void play(const std::string& key) {
		m_animationSheet[key].play();
	}

	void playCurrent() {
		m_animation_current->play();
	}

public:		// public members

public:		// accessors&mutators
	void resetCurrent() {
		m_animation_current->reset();
	}
	void setCurrent(const std::string& key) {
		m_animation_current = &m_animationSheet[key];
	}
	void setTextureSheetPtr(sf::Texture* textureSheet) {
		p_textureSheet = textureSheet;
	}

private:	// private members
	std::unordered_map<std::string, Animation> m_animationSheet;
	Animation* m_animation_current;
	sf::Sprite* p_sprite;
	sf::Texture* p_textureSheet;

private:	// private methods

};

} // namespace EGE
