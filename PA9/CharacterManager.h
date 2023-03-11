#pragma once

#include "BaseCharacter.h"
#include "Monster01.h"
#include "Monster02.h"

class CharacterManager {
private:
public:
	CharacterManager();

	BaseCharacter Generate_Role_1();

	Monster01 Generate_Monster_01();

	Monster02 Generate_Monster_02();
};