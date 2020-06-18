#include "ChatServer.h"
#include "ScreenManager.h"
#include <iostream>


ChatServer::ChatServer()
{
	m_sendMsg = "";
	m_recvMsg = "";

	m_isTyping = false;

	m_server = new TCPServer();
}

ChatServer::~ChatServer()
{
	delete m_server;
}

bool ChatServer::Startup(Uint16 port, const char* IP)
{
	if (!m_server->Initialize())
	{
		std::cout << "Failed to initialize SDL." << std::endl;
		return false;
	}

	if (!m_server->Init(port, IP))
	{
		std::cout << "Failed to Create Server." << std::endl;

		RetryConnection();
		if (RetryConnection() == false)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	if (!m_server->OpenSocket())
	{
		return false;
	}

	// Creating thread for listener

	if (!m_server->ListenSocket())
	{
		return false;
	}
}


void ChatServer::Chat()
{
	// Setting up threading for send and recieve
	ListenThread = std::thread(&ChatServer::ListenForClients, this);
	SendThread = std::thread(&ChatServer::SendingMsg, this);
	RecvThread = std::thread(&ChatServer::RecievingMsg, this);
	ListenThread.detach();
	SendThread.detach();
	RecvThread.detach();

	m_server->ClientList();

	// If user hasn't typed in 'end' in chat, then it will
	// continously loop
	bool isChatActive = true;

	while (isChatActive)
	{
		if (m_sendMsg == "end")
		{
			isChatActive = false;
		}
	}
}

void ChatServer::SendingMsg()
{
	while (m_sendMsg != "end")
	{
		// Enter a message into chat
		std::cout << ">";
		std::getline(std::cin, m_sendMsg);
		// Send message to client
		
		//std::lock_guard<std::mutex> lock(m_lock);
		m_server->Send(m_sendMsg);
		SDL_Delay(500);
	}

	std::cout << "Server Exited the chat application. Shutting down..." << std::endl;
}

void ChatServer::RecievingMsg()
{
			
	while (m_recvMsg != "end")
	{
		SDL_Delay(500);
		//std::lock_guard<std::mutex> lock(m_lock);
		// Receive message from client
		m_server->Recv();
		m_recvMsg = m_server->GetRecvMsg();
		std::cout << m_recvMsg << std::endl;
	}

	std::cout << "Client Exited the chat application. Shutting down..." << std::endl;
}

void ChatServer::ListenForClients()
{
	// At this point we'll assume if we 
	// could open the socket, then we can
	// start listening
	while (true)
	{
		m_server->ListenSocket();
	}
}

bool ChatServer::RetryConnection()
{
	// Closing a socket in case one was opened
	m_server->CloseSocket();

	char answer = NULL;

	std::cout << "Would you like to retry connection? Y/N?";
	
	std::cin >> answer;
	if (answer == 'Y')
	{
		std::cout << "Resetting Server Connection..." << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

void ChatServer::Shutdown()
{
	if (ListenThread.joinable())
	{
		ListenThread.join();
	}

	/// This is if a thread is not detached
	if (SendThread.joinable())
	{
		SendThread.join();
	}
	if (RecvThread.joinable())
	{
		RecvThread.join();
	}

	m_server->CloseSocket();
	m_server->Shutdown();
}