#include "Monster02.h"

Monster02::Monster02() {
	mTexture_ThrowingKnife.loadFromFile("Assets/Character/ThrowingKnife.png");
	mSprite_ThrowingKnife.setTexture(mTexture_ThrowingKnife);
}

sf::Sprite Monster02::getThrowingKnife() {
	return mSprite_ThrowingKnife;
}

bool Monster02::atk(sf::Time atkTime, BaseCharacter& target) {
	if (!mIsThrowing) {
		if (atkTime >= throwCDTime) {
			/*if (inRange(getCenterPosition().x, target.getCenterPosition().x, 200)) {

			}*/
			mSprite_ThrowingKnife.setPosition(getCenterPosition());
			mThrowedDistance = 0;
			throwCDTime = atkTime + sf::seconds(2.0f);

			mIsThrowing = true;
		}
	}


	return true;
}

void Monster02::updateThrowingKnife(float deltaTime, BaseCharacter& target) {
	if (mIsThrowing) {
		// if the knife is traveling long enough
		if (mThrowedDistance >= 500) {
			mIsThrowing = false;
			mSprite_ThrowingKnife.setPosition(sf::Vector2f(0, 999));
		}
		else {
			float dis = 1 * 400 * deltaTime;
			mSprite_ThrowingKnife.move(sf::Vector2f(-dis, 0.f));
			mThrowedDistance += dis;

			if (inRange(sf::Vector2f(mSprite_ThrowingKnife.getGlobalBounds().left, mSprite_ThrowingKnife.getGlobalBounds().top), target.getCenterPosition(), 5)) {
				target.addHP(-1);
				mIsThrowing = false;
				mSprite_ThrowingKnife.setPosition(sf::Vector2f(0, 999));
			}
		}
	}
}