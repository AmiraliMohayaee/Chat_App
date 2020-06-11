#include "ChatServer.h"
#include "ScreenManager.h"
#include <iostream>


ChatServer::ChatServer()
{
	m_sendMsg = nullptr;
	m_recvMsg = nullptr;

	m_connection = new TCPConnection();
	m_server = new TCPServer();
}

ChatServer::~ChatServer()
{
	delete m_connection;
	delete m_server;
}

bool ChatServer::Startup(Uint16 port, const char* IP)
{
	if (!m_connection->Initialize())
	{
		std::cout << "Failed to initialize SDL." << std::endl;
		return false; 
	}

	if (!m_server->Init(port, IP))
	{
		std::cout << "Failed to Create Server." << std::endl;
		return false;
	}

	if (!m_server->OpenSocket())
	{
		return false;
	}
	
	// At this point we'll assume if we 
	// could open the socket, then we can
	// start listening
	m_server->ListenSocket();
}

void ChatServer::Update()
{

	Chat();

	// Anything
}

void ChatServer::Chat()
{
	std::string message;
	message = "Hello and welcome to the chat app, est. 1989";

	m_server->Send(message);

	while (m_sendMsg != "end" && m_recvMsg != "end")
	{
		if (m_sendMsg.empty() && m_recvMsg.empty())
		{
			//m_server->Send();
		}
		else
		{
			//m_server->Recv();
		}
		//receive message from other computer
		//display message
		//prompt user to enter a message
		//send message to other computer
	}
}

void ChatServer::Shotdown()
{
	m_server->CloseSocket();
	m_connection->Shutdown();
}
