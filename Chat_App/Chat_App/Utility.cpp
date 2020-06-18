#include "Utility.h"
#include <iostream>


namespace Utility
{
	void ChangeTextImage(int color)
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(hConsole, color);
	}

	void ResizeWindow(int width, int height)
	{
		HWND handle = GetConsoleWindow();
		RECT r;
		GetWindowRect(handle, &r); //stores the console's current dimensions

		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(handle, r.left, r.top, width, height, FALSE);
	}
}
