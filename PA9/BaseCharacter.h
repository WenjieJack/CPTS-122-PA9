#pragma once

#include "pa9.h"
#include "Animator.h"

class BaseCharacter {
private:
	bool mIsOnGround = true;

	int mMoveRight = 0,// 1 is move right, -1 left, 0 stay
		mHPMax = 0,
		mHP = 0;

	float mStandingHeight = 0.0f,// the y value to stand on floor
		mMovingSpeed = 400.f,// horizontal moving speed
		mGravity = 50.f,
		mVelocityY = 0.f,// velocity will interact with gravity
		mJumpSpeed = -1000.f,// initial jump speed, can control jump height
		halfWidth = 17.f;// the half width of the character, not the sprite, used to not go over screen edge

	sf::Time atkCDTime = sf::seconds(0.f);// the game time when atk is off cool down
	sf::Time hurtCDTime = sf::seconds(0.f);

	// main texture and sprite for this character
	sf::Texture mMainTexture;
	sf::Sprite mMainSprite;

	// hp bar
	sf::Texture mHPBG_Texture;
	sf::Sprite mHPBG_Sprite;
	sf::Texture mHP_Texture;
	sf::Sprite mHP_Sprite;

	// animator class to control how all the animations be organized and played
	Animator mAnimator;

	// sound effect
	sf::SoundBuffer sb_Atk;
	sf::Sound sound_Atk;

public:
	bool isPlayer = false;

	int hpOffset = 40;

	BaseCharacter();

	// getters
	sf::Sprite getMainSprite();
	float getStandingHeight();
	int getHP();

	// setters
	void setStandingHeight(float newData);
	void setHPMax(int value);

	void addAnimation(int typeAnim, string texturePath, unsigned short newFrameWidth, unsigned short newAnimationGap);

	// change current hp value, you can pass in positive or negative integer
	void addHP(int value);

	void afterInit();

	// get the center position of the main sprite
	sf::Vector2f getCenterPosition();

	// set left and top
	void setPosition(sf::Vector2f newPos);
	sf::Vector2f getPosition();
	// another version
	sf::Vector2f getPositionCenter();

	void loadMainTexture(string mainTexturePath);

	void move(int newMoveRight);

	void startJump();

	// handle getting hurt
	void hurt(sf::Time hurtTime, int distance);

	bool isDead();

	virtual bool atk(sf::Time atkTime, std::vector<BaseCharacter*> target);

	void update(float deltaTime);

	void drawAll(sf::RenderWindow& window);

	bool checkCollission(BaseCharacter& target);
};