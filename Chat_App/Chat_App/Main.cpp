#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_net.h>


/////////////////////////////////////
//	Server-side code
/////////////////////////////////////


std::string message;


IPaddress ip;

TCPsocket listenSocket = nullptr;
TCPsocket clientSocket = nullptr;


bool Initialize()
{
	// Initializing all SDL components
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL failed to initialise." << std::endl;
		return 0;
	}

	// Initializing SDL net 
	if (SDLNet_Init() == -1)
	{
		std::cout << "SDL Network failed to initialise." << std::endl;
		return 0;
	}

	return true;
}

void Shutdown()
{
	// Setting off SDL and SDL net 
	SDL_Quit();
	SDLNet_Quit();
}



int main(int argc, char* argv[])
{

	if (!Initialize())
	{
		return 0;
	}
		

	// 
	if (SDLNet_ResolveHost(&ip, nullptr, 1234) == -1)
	{
		std::cout << "Failed to create a server." << std::endl;
		system("pause");
		return 0;
	}

	// Establishing the server's listerner socket 
	// to prepare for connection with a client
	// This will happen after we assured that the 
	// server is created without errors
	listenSocket = SDLNet_TCP_Open(&ip);


	if (listenSocket == nullptr)
	{
		std::cout << "Could not crete a server's listerner socket." << std::endl;
		system("pause");
		return 0;
	}

	std::cout << "Server socket ready for connection..." << std::endl;
	std::cout << "Awaiting connection..." << std::endl;


	// If connection is possible, the client will
	// attempt to accept the connection with the server
	// every half of second
	while (!clientSocket)
	{
		clientSocket = SDLNet_TCP_Accept(listenSocket);
		std::cout << ".";
		SDL_Delay(500);
	}

	SDLNet_TCP_Close(listenSocket);
	std::cout << "Connection established with client." << std::endl;


	message = "Hello and welcome to the chat app, est. 1989";

	int length = message.length() + 1;

	if (SDLNet_TCP_Send(clientSocket, message.c_str(), length) < length)
	{
		std::cout << "Message could not be sent. Possble loss of data." << std::endl;
	}
	else
	{
		std::cout << "Message succesfully sent." << std::endl;
	}


	SDLNet_TCP_Close(clientSocket);

	Shutdown();

	system("Pause");
	return 0;
}