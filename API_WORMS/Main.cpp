#include "GamePlay.h"
#include "MainMenu.h"

HWND hWnd;
GameSound gSndController;
INT gSceneController;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY :
		PostQuitMessage(0);
		break;
	default :
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int APIENTRY WinMain(HINSTANCE Inst, HINSTANCE PrevInst, LPSTR CmdLine, int Show)
{
	WNDCLASSEXA wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = Inst;
	wcex.hIcon = LoadIcon(Inst, IDI_APPLICATION);
	wcex.hCursor = LoadCursorFromFile("./Resource/mouse.cur");
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "API Worms";
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	RegisterClassEx(&wcex);

	hWnd = CreateWindow("API Worms", "Worms",
		WS_OVERLAPPEDWINDOW,
		50, 50,
		WINSIZEX, WINSIZEY,
		nullptr, nullptr, Inst, nullptr);

	ShowWindow(hWnd, Show);
	UpdateWindow(hWnd);

	MSG msg;
	CMainMenu Menu;
	if (!Menu.Initialize())
		return 0;
	CGamePlay Start;
	gSceneController = MAINSCENE;

	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// TODO : Game Logic
		switch (gSceneController)
		{
		case MAINSCENE :
			if (Menu.Update() == false)
				break;
			Menu.Render();
			break;
		case GAMELOAD :
			Menu.Destroy();
			if (!Start.Initialize())
				return 0;
			gSceneController = GAMESCENE;
		case GAMESCENE :
			if (Start.Update() == false)
				break;
			Start.Render();
			break;
		case EXITGAME :
			return (int)msg.wParam;
		default:
			break;
		}
	}

	return (int)msg.wParam;
}