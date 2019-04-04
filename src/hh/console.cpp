

#include "hh/console.hpp"

#include <Windows.h>

#include <functional>

namespace hh
{
	struct console::control_handler
	{
		static BOOL WINAPI CtrlHandler(DWORD fdwCtrlType);
		static int register_me(bool value);
		//
		std::function<void(int)> callback;
	};
	struct console::control_handler console_control_handler_impl;
	BOOL __stdcall console::control_handler::CtrlHandler(DWORD fdwCtrlType)
	{
		switch (fdwCtrlType)
		{
			// Handle the CTRL-C signal. 
		case CTRL_C_EVENT:
			//printf("Ctrl-C event\n\n");
			//Beep(750, 300);
			return TRUE;

			// CTRL-CLOSE: confirm that the user wants to exit. 
		case CTRL_CLOSE_EVENT:
			//Beep(600, 200);
			//printf("Ctrl-Close event\n\n");
			return TRUE;

			// Pass other signals to the next handler. 
		case CTRL_BREAK_EVENT:
			//Beep(900, 200);
			//printf("Ctrl-Break event\n\n");
			return TRUE;

		case CTRL_LOGOFF_EVENT:
			//Beep(1000, 200);
			//printf("Ctrl-Logoff event\n\n");
			return FALSE;

		case CTRL_SHUTDOWN_EVENT:
			//Beep(750, 500);
			//printf("Ctrl-Shutdown event\n\n");
			return FALSE;

		default:
			return FALSE;
		}
	}

	int console::control_handler::register_me(bool value)
	{
		return SetConsoleCtrlHandler(CtrlHandler, value ? TRUE : FALSE) ? 0 : GetLastError();
	}

	console::console(handle_t h)
		: m_handle(h)
	{
	}
	console::console(standard_mode mode)
	{
		switch (mode)
		{
		case standard_input:
			m_handle = (size_t)GetStdHandle(STD_INPUT_HANDLE);
			break;
		case standard_output:
			m_handle = (size_t)GetStdHandle(STD_OUTPUT_HANDLE);
			break;
		case standard_error:
			m_handle = (size_t)GetStdHandle(STD_ERROR_HANDLE);
			break;
		default:
			m_handle = (size_t)INVALID_HANDLE_VALUE;
			break;
		}
	}
	console::~console()
	{
	}
	void console::cls()
	{
		auto h = (HANDLE)m_handle;
		if (h == INVALID_HANDLE_VALUE) { return; }
		if (h == nullptr) { return; }

		COORD coordScreen = { 0, 0 };    // home for the cursor 
		DWORD cCharsWritten;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD dwConSize;

		// Get the number of character cells in the current buffer. 

		if (!GetConsoleScreenBufferInfo(h, &csbi))
		{
			return;
		}

		dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

		// Fill the entire screen with blanks.

		if (!FillConsoleOutputCharacter(h,        // Handle to console screen buffer 
			(TCHAR) ' ',     // Character to write to the buffer
			dwConSize,       // Number of cells to write 
			coordScreen,     // Coordinates of first cell 
			&cCharsWritten))// Receive number of characters written
		{
			return;
		}

		// Get the current text attribute.

		if (!GetConsoleScreenBufferInfo(h, &csbi))
		{
			return;
		}

		// Set the buffer's attributes accordingly.

		if (!FillConsoleOutputAttribute(h,         // Handle to console screen buffer 
			csbi.wAttributes, // Character attributes to use
			dwConSize,        // Number of cells to set attribute 
			coordScreen,      // Coordinates of first cell 
			&cCharsWritten)) // Receive number of characters written
		{
			return;
		}

		// Put the cursor at its home coordinates.

		SetConsoleCursorPosition(h, coordScreen);
	}
	void console::register_control_handler(bool value)
	{
	}
	int console::ScrollByAbsoluteCoord(int iRows)
	{
		auto h = (HANDLE)m_handle;

		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
		SMALL_RECT srctWindow;

		// Get the current screen buffer size and window position. 

		if (!GetConsoleScreenBufferInfo(h, &csbiInfo))
		{
			printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());
			return 0;
		}

		// Set srctWindow to the current window size and location. 

		srctWindow = csbiInfo.srWindow;

		// Check whether the window is too close to the screen buffer top

		if (srctWindow.Top >= iRows)
		{
			srctWindow.Top -= (SHORT)iRows;     // move top up
			srctWindow.Bottom -= (SHORT)iRows;  // move bottom up

			if (!SetConsoleWindowInfo(
				h,          // screen buffer handle 
				TRUE,             // absolute coordinates 
				&srctWindow))     // specifies new location 
			{
				printf("SetConsoleWindowInfo (%d)\n", GetLastError());
				return 0;
			}
			return iRows;
		}
		else
		{
			printf("\nCannot scroll; the window is too close to the top.\n");
			return 0;
		}
	}
	int console::ScrollByRelativeCoord(int iRows)
	{
		auto h = (HANDLE)m_handle;

		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
		SMALL_RECT srctWindow;

		// Get the current screen buffer window position. 

		if (!GetConsoleScreenBufferInfo(h, &csbiInfo))
		{
			printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());
			return 0;
		}

		// Check whether the window is too close to the screen buffer top

		if (csbiInfo.srWindow.Top >= iRows)
		{
			srctWindow.Top = -(SHORT)iRows;     // move top up
			srctWindow.Bottom = -(SHORT)iRows;  // move bottom up 
			srctWindow.Left = 0;         // no change 
			srctWindow.Right = 0;        // no change 

			if (!SetConsoleWindowInfo(
				h,          // screen buffer handle 
				FALSE,            // relative coordinates
				&srctWindow))     // specifies new location 
			{
				printf("SetConsoleWindowInfo (%d)\n", GetLastError());
				return 0;
			}
			return iRows;
		}
		else
		{
			printf("\nCannot scroll; the window is too close to the top.\n");
			return 0;
		}
	}
}
