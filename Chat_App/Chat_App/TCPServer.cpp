#include "TCPServer.h"
#include <iostream>
#include <chrono>

TCPServer::TCPServer()
{
	//m_client = nullptr;

	m_clientSockets;
}

TCPServer::~TCPServer()
{
	m_clientSockets.clear();
}


bool TCPServer::Init(Uint16 port, const char* IPAddress)
{
	if (SDLNet_ResolveHost(&m_ip, nullptr, port) == -1)
	{
		std::cout << "Failed to create a server." << std::endl;
		return false;
	}
	else
	{
		return true;
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
		return false;
	}
	else
	{
		std::cout << "Server socket ready for connection..." << std::endl;
		std::cout << "Awaiting connection..." << std::endl;
		return true;
	}
}


bool TCPServer::ListenSocket()
{
	TCPsocket tempSock = nullptr;

	// If connection is possible, the client will
	// attempt to accept the connection with the server
	// every half of second
	while (!tempSock)
	{
		tempSock = SDLNet_TCP_Accept(m_socket);
		//std::cout << ".";
		SDL_Delay(500);
	}

	std::cout << std::endl << "Connection established with a client." << std::endl;
	//m_client = tempSock;

	// If there are multiple clients, we can push
	// new ones after every successful attempt
	PushClient(tempSock);

	return true;
}


bool TCPServer::Send(const std::string& msg)
{
	int length = msg.length() + 1;

	if (SDLNet_TCP_Send(m_clientSockets.back(), msg.c_str(), length) < length)
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


bool TCPServer::Recv()
{
	// container for storing outgoing server
	// message
	char incomingMsg[100];

	if (SDLNet_TCP_Recv(m_clientSockets.back(), incomingMsg, 100) <= 0)
	{
		//std::cout << "Could not recieve message from Client.\n" << std::endl;
		return false;
	}
	else
	{
		m_recvMsg = incomingMsg;
		//std::cout << "Message succesfully recieved: " << incomingMsg << std::endl;
		return true;
	}
}

void TCPServer::CloseSocket()
{
	SDLNet_TCP_Close(m_client);
}

void TCPServer::PushClient(const TCPsocket& sock)
{
	m_clientSockets.push_back(sock);
}

void TCPServer::RemoveClient(const TCPsocket& sock)
{
	m_clientSockets.remove(sock);
	CloseSocket();
}

void TCPServer::ClientList()
{
	// This can be a bit expensive
	for (unsigned i = 0; i < m_clientSockets.size(); i++)
	{
		std::cout << "Client " << i << " is a connected user on the list."
			<< std::endl;
	}

	std::cout << "There are " << m_clientSockets.size() << " users connected" << std::endl;
	std::cout << "Server can hold a max number of " << m_clientSockets.max_size() <<
		"users." << std::endl;
}

bool TCPServer::TimeOutCount()
{
	// Setting up counter for resetting or aborting
	// connection attempt if it takes too long
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	if ((end - begin).count() / 10000)
	{
		std::cout << "Connection Timed out" << std::endl;
		return false;
	}

	return true;
}

const std::string TCPServer::GetSentMsg()
{
	return m_sendMsg;
}

const std::string TCPServer::GetRecvMsg()
{
	return m_recvMsg;
}
