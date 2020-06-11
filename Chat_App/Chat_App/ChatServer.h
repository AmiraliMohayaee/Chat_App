#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include <string>
#include "TCPConnection.h"


class ChatServer
{
public:
	ChatServer();
	~ChatServer();
	bool Startup(Uint16 port, const char* IP = nullptr);
	void Chat();
	void Update();

	void Shotdown();

private:
	std::string m_sendMsg;
	std::string m_recvMsg;

	TCPConnection* m_connection;
	TCPServer* m_server;
};


#endif