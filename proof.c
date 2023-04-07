#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define NAME "proof"
#define DEFAULT_MODKEY MOD_ALT

enum keys {
	KEY_SELECT_UP = 1,
	KEY_SELECT_DOWN = 2,
	KEY_LEFT = 18,
	KEY_RIGHT = 19
};

BOOL CALLBACK filter_windows(HWND hwnd, LPARAM lParam)
{
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		case WM_HOTKEY: {
			printf("WM_HOTKEY\n");
			break;
		}
		default:
			printf("default WndProc\n");
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
  	WNDCLASSEX winClass;
  	HWND hwnd;
  	MSG msg;

  	memset(&winClass, 0, sizeof(winClass));

  	winClass.cbSize = sizeof(WNDCLASSEX);
  	winClass.lpfnWndProc = WndProc;
  	winClass.hInstance = hInstance;
  	winClass.hCursor = NULL;
  	winClass.hbrBackground = NULL;
  	winClass.lpszClassName = NAME;
  	winClass.hIcon = NULL;
  	winClass.hIconSm = NULL;
  	winClass.lpszMenuName = NULL;
  	winClass.style = 0;

  	if(!RegisterClassEx(&winClass)) {
  		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
  		return 0;
  	}

  	hwnd = CreateWindowEx(0, NAME, NAME, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, hInstance, NULL);
  
  	if(hwnd == NULL) {
  		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
  		return 0;
  	}

	printf("hInstance: %d\n", hInstance);
	printf("hPrevInstance: %d\n", hPrevInstance);
	printf("lpCmdLine: %s\n", lpCmdLine);
	printf("nCmdShow: %d\n", nCmdShow);
	printf("hwnd: %d\n", hwnd);
	printf("msg: %d\n", msg);

	RegisterHotKey(hwnd, 1, DEFAULT_MODKEY, 'J');

	EnumWindows(filter_windows, 0);

	while(GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
  		DispatchMessage(&msg);
  	}

	return TRUE;
}
