#include "CharacterManager.h"

CharacterManager::CharacterManager() {}

BaseCharacter CharacterManager::Generate_Role_1() {
	BaseCharacter role;

	role.addAnimation(IDLE_ANIM, "Assets/Character/role_0_idle.png", 120, 4);
	role.addAnimation(WALK_ANIM, "Assets/Character/role_0_walk.png", 120, 4);
	role.addAnimation(ATK_ANIM, "Assets/Character/role_0_atk.png", 120, 6);
	role.addAnimation(HURT_ANIM, "Assets/Character/role_0_hurt.png", 120, 8);

	role.isPlayer = true;
	role.setStandingHeight(310.f);
	role.setHPMax(3);

	role.afterInit();

	// 380
	role.setPosition(sf::Vector2f(380.f, role.getStandingHeight()));

	return role;
}

Monster01 CharacterManager::Generate_Monster_01() {
	Monster01 role;

	role.addAnimation(IDLE_ANIM, "Assets/Character/role_10_idle.png", 80, 9);

	// 330
	role.setStandingHeight(330.f);
	role.setHPMax(3);

	role.afterInit();

	role.setPosition(sf::Vector2f(500.f, role.getStandingHeight()));

	return role;
}

Monster02 CharacterManager::Generate_Monster_02() {
	Monster02 role;

	role.addAnimation(IDLE_ANIM, "Assets/Character/role_20_idle_1.png", 168, 9);

	role.hpOffset = 80;
	// 330
	role.setStandingHeight(270.f);
	role.setHPMax(3);

	role.afterInit();

	// 1500
	role.setPosition(sf::Vector2f(1500.f, role.getStandingHeight()));

	return role;
}