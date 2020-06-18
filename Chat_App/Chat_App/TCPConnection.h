#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H


#include <SDL.h>
#include <SDL_net.h>


class TCPConnection
{
public:
	TCPConnection();
	bool Initialize();
	void Shutdown();

protected:
	IPaddress m_ip;
	TCPsocket m_socket;
};



#endif