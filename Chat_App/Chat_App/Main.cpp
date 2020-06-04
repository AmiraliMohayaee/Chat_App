#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_net.h>


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
	Initialize();

	// 
	if (SDLNet_ResolveHost(&ip, "www.google.com", 80) == -1)
	{
		std::cout << "Failed to make connection to website." << std::endl;
		return 0;   
	}
	else
	{
		// Convert the port to the correct endianness
		Uint8* port = reinterpret_cast<Uint8*>(&ip.port);

		std::cout << "Port num in NBO is: " << ip.port << std::endl;
		std::cout << "Port number in correct endian: " << static_cast<unsigned int>(port[1]) << std::endl;

		Uint8* iphost = reinterpret_cast<Uint8*>(&ip.host);

		std::cout << "The IPV4 address of the host is: " << static_cast<unsigned int>(iphost[0]) << ".";
		std::cout << static_cast<unsigned int>(iphost[1]) << ".";
		std::cout << static_cast<unsigned int>(iphost[2]) << ".";
		std::cout << static_cast<unsigned int>(iphost[3]) << std::endl;
	}

	clientSocket = SDLNet_TCP_Open(&ip);

	if (clientSocket == nullptr)
	{
		std::cout << "Could not open clientSocket" << std::endl;
		return 0;
	}
	else
	{
		message = "GET /HTTPS/1.0\r\n\n\n";

		int length = message.length() + 1;

		if (SDLNet_TCP_Send(clientSocket, message.c_str(), length) < length)
		{
			std::cout << "Message could not be requested. Possibly too long." << std::endl;
			return 0;
		}
		else
		{
			char response[2000];

			if (SDLNet_TCP_Recv(clientSocket, response, 2000) <= 0)
			{
				std::cout << "Message not recieved. Possible Loss of data"
					<< std::endl;
				return 0;
			}
			else
			{
				std::cout << response << std::endl;
			}
		}

		SDLNet_TCP_Close(clientSocket);
	}

	Shutdown();

	system("Pause");
	return 0;
}