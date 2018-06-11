#include "Window.h"
#include "GameEngine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pstrCmdLine, int iCmdShow)
{
	MSG msg;
	std::string strAppName = "Assignment 1: DirectX 9";
	Window* window = new Window(hInstance, strAppName);

	window->Show();
	window->Update();

	GameEngine* game = new GameEngine(window);
	window->SetGameEngine(game);

	if (FAILED(game->Init())) {
		delete window;
		delete game;
	}

	double start = (float)timeGetTime();
	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			double end = timeGetTime();
			double deltaTime = (end - start);
			start = timeGetTime();
			game->GameLoop(deltaTime / 1000);
		}
	}

	delete window;
	delete game;

	return msg.wParam;
}