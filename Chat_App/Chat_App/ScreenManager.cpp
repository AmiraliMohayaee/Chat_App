#include "ScreenManager.h"
#include <iostream>


ScreenManager* ScreenManager::GetInstance()
{
	static ScreenManager* s_screenInstance = new ScreenManager;
	return s_screenInstance;
}

ScreenManager::ScreenManager()
{
	// Get window handle to console, and device context
	console_handle = GetConsoleWindow();
	device_context = GetDC(console_handle);
}

ScreenManager::~ScreenManager()
{
	ReleaseDC(console_handle, device_context);
}

void ScreenManager::DrawLine(int width, int r, int g,
	int b, int x, int y)
{
	HPEN pen = CreatePen(PS_SOLID, width, RGB(r, g, b));
	SelectObject(device_context, pen);

	LineTo(device_context, x, y);
}

void ScreenManager::OnWait()
{
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << "Press Enter key to continue..." << std::endl;
	std::cin.get();
}

void ScreenManager::ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home to starting position at coords 0, 0 */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void ScreenManager::ConsoleResize(int width, int height)
{
	console_handle = GetConsoleWindow();
	RECT r;
	GetWindowRect(console_handle, &r); //stores the console's current dimensions

	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(console_handle, r.left, r.top, width, height, FALSE);
}

void ScreenManager::ChangeTextColor(int colour)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, colour);
}
