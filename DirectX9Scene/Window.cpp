#include "Window.h"
#include "GameEngine.h"
#include "RenderEngine.h"

Window::Window(HINSTANCE hInstance, std::string title)
{
	WNDCLASSEX wc;

	// Fill the window class struct
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = sizeof(GameEngine*);
	wc.lpfnWndProc = Window::WndProc;
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_HAND);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = title.c_str();

	// Register the window to the OS and create the window
	RECT r;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &r, 0);
	RegisterClassEx(&wc);
	mHwnd = CreateWindowEx(NULL,
		title.c_str(),
		title.c_str(),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		RenderEngine::WIDTH, RenderEngine::HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);
}

HWND Window::GetHwnd() const
{
	return mHwnd;
}

bool Window::Show() const
{
	return ShowWindow(mHwnd, SW_SHOW);
}

bool Window::Update() const
{
	return UpdateWindow(mHwnd);
}

void Window::SetGameEngine(const GameEngine* engine)
{
	SetWindowLongPtr(mHwnd, 0, (LONG)engine);
}

LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	GameEngine* game = nullptr;
	switch (uMessage) {

	case WM_LBUTTONDOWN:
		game = (GameEngine*)GetWindowLongPtr(hwnd, 0);
		if (game != nullptr) {
			game->GetRenderEngine()->PickModel(LOWORD(lParam), HIWORD(lParam));
		}
		return 0;

	case WM_PAINT:
		ValidateRect(hwnd, NULL);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMessage, wParam, lParam);
}