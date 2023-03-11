#include "Animation.h"

Animation::Animation() {
	mMainTexture = nullptr;
	mSpriteSource = nullptr;
}

// private
void Animation::loopTexture() {
	if (!mIsFlipped) {
		mSpriteSource->setTextureRect(sf::IntRect(mCurrentFrame * mFrameWidth, 0, mFrameWidth, mMainTexture->getSize().y));
	}
	else {
		mSpriteSource->setTextureRect(sf::IntRect((mCurrentFrame+1) * mFrameWidth, 0, -mFrameWidth, mMainTexture->getSize().y));
	}
}

void Animation::setUp(string newTexturePath, unsigned short newFrameWidth, unsigned short newAnimationGap) {
	mIsFlipped = false;
	mAnimationIterator = newAnimationGap;
	mFrameWidth = newFrameWidth;
	mAnimationGap = newAnimationGap;
	mCurrentFrame = 0;

	mMainTexture = new sf::Texture();
	mMainTexture->loadFromFile(newTexturePath);
	mTotalFrames = mMainTexture->getSize().x / mFrameWidth;
	// total frames need at least 1
	if (mTotalFrames == 0) mTotalFrames = 1;
}

void Animation::setSpriteSource(sf::Sprite& spriteSource) {
	mSpriteSource = &spriteSource;
}

void Animation::setFlip(bool f) {
	mIsFlipped = f;
}

bool Animation::isDone() {
	return mAnimationIterator == mAnimationGap && mCurrentFrame == mTotalFrames - 1;
}

void Animation::play() {
	mAnimationIterator = mAnimationGap;
	mCurrentFrame = 0;
	mSpriteSource->setTexture(*mMainTexture);
	loopTexture();
}

void Animation::update() {
	if (mAnimationIterator == mAnimationGap) {
		mAnimationIterator = 0;

		loopTexture();

		mCurrentFrame = (mCurrentFrame + 1) % mTotalFrames;
	}

	mAnimationIterator++;
}