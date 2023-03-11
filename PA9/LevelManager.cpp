#include "LevelManager.h"

LevelManager::LevelManager() {}
LevelManager::~LevelManager() {}

std::vector<sf::Sprite> LevelManager::generate_Level_One() {
	
	sf::Texture* t_bg_1_0=new sf::Texture();
	t_bg_1_0->loadFromFile("Assets/Level_1/bg_1_0.png");
	sf::Sprite sp_bg_1_0;
	sp_bg_1_0.setTexture(*t_bg_1_0);
	sp_bg_1_0.setScale(sf::Vector2f(10.f, 10.f));
	sp_bg_1_0.setPosition(sf::Vector2f(0.f, -399.f));
	allSprite.push_back(sp_bg_1_0);

	sf::Texture* t_bg_1_1 = new sf::Texture();
	t_bg_1_1->loadFromFile("Assets/Level_1/bg_1_1.png");
	sf::Sprite sp_bg_1_1;
	sp_bg_1_1.setTexture(*t_bg_1_1);
	sp_bg_1_1.setPosition(sf::Vector2f(0.f, 260.f));
	allSprite.push_back(sp_bg_1_1);

	sf::Texture* t_bg_1_1b = new sf::Texture();
	t_bg_1_1b->loadFromFile("Assets/Level_1/bg_1_1.png");
	sf::Sprite sp_bg_1_1b;
	sp_bg_1_1b.setTexture(*t_bg_1_1b);
	sp_bg_1_1b.setPosition(sf::Vector2f(1000.f, 120.f));
	allSprite.push_back(sp_bg_1_1b);

	

	
	

	sf::Texture* t_bg_1_2=new sf::Texture();
	t_bg_1_2->loadFromFile("Assets/Level_1/bg_1_2.png");
	//sf::Texture* t_bg_1_2a = new sf::Texture();
	//t_bg_1_2->loadFromFile("Assets/Level_1/bg_1_2a.png");


	for (int i = 1; i <= 30;i++) {
		sf::Sprite sp_bg_1_2;
		sp_bg_1_2.setTexture(*t_bg_1_2);
		sp_bg_1_2.setPosition(sf::Vector2f(-50.f + i * 50, 400.f));
		sf::Sprite sp_bg_1_2a;
		//sp_bg_1_2a.setTexture(*t_bg_1_2a);
		//sp_bg_1_2a.setPosition(sf::Vector2f(-50.f + i * 135, 500.f));
		allSprite.push_back(sp_bg_1_2);
		//allSprite.push_back(sp_bg_1_2a);
	}


	return allSprite;
}
std::vector<sf::Sprite> LevelManager::generate_Level_Two() {
	sf::Texture* t_bg_2_0 = new sf::Texture();
	t_bg_2_0->loadFromFile("Assets/Level_2/bg_2_0.png");
	sf::Sprite sp_bg_2_0;
	sp_bg_2_0.setTexture(*t_bg_2_0);
	//sp_bg_2_0.setScale(sf::Vector2f(0.f, 0.f));
	sp_bg_2_0.setPosition(sf::Vector2f(950.f, -90.f));
	allSprite.push_back(sp_bg_2_0);

	sf::Texture* t_bg_2_0b = new sf::Texture();
	t_bg_2_0b->loadFromFile("Assets/Level_2/bg_2_0.png");
	sf::Sprite sp_bg_2_0b;
	sp_bg_2_0b.setTexture(*t_bg_2_0b);
	//sp_bg_2_0.setScale(sf::Vector2f(0.f, 0.f));
	sp_bg_2_0b.setPosition(sf::Vector2f(1750.f, -90.f));
	allSprite.push_back(sp_bg_2_0b);

	sf::Texture* t_bg_2_0c = new sf::Texture();
	t_bg_2_0c->loadFromFile("Assets/Level_2/bg_2_0b.png");
	sf::Sprite sp_bg_2_0c;
	sp_bg_2_0c.setTexture(*t_bg_2_0c);
	//sp_bg_2_0.setScale(sf::Vector2f(0.f, 0.f));
	sp_bg_2_0c.setPosition(sf::Vector2f(1750.f, -345.f));
	allSprite.push_back(sp_bg_2_0c);

	sf::Texture* t_bg_2_0c2 = new sf::Texture();
	t_bg_2_0c2->loadFromFile("Assets/Level_2/bg_2_0b.png");
	sf::Sprite sp_bg_2_0c2;
	sp_bg_2_0c2.setTexture(*t_bg_2_0c2);
	//sp_bg_2_0.setScale(sf::Vector2f(0.f, 0.f));
	sp_bg_2_0c2.setPosition(sf::Vector2f(950.f, -345.f));
	allSprite.push_back(sp_bg_2_0c2);

	sf::Texture* t_bg_2_1 = new sf::Texture();
	t_bg_2_1->loadFromFile("Assets/Level_2/bg_2_1.png");
	sf::Sprite sp_bg_2_1;
	sp_bg_2_1.setTexture(*t_bg_2_1);
	//sp_bg_2_0.setScale(sf::Vector2f(0.f, 0.f));
	sp_bg_2_1.setPosition(sf::Vector2f(853.f, 315.f));
	allSprite.push_back(sp_bg_2_1);

	return allSprite;
}

void LevelManager::drawAll(sf::RenderWindow& window) {

	for (int i = 0; i < allSprite.size(); i++)
	{
		window.draw((allSprite[i]));
	}
}

