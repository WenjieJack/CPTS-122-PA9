/*
	Author: Wenjie Wang, Erfei Yang, Jiaming Chu
	Class: CptS 122, Fall 2022
	Date: Wednesday, December 7, 2022
	Task: Programming Assignment 9

	Description: A Graphical Game or Application
*/

// network implementation try out
//#include <winsock2.h>
//#include <WS2tcpip.h>
//#pragma comment(lib, "ws2_32.lib")
//#pragma warning(disable:4996)
//#define PORT 9999

#include "pa9.h"
#include "LevelManager.h"
#include "CharacterManager.h"
#include "GameServer.h"
#include "ParticleManager.h"

int main() {
	float windowWidth = 800.f, windowHeight = 600.f;

	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode((int)windowWidth, (int)windowHeight, 32), "PA 9", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	// LOADED THE HIT TEXTURES
	sf::Texture t_hit_Effect;
	t_hit_Effect.loadFromFile("Assets/Character/hit_effect.png");
	sf::Texture t_blood_Effect;
	t_blood_Effect.loadFromFile("Assets/Character/role_0_blood.png");

	// load menu texture and sprite
	sf::Texture t_menu1;
	t_menu1.loadFromFile("Assets/Menu/menu1.png");
	sf::Sprite sp_menu1;
	sp_menu1.setTexture(t_menu1);

	// load background music
	sf::Music music_BG;
	music_BG.openFromFile("Assets/Sound/Music_BG.wav");
	music_BG.setVolume(20);
	music_BG.setLoop(true);
	music_BG.play();

	// LOADED THE HURT SOUND
	sf::SoundBuffer sb_hurts;
	sb_hurts.loadFromFile("Assets/Sound/hurt.wav");
	sf::Sound sound_hurts;
	sound_hurts.setBuffer(sb_hurts);

	LevelManager myLevelManager;
	CharacterManager myCharacterManager;

	/*GameServer* myGameServer = nullptr;
	char who;
	std::cout << "Do you want to be a server (s) or a client (c)? ";
	std::cin >> who;
	if (who == 's') {
		myGameServer = new GameServer();
	}
	else {
		sf::IpAddress server("127.0.0.1");
		sf::TcpSocket socket;
		socket.connect(server, ServerPort);
	}*/

	//// network implementation try out
	////initialize the socket and connect to the server
	//WSADATA wsd;
	//WSAStartup(MAKEWORD(2, 2), &wsd);
	//SOCKET SocketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//SOCKADDR_IN  ClientAddr;
	//ClientAddr.sin_family = AF_INET;
	//ClientAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	//ClientAddr.sin_port = htons(PORT);
	//int n = 0;
	//n = connect(SocketClient, (struct sockaddr*)&ClientAddr, sizeof(ClientAddr));
	//if (n == SOCKET_ERROR) {
	//	cout << "Connection Fail" << endl;
	//}
	//else {
	//	con = true;
	//}

	std::vector<sf::Sprite> level_One = myLevelManager.generate_Level_One();
	std::vector<sf::Sprite> level_Two = myLevelManager.generate_Level_Two();
	// create a view with its center and size
	sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(windowWidth, windowHeight));

	// array of all monsters
	std::vector<BaseCharacter*> allMonsters;
	BaseCharacter role_1 = myCharacterManager.Generate_Role_1();
	Monster01 monster_01 = myCharacterManager.Generate_Monster_01();
	allMonsters.push_back(&monster_01);
	Monster02 monster_02 = myCharacterManager.Generate_Monster_02();
	allMonsters.push_back(&monster_02);

	// particle manager
	ParticleManager myParticleManager;
	myParticleManager.setFloorHeight(400.f);
	float deltatime, fps;
	int targetFramerate = 60;

	// load victory texture and sprite
	sf::Texture* t_bg_2_2 = new sf::Texture();
	t_bg_2_2->loadFromFile("Assets/Level_2/bg_2_2.png");
	sf::Sprite sp_bg_2_2;
	sp_bg_2_2.setTexture(*t_bg_2_2);

	int start = 1,
		end = 0,
		curLevel = 1;// current playing level, currently max 2 level
	sf::Clock perFrameClock;
	sf::Clock gameClock;
	int hurt = 0, hurtTime = 0;

	while (window.isOpen()) {
		sf::Event gameEvent;
		while (window.pollEvent(gameEvent)) {
			if (gameEvent.type == sf::Event::Closed) {
				window.close();
				break;
			}
		}

		float deltaTime = perFrameClock.restart().asSeconds();

		if (start) {
			// draw main menu
			window.draw(sp_menu1);
			// press 1 to play the game
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
				start = 0;
			}
			// press 2 to exit
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
				window.close();
				break;
			}
		}
		/*else if (end==1) {
			window.draw(sp_bg_2_2);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
				end = 0;
			}
		}*/
		// after pass the main menu, game starts
		else {
			// if main role is at right side of monster 1
			if (role_1.getCenterPosition().x <= monster_01.getCenterPosition().x + 40 && role_1.getCenterPosition().x >= monster_01.getCenterPosition().x && role_1.getCenterPosition().y > monster_01.getCenterPosition().y + monster_01.getStandingHeight() - 350) {
				hurt = 5;
				hurtTime = 40;
			}
			// else if main role is at left side of monster 1
			else if (role_1.getCenterPosition().x >= monster_01.getCenterPosition().x - 40 && role_1.getCenterPosition().x <= monster_01.getCenterPosition().x && role_1.getCenterPosition().y > monster_01.getCenterPosition().y + monster_01.getStandingHeight() - 350) {
				hurt = -5;
				hurtTime = 40;
			}
			// a timer for the main role, play hitting particle effect when hit a monster
			if (hurtTime == 0) {
				// press x to attack
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
					if (role_1.atk(gameClock.getElapsedTime(), allMonsters) && role_1.checkCollission(monster_01))
					{
						// spawn blood particle effect
						myParticleManager.spawnBloodEffect(t_blood_Effect, monster_01.getCenterPosition(), 20);
						// spawn hit particle effect
						myParticleManager.spawnHitEffect(t_hit_Effect, monster_01.getCenterPosition());
						// slow down
						targetFramerate = 10;
						// play enemy damage sound effect
						sound_hurts.play();
					}
				}
				else {
					// press right arrow to move right
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
						role_1.move(1);
					}

					// press left arrow to move left
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
						role_1.move(-1);
					}

					// press space to jump
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						role_1.startJump();
					}
				}
				targetFramerate += 6;
				if (60 <= targetFramerate)
				{
					targetFramerate = 60;
				}
				window.setFramerateLimit(targetFramerate);

			}
			if (hurt > 0) {
				hurt--;
				role_1.hurt(gameClock.getElapsedTime(), 8);
			}
			if (hurt < 0) {
				hurt++;
				role_1.hurt(gameClock.getElapsedTime(), -8);
			}
			if (hurtTime > 0) {
				hurtTime--;
			}

			//// network implementation try out
			//msgbuffer = (char*)(&move);
			//role_1.update(deltaTime);
			//monster_01.update(deltaTime);
			//int r2 = 0;
			////there should gernerate a new character, but the role_2 cannot be generated;!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//BaseCharacter role_2 = myCharacterManager.Generate_Role_1();
			//// if the current client is connecting to the server;
			//if (con) {
			//	//send the msg to the server
			//	send(SocketClient, msgbuffer, sizeof(msgbuffer), 0);
			//	memset(msgbuffer, 0, sizeof(msgbuffer));
			//	//Receive msg from the server
			//	Sleep(500);
			//	int size = recv(SocketClient, msgbuffer, sizeof(msgbuffer), 0);
			//	memset(msgbuffer, 0, sizeof(msgbuffer));
			//	if ((strcmp(msgbuffer, "end\0") == 0) || size < 0 || size == 0)
			//	{  //set the flag of info of role 2 and its monster as 0
			//		con = 0;
			//	}
			//	else {
			//		// update the info of the other user and its monster
			//		con = 1;

			//	}
			//}

			// necessary update call per frame
			role_1.update(deltaTime);
			monster_01.update(deltaTime);
			monster_02.atk(gameClock.getElapsedTime(), role_1);
			monster_02.updateThrowingKnife(deltaTime, role_1);
			monster_02.update(deltaTime);
			myParticleManager.update(deltaTime);

			// camera following the main role
			// set view's center
			float xRight = 5000;
			/*	if (0) xRight = 950 - windowWidth / 2;
				if (0) xRight = 950 - windowWidth / 2;*/
			if (curLevel == 1) xRight = 950 - windowWidth / 2;
			if (role_1.getCenterPosition().x > 853)
				xRight = 5000;
			if (role_1.getCenterPosition().x > 1750)
				xRight = 1750;
			float x = clamp<float>(role_1.getCenterPosition().x, windowWidth / 2, xRight);
			view.setCenter(x, role_1.getCenterPosition().y);
			// activate it
			window.setView(view);

			window.clear();

			// necessary window.draw call
			myLevelManager.drawAll(window);
			monster_01.drawAll(window);
			monster_02.drawAll(window);
			window.draw(monster_02.getThrowingKnife());
			role_1.drawAll(window);
			myParticleManager.drawAll(window);
		}

		//// network implementation try out
		/*bool exist = true;
		if (con) {
			if (msgbuffer == "1" or msgbuffer == "2") {
				role_2.move(atoi(msgbuffer));
			}
			else if (msgbuffer == "3") {
				role_2.startJump();
			}
			else if (msgbuffer == "4") {
				role_2.atk(gameClock.getElapsedTime());
			}
			else {
				exist = false;
			}
			if (exist) {
				role_2.drawAll(window);
			}

		}*/

		// condition for victory
		if (monster_02.isDead()) {
			sp_bg_2_2.setPosition(role_1.getCenterPosition() - sf::Vector2f(sp_bg_2_2.getGlobalBounds().height / 2, sp_bg_2_2.getGlobalBounds().width / 2));
			sp_bg_2_2.setScale(sf::Vector2f(2.5f, 2.5f));
			window.draw(sp_bg_2_2);
			end = 1;
		}

		window.display();
	}

	return 0;
}