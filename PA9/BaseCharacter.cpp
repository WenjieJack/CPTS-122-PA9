#include "BaseCharacter.h"

BaseCharacter::BaseCharacter() {
	// load hp bar background and hp bar
	mHPBG_Texture.loadFromFile("Assets/Character/health bar bg.png");
	mHPBG_Sprite.setTexture(mHPBG_Texture);
	mHP_Texture.loadFromFile("Assets/Character/health bar.png");
	mHP_Sprite.setTexture(mHP_Texture);
	mHPBG_Sprite.setScale(sf::Vector2f(0.6f, 0.6f));
	mHP_Sprite.setScale(sf::Vector2f(0.6f, 0.6f));

	// load attack sound
	sb_Atk.loadFromFile("Assets/Sound/Sound_0_Atk.wav");
	sound_Atk.setBuffer(sb_Atk);
}

// getters
sf::Sprite BaseCharacter::getMainSprite() {
	return mMainSprite;
}

float BaseCharacter::getStandingHeight() {
	return mStandingHeight;
}

int BaseCharacter::getHP() {
	return mHP;
}

// setters
void BaseCharacter::setStandingHeight(float newData) {
	mStandingHeight = newData;
}

void BaseCharacter::setHPMax(int value) {
	mHPMax = value;
	mHP = mHPMax;
}

void BaseCharacter::addAnimation(int typeAnim, string texturePath, unsigned short newFrameWidth, unsigned short newAnimationGap) {
	Animation anim;
	anim.setUp(texturePath, newFrameWidth, newAnimationGap);
	anim.setSpriteSource(mMainSprite);
	mAnimator.add(typeAnim, anim);
}

// change current hp value, you can pass in positive or negative integer
void BaseCharacter::addHP(int value) {
	mHP = mHP + value;
	float t = mHP * 1.f / mHPMax;
	//mHP_Sprite.setScale(sf::Vector2f(0.6f * (t), 0.6f));
	mHP_Sprite.scale(sf::Vector2f(t, 1));

	if (!isPlayer && isDead()) {
		mMainSprite.setPosition(sf::Vector2f(0, 30000));
		mStandingHeight = 30000;
	}
}

void BaseCharacter::afterInit() {
	mAnimator.play(IDLE_ANIM, true);
}

// get the center position of the main sprite
sf::Vector2f BaseCharacter::getCenterPosition() {
	sf::FloatRect bound = mMainSprite.getGlobalBounds();

	sf::Vector2f centerPosition(bound.left + bound.width / 2, bound.top + bound.height / 2);

	return centerPosition;
}

sf::Vector2f BaseCharacter::getPosition()
{
	return mMainSprite.getPosition();
}

// another version
sf::Vector2f BaseCharacter::getPositionCenter()
{
	sf::Vector2f _return = getPosition();
	_return.x += mMainSprite.getGlobalBounds().width / 2;
	_return.y += mMainSprite.getGlobalBounds().height / 2;
	return _return;
}

void BaseCharacter::setPosition(sf::Vector2f newPos) {
	mMainSprite.setPosition(newPos);
}

void BaseCharacter::loadMainTexture(string mainTexturePath) {
	mMainTexture.loadFromFile(mainTexturePath);

	mMainSprite.setTexture(mMainTexture);
}

void BaseCharacter::move(int newMoveRight) {
	mMoveRight = newMoveRight;
}

void BaseCharacter::startJump() {
	if (mIsOnGround) {
		mIsOnGround = false;
		mVelocityY = mJumpSpeed;
	}
}

bool BaseCharacter::atk(sf::Time atkTime, std::vector<BaseCharacter*> target) {
	if (atkTime > atkCDTime) {
		mAnimator.play(ATK_ANIM, false);
		sound_Atk.play();
		atkCDTime = atkTime + sf::seconds(0.4f);

		for (int i = 0; i < target.size(); i++)
		{
			if (inRange(getCenterPosition(), target[i]->getCenterPosition(), 100)) {
				target[i]->addHP(-1);
			}
		}
		return true;
	}
	return false;
}

void BaseCharacter::hurt(sf::Time hurtTime, int distance) {
	if (hurtTime > hurtCDTime) {
		addHP(-1);
		hurtCDTime = hurtTime + sf::seconds(0.7f);
	}
	//sf::sleep(sf::seconds(0.1f));

	mAnimator.play(HURT_ANIM, true);
	sound_Atk.play();
	float x = mMainSprite.getGlobalBounds().left + distance;
	mMainSprite.setPosition(sf::Vector2f(x, mStandingHeight));
	//sf::sleep(sf::seconds(0.1f));
	mAnimator.play(HURT_ANIM, false);
}

bool BaseCharacter::isDead() {
	return mHP <= 0;
}

void BaseCharacter::update(float deltaTime) {
	if (!mIsOnGround) {
		mVelocityY += mGravity;
		mMainSprite.move(sf::Vector2f(0.f, mVelocityY * deltaTime));
	}

	if (getCenterPosition().y - mMainSprite.getGlobalBounds().height / 2 > mStandingHeight) {
		float x = mMainSprite.getGlobalBounds().left;
		mMainSprite.setPosition(sf::Vector2f(x, mStandingHeight));
		mVelocityY = 0.f;
		mIsOnGround = true;
	}

	if (mMoveRight != 0) {
		float checkLeft = getCenterPosition().x - halfWidth + mMoveRight * mMovingSpeed * deltaTime;
		float checkRight = getCenterPosition().x + halfWidth + mMoveRight * mMovingSpeed * deltaTime;
		if (checkLeft > 0 && checkRight < (950 + 804+400)) {
			mMainSprite.move(sf::Vector2f(mMoveRight * mMovingSpeed * deltaTime, 0.f));
		}
		mAnimator.isFlipped = mMoveRight == 1;
		mAnimator.play(WALK_ANIM, false);
	}

	mMoveRight = 0;

	mAnimator.update();

	sf::Vector2f pos_HP = sf::Vector2f(getCenterPosition().x - mHPBG_Sprite.getGlobalBounds().width / 2, getCenterPosition().y - hpOffset);
	mHPBG_Sprite.setPosition(pos_HP);
	mHP_Sprite.setPosition(pos_HP);
}

void BaseCharacter::drawAll(sf::RenderWindow& window) {
	window.draw(mHPBG_Sprite);
	window.draw(mHP_Sprite);
	window.draw(mMainSprite);
}

bool BaseCharacter::checkCollission(BaseCharacter& target)
{
	bool dir = 0 < (target.getPositionCenter().x - getCenterPosition().x);
	return target.getMainSprite().getGlobalBounds().intersects(mMainSprite.getGlobalBounds()) && dir == mAnimator.isFlipped;
}