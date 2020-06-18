#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include <string>
#include <thread>
#include "TCPServer.h"
#include <mutex>

class ChatServer
{
public:
	ChatServer();
	~ChatServer();

	bool Startup(Uint16 port, const char* IP = nullptr);
	void Chat();

	void SendingMsg();
	void RecievingMsg();
	void ListenForClients();

	bool RetryConnection();

	void Shutdown();

private:
	std::string m_sendMsg;
	std::string m_recvMsg;

	// Flag for checking if a client is typing
	bool m_isTyping;

	TCPServer* m_server;

	std::mutex m_lock;
	std::thread SendThread;
	std::thread RecvThread;
	std::thread ListenThread;
};


#endif