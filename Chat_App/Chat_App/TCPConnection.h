#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H


#include <string>
#include <vector>
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


class TCPServer : public TCPConnection
{
public:
	TCPServer();
	bool Init(Uint16 port, const char* IPAddress = nullptr);
	bool OpenSocket();
	void ListenSocket();

	bool Send(const std::string& msg);
	bool Recv(std::string& msg);

	void CloseSocket();

	void PushClient();
	void PopClient();


private:
	TCPsocket m_client;

	std::vector<TCPsocket> m_clientSockets;
};

#endif