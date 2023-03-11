#pragma once

#include <vector>
#include "pa9.h"

class LevelManager {
private:
	std::vector<sf::Sprite> allSprite;
	std::vector<sf::Sprite> allAir;
	std::vector<sf::Sprite> allSprite2;

public:
	LevelManager();
	~LevelManager();

	std::vector<sf::Sprite> generate_Level_One();
	std::vector<sf::Sprite> generate_Level_Two();
	void drawAll(sf::RenderWindow& window);
};
