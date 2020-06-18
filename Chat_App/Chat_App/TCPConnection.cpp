#include "TCPConnection.h"
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

	return true;
}

void TCPConnection::Shutdown()
{
	// Setting off SDL and SDL net 
	SDL_Quit();
	SDLNet_Quit();
}

