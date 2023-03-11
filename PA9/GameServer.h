#pragma once

#include <SFML/System/Thread.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>

#include "pa9.h"

class GameServer {
private:
	sf::Thread mThread;
	bool mWaitingThreadEnd;
	sf::TcpListener	mListenerSocket;
	bool mListeningState;

	void executionThread();
	void setListening(bool enable);

	void handleIncomingConnections();

public:
	GameServer();
	~GameServer();
};