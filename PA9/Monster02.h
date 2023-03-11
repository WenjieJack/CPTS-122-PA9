#pragma once

#include "BaseCharacter.h"

class Monster02 : public BaseCharacter {
private:
	bool mIsThrowing = false;

	float mThrowedDistance = 0.0f;

	sf::Texture mTexture_ThrowingKnife;
	sf::Sprite mSprite_ThrowingKnife;

	sf::Time throwCDTime = sf::seconds(0.f);

public:
	Monster02();

	sf::Sprite getThrowingKnife();

	bool atk(sf::Time atkTime, BaseCharacter& target);

	void updateThrowingKnife(float deltaTime, BaseCharacter& target);
};