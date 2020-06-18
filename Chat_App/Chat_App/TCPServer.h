#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <string>
#include <list>
#include "TCPConnection.h"



class TCPServer : public TCPConnection
{
public:
	TCPServer();
	~TCPServer();
	bool Init(Uint16 port, const char* IPAddress = nullptr);
	bool OpenSocket();
	bool ListenSocket();

	bool Send(const std::string& msg);
	bool Recv();

	void CloseSocket();

	void PushClient(const TCPsocket& sock);
	void RemoveClient(const TCPsocket& sock);
	void ClientList();

	bool TimeOutCount();

	const std::string GetSentMsg();
	const std::string GetRecvMsg();


private:
	// These elements are saves and send to 
	// the chat just in case
	std::string m_sendMsg;
	std::string m_recvMsg;

	TCPsocket m_client;

	std::list<TCPsocket> m_clientSockets;
};


#endif