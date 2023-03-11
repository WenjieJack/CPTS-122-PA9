#include "Particle.h"

Particle::Particle(sf::Texture& particleTexture, float duration, sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f scale, float angularVelocity, bool applyGravity, bool ignoreFloorCollission)
{
	mTimeLapse = 0.f;
	mSprite.setTexture(particleTexture);
	mSprite.setOrigin(sf::Vector2f(mSprite.getLocalBounds().width * 0.5f, mSprite.getLocalBounds().height * 0.5f));
	mSprite.setPosition(position);
	mSprite.setRotation(rand() % 360);
	mSprite.setScale(scale);
	mDuration = duration;
	mVelocity = velocity;
	mAngularVelocity = angularVelocity;
	mIsApplyGravity = applyGravity;
	mIsIgnoreFloorCollission = ignoreFloorCollission;
}

Particle::~Particle()
{
	//cout << "Particle Removed: " << mId << endl;
}

bool Particle::operator==(const Particle& test)
{
	return mId == test.mId;
}

bool Particle::update(float deltaTime, float floorHeight)
{
	mSprite.move(mVelocity);
	mSprite.rotate(mAngularVelocity);
	if (mIsApplyGravity)
	{
		mVelocity.y += 9.8f * deltaTime;
		if (!mIsIgnoreFloorCollission && floorHeight <= mSprite.getPosition().y)
		{
			// collission impulse
			mVelocity.y *= -1;
			// drag
			mVelocity.y += 3.0f;
			mVelocity.x += 0 < mVelocity.x ? -1 : 1;
			mAngularVelocity += 0 < mAngularVelocity ? -5 : 5;
			// collissionResponse
			mSprite.setPosition(mSprite.getPosition().x, floorHeight);
		}
	}
	mTimeLapse += deltaTime;
	if (mDuration <= mTimeLapse)
	{
		return true;
	}
	return false;
}

void Particle::draw(sf::RenderWindow& window)
{
	window.draw(mSprite);
}
