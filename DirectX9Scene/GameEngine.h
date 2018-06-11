#pragma once
#include "Includes.h"
#include "RenderEngine.h"

class Window;

/**
	GameEngine
	Main engine for the game logic. Encompasses all engines needed for the game to run and render.
*/
class GameEngine {
public:
	/** Constructs objects of type GameEngine.
		Sets the window the game engine will run in.
		
		@param window - Window the game engine will run in
	*/
	GameEngine(Window* window);

	/** Destructor for objects of type GameEngine.
		Releases all memory allocated by the game engine.
	*/
	virtual ~GameEngine();

	/** Initializes the GameEngine.
		Sets up the render engine.

		@return Pass or fail result of initialization
	*/
	HRESULT Init();

	/** Gets the render engine.

		@return Render engine
	*/
	RenderEngine* GetRenderEngine() const;

	/** Continuous loop that runs the game code.
		Counts frame rate and renders the scene until escape key is pressed.

		@param deltaTime - Time in seconds

		@return Pass or fail result of the game loop
	*/
	HRESULT GameLoop(double deltaTime);

private:
	Window* mWindow; // Window that the game engine is in
	RenderEngine* mRenderEngine; // Render engine to render the scene
};