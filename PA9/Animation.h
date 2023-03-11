#pragma once

#include "pa9.h"

class Animation {
private:
	bool mIsFlipped = false;

	unsigned short mAnimationIterator = 1;
	// the gap in frames between two pictures
	unsigned short mAnimationGap = 0;
	unsigned short mCurrentFrame = 0;
	unsigned short mFrameWidth = 1;
	unsigned short mTotalFrames = 0;

	sf::Texture* mMainTexture;

	sf::Sprite* mSpriteSource;

	void loopTexture();

public:
	Animation();

	// getters

	// setters
	void setFlip(bool f);

	// setup animation
	void setUp(string newTexturePath, unsigned short newFrameWidth, unsigned short newAnimationGap);

	void setSpriteSource(sf::Sprite& spriteSource);

	bool isDone();

	void play();

	void update();
};