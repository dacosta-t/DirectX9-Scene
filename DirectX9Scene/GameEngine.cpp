#include "GameEngine.h"
#include "Window.h"

GameEngine::GameEngine(Window* window)
	: mWindow(window)
{
	mRenderEngine = new RenderEngine();
}

GameEngine::~GameEngine()
{
	delete mRenderEngine;
	mWindow = nullptr;
}

HRESULT GameEngine::Init()
{
	// Initialize render engine
	if (FAILED(mRenderEngine->Init(mWindow->GetHwnd()))) {
		OutputDebugString("Render engine failed to initialize");
		return E_FAIL;
	}

	return S_OK;
}

RenderEngine* GameEngine::GetRenderEngine() const
{
	return mRenderEngine;
}

HRESULT GameEngine::GameLoop(double deltaTime)
{
	// Update and render the scene
	mRenderEngine->Update(deltaTime);
	mRenderEngine->RenderScene();

	// Quit when escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE)) {
		PostQuitMessage(0);
	}

	return S_OK;
}