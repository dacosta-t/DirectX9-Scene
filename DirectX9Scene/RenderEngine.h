#pragma once
#include <windows.h>
#include <string>
#include <vector>

#include "Includes.h"
#include "PickingEngine.h"
#include "Fireworks.h"
#include "Snow.h"
#include "SurfaceLoader.h"
#include "Model.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "Mirror.h"

class RenderEngine {
public:
	/** Constructs objects of type RenderEngine. */
	RenderEngine();

	/** Desctructor for objects of type RenderEngine.
		Releases all memory allocated by the render engine.
	*/
	virtual ~RenderEngine();

	/** Initializes the render engine.
		Initializes DirectX objects and stretches bitmap to surface and frequency for the frame count.

		@param hwnd - The handle to the window that the render engine will be drawing to

		@return Pass or fail result of initialization
	*/
	HRESULT Init(HWND hwnd);

	/** Creates models out of meshes. */
	HRESULT CreateModels();

	/** Creates lights and adds it to the graphics device.
		Creates a directional, spot, and point light.
	*/
	void CreateLights();

	/** Initalizes the DirectX render device.

		@param hWndTarget - Handle to the window that the render engine is in
		@param width - Width of the window
		@param height - Height of the window
		@param bWindowed -  Whether the window is windowed or fullscreen
		@param fullScreenFormat - Surface format for the back buffer
		@param pD3D - COM object
		@param ppDevice - graphics device

		@return Pass or fail result of initializing render device
	*/
	HRESULT InitDirect3DDevice(HWND hWndTarget, int width, int height, BOOL bWindowed, D3DFORMAT fullScreenFormat, LPDIRECT3D9 pD3D, LPDIRECT3DDEVICE9* ppDevice);

	/** Gets the graphics device.

		@return Graphics device
	*/
	LPDIRECT3DDEVICE9 GetDevice() const;

	/** Gets the camera.

		@return Game camera
	*/
	Camera* GetCamera() const;

	/** Gets the selected model.

		@return Currently selected model
	*/
	Model* GetSelectedModel();

	/** Updates the objects and camera.

		@param deltaTime - Time in seconds
	*/
	void Update(float deltaTime);

	/** Renders the scene.
		Swaps the surface with the back buffer to display the scene.

		@return Pass or fail result of rendering
	*/
	HRESULT RenderScene();

	/** Renders the models and fps in the scene.

		@return Pass or fail result of rendering
	*/
	HRESULT RenderObjects();

	/** Selects the model to interact with by mouse click position. */
	void PickModel(int x, int y);

	/** Increments the frame count to keep track of frame rate. */
	void FrameCount();

	const static int WIDTH = 1920; // Width of screen
	const static int HEIGHT = 1080; // Height of screen
	const static int TRANSFORM_SPEED = 3; // Speed to perform transforms

private:
	LPDIRECT3D9 mPD3D; // COM object
	LPDIRECT3DDEVICE9 mPDevice; // Graphics device
	LPDIRECT3DSURFACE9 mPSurface; // Surface
	SurfaceLoader* mSurfaceLoader; // Loader to load objects to the surface
	LPD3DXFONT mFont; // Font to display FPS counter

	PickingEngine* mPickEngine; // Picking engine to select models
	ParticleEngine* mParticleEngine; // Particle engine
	Camera* mCamera; // Game camera
	std::vector<Model*> mModels; // Array of models to render
	std::vector<Light*> mLights; // Array of lights to render
	Mirror* mMirror; // Mirror

	int mSelectedIndex; // Index of the selected model -> -1 = camera
	INT64 mFrequency; // Holds number of ticks per second
	INT64 mFrameRate; // Holds current frame rate calculated
	INT64 mFrameCount; // Holds current number of frames counted before 1 second has passed
};