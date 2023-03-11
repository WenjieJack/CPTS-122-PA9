#include "GameServer.h"

GameServer::GameServer()
	: mThread(&GameServer::executionThread, this)
	, mWaitingThreadEnd(false)
	, mListeningState(false)
{
	mListenerSocket.setBlocking(false);
	//mPeers[0].reset(new RemotePeer());
	mThread.launch();
}

GameServer::~GameServer()
{
	mWaitingThreadEnd = true;
	mThread.wait();
}

// private
void GameServer::executionThread() {
	setListening(true);

	while (!mWaitingThreadEnd)
	{
		//handleIncomingPackets();
		handleIncomingConnections();

		// Sleep to prevent server from consuming 100% CPU
		sf::sleep(sf::milliseconds(100));
	}
}

// private
void GameServer::setListening(bool enable)
{
	// Check if it isn't already listening
	if (enable)
	{
		if (!mListeningState) {
			mListeningState = (mListenerSocket.listen(ServerPort) == sf::TcpListener::Done);
			cout << "Server IP is " << sf::IpAddress::getLocalAddress() << endl;
			cout << "Server is listening to port " << ServerPort << ", waiting for connections... " << endl << endl;
		}
	}
	else
	{
		mListenerSocket.close();
		mListeningState = false;
	}
}

// private
void GameServer::handleIncomingConnections() {
	if (!mListeningState)
		return;

	sf::TcpSocket socket;
	if (mListenerSocket.accept(socket) == sf::TcpListener::Done) {
		std::cout << "Client connected: " << socket.getRemoteAddress() << std::endl;
	}
}