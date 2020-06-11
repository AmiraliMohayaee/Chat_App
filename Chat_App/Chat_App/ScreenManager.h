#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H


#include "Singleton.h"

// Defining that you're running win2000 or higher
#define _WIN32_WINNT 0x0500

//it is important that the above line be typed
//  BEFORE <windows.h> is included
#include <Windows.h>
//#include <dos.h>	// Can't believe this still exists

// Creating a global typename for the manager
#define Screen ScreenManager::GetInstance()

class ScreenManager
{

public:
	~ScreenManager();
	void DrawLine(int width, int r, int g, int b, int x, int y);

	void OnWait();
	void ClearScreen();
	void ConsoleResize(int width, int height);
	void ChangeTextColor(int color);

	static ScreenManager* GetInstance();


private:
	// Required ctor and copy-ctor for singleton 
	ScreenManager();
	ScreenManager(const ScreenManager& screen);
	ScreenManager& operator=(const ScreenManager& screen);

private:
	// Get window handle to console, and device context
	HWND console_handle;
	HDC device_context;
	int m_colour = 0; // Setting to 0 = black by default
};



#endif




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	For reference: https://social.msdn.microsoft.com/Forums/vstudio/en-US/aa573238-3228-44bc-ae4d-368386005031/any-alternatives-to-systemquotpausequot?forum=vcgeneral
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//
//	For reference: http://www.cplusplus.com/articles/4z18T05o/
//
////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
////
////	For Ref: http://www.cplusplus.com/forum/beginner/1481/
////
///////////////////////////////////////////////////////////////////
