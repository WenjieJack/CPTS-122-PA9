#pragma once


#include <vector>
#include "pa9.h"

class Particle
{
private:
	float mTimeLapse;
	float mDuration;
	sf::Sprite mSprite;
	sf::Vector2f mVelocity;
	float mAngularVelocity;
	bool mIsApplyGravity;
	bool mIsIgnoreFloorCollission;
public:
	Particle(sf::Texture& particleTexture, float duration, sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f scale, float angularVelocity, bool applyGravity, bool ignoreFloorCollission);
	~Particle();
	bool operator== (const Particle& test);
	bool update(float deltaTime, float floorHeight);
	void draw(sf::RenderWindow& window);
public:
	int mId;
};

