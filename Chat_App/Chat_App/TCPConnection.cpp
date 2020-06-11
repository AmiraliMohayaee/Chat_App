#include "TCPConnection.h"
#include "ScreenManager.h"
#include <iostream>


TCPConnection::TCPConnection()
{
	m_ip = { 0, 0 };
	m_socket = nullptr;
}

bool TCPConnection::Initialize()
{
	// Initializing all SDL components
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL failed to initialise." << std::endl;
		return false;
	}

	// Initializing SDL net 
	if (SDLNet_Init() == -1)
	{
		std::cout << "SDL Network failed to initialise." << std::endl;
		return false;
	}
}

bool TCPServer::OpenSocket()
{
	// Establishing the server's listerner socket 
	// to prepare for connection with a client
	// This will happen after we assured that the 
	// server is created without errors
	m_socket = SDLNet_TCP_Open(&m_ip);


	if (m_socket == nullptr)
	{
		std::cout << "Could not crete a server's listerner socket." << std::endl;
		Screen->OnWait();
		return false;
	}
	else
	{
		std::cout << "Server socket ready for connection..." << std::endl;
		std::cout << "Awaiting connection..." << std::endl;
		return true;
	}
}

void TCPServer::ListenSocket()
{
	// If connection is possible, the client will
	// attempt to accept the connection with the server
	// every half of second
	while (!m_client)
	{
		m_client = SDLNet_TCP_Accept(m_socket);
		std::cout << ".";
		SDL_Delay(500);
	}

	SDLNet_TCP_Close(m_socket);
	std::cout << std::endl << "Connection established with client." << std::endl;
}

bool TCPServer::Send(const std::string& msg)
{
	int length = msg.length() + 1;

	if (SDLNet_TCP_Send(m_client, msg.c_str(), length) < length)
	{
		std::cout << "Message could not be sent. Possble loss of data." << std::endl;
		return false;
	}
	else
	{
		std::cout << "Message succesfully sent." << std::endl;
		return true;
	}
}

bool TCPServer::Recv(std::string& msg)
{
	// container for storing outgoing server
	// message
	char incomingMsg[2000];

	if (SDLNet_TCP_Recv(m_socket, incomingMsg, 2000) <= 0)
	{
		std::cout << "Could not recieve message from Server.\n" << std::endl;
		return false;
	}
	else
	{
		std::cout << "Message succesfully recieved: " << incomingMsg << std::endl;
		return true;
	}
}

void TCPServer::CloseSocket()
{
	SDLNet_TCP_Close(m_client);
}

void TCPServer::PushClient()
{
}

void TCPServer::PopClient()
{
}

void TCPConnection::Shutdown()
{
	// Setting off SDL and SDL net 
	SDL_Quit();
	SDLNet_Quit();
}

TCPServer::TCPServer()
{
	m_client = nullptr;
}

bool TCPServer::Init(Uint16 port, const char* IPAddress)
{
	if (SDLNet_ResolveHost(&m_ip, nullptr, port) == -1)
	{
		std::cout << "Failed to create a server." << std::endl;
		Screen->OnWait();
		return false;
	}
	else
	{
		return true;
	}
}
