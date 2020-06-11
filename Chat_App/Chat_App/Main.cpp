#include <iostream>
#include <string>
#include "TCPConnection.h"
#include "ScreenManager.h"
#include "ChatServer.h"


/////////////////////////////////////
//	Server-side code
/////////////////////////////////////

int main(int argc, char* argv[])
{
	Screen->ConsoleResize(800, 800);

	ChatServer chat;

	std::string character;

	chat.Startup(1234, nullptr);
	chat.Update();
	chat.Shotdown();

	Screen->OnWait();
	
	return 0;
}