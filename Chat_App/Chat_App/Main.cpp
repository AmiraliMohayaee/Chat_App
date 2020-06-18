#include <iostream>
#include <string>
#include "ChatServer.h"
#include "Utility.h"#


/////////////////////////////////////
//	Server-side code
/////////////////////////////////////

int main(int argc, char* argv[])
{
	Utility::ResizeWindow(800, 800);

	ChatServer chat;

	std::cout << "+=============================+" << std::endl;
	std::cout << R"(   Beginning Chat App Server)" << std::endl;
	std::cout << "+=============================+" << std::endl;

	chat.Startup(1234, nullptr);
	chat.Chat();
	chat.Shutdown();

	return 0;
}