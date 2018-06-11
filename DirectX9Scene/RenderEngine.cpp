#include "RenderEngine.h"

RenderEngine::RenderEngine()
	: mSelectedIndex(-1)
{
	mPickEngine = new PickingEngine();
	//D3DXVECTOR3 origin(0.0f, 0.0f, 50.0f);
	//mParticleEngine = new Fireworks(&origin, 6000);
	BoundingBox boundingBox;
	boundingBox.min = D3DXVECTOR3(-10.0f, -10.0f, -10.0f);
	boundingBox.max = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
	mParticleEngine = new Snow(&boundingBox, 5000);
	mSurfaceLoader = new SurfaceLoader();
}

RenderEngine::~RenderEngine()
{
	if (mPDevice) {
		mPDevice->Release();
	}
	if (mPD3D) {
		mPD3D->Release();
	}
	if (mPSurface) {
		mPSurface->Release();
	}
	if (mFont) {
		mFont->Release();
	}

	for (size_t i = 0; i < mModels.size(); i++) {
		delete mModels[i];
	}
	mModels.clear();

	for (size_t i = 0; i < mLights.size(); i++) {
		delete mLights[i];
	}
	mLights.clear();

	delete mCamera;
	delete mMirror;
	delete mSurfaceLoader;
	delete mParticleEngine;
	delete mPickEngine;
}

HRESULT RenderEngine::Init(HWND hwnd)
{
	HRESULT r; // Return value

	// Create COM object
	mPD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (mPD3D == NULL) {
		OutputDebugString("Could not create IDirect3D9 object");
		return E_FAIL;
	}

	// Initialize device
	r = InitDirect3DDevice(hwnd, RenderEngine::WIDTH, RenderEngine::HEIGHT, true, D3DFMT_X8R8G8B8, mPD3D, &mPDevice);
	if (FAILED(r)) {
		OutputDebugString("Initialization of the device failed");
		return E_FAIL;
	}

	LPDIRECT3DSURFACE9 pBackSurf = 0;
	// Get the back buffer to later load a surface to it
	r = mPDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackSurf);
	if (FAILED(r)) {
		OutputDebugString("Could not retrieve back buffer");
		return E_FAIL;
	}

	// Load the bitmap to the surface
	r = mSurfaceLoader->LoadBitmapToSurface("wowpurple.bmp", &mPSurface, mPDevice);
	if (FAILED(r)) {
		OutputDebugString("Could not load bitmap");
		return E_FAIL;
	}

	// Load the newly created surface onto the back buffer
	r = D3DXLoadSurfaceFromSurface(pBackSurf, NULL, NULL, mPSurface, NULL, NULL, D3DX_FILTER_TRIANGLE, 0);
	if (FAILED(r)) {
		OutputDebugString("Could not load surface");
		return E_FAIL;
	}

	pBackSurf->Release();
	pBackSurf = nullptr;

	// Create the font used to draw the FPS counter
	r = D3DXCreateFont(mPDevice, 18, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Calibri", &mFont);
	if (FAILED(r)) {
		OutputDebugString("Could not create font");
		return E_FAIL;
	}

	// Enable the zbuffer
	mPDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	// Create the camera
	mCamera = new Camera(mPDevice);

	//Create the mirror
	mMirror = new Mirror(mPDevice);

	// Create the models
	r = CreateModels();
	if (FAILED(r)) {
		OutputDebugString("Could not create models");
		return E_FAIL;
	}

	r = mParticleEngine->Init(mPDevice, "snowflake.dds");
	if (FAILED(r)) {
		OutputDebugString("Failed to initialize particle engine.");
	}

	// Create the lights
	CreateLights();

	// Set up frequency for frame counter
	QueryPerformanceFrequency((LARGE_INTEGER*)&mFrequency);

	if (mFrequency == 0) {
		OutputDebugString("The system does not support high resolution timing");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT RenderEngine::InitDirect3DDevice(HWND hWndTarget, int width, int height, BOOL bWindowed, D3DFORMAT fullScreenFormat, LPDIRECT3D9 pD3D, LPDIRECT3DDEVICE9* ppDevice)
{
	D3DPRESENT_PARAMETERS d3dpp; // rendering info
	D3DDISPLAYMODE d3ddm; // current display mode info
	HRESULT r = 0; // return value

	if (*ppDevice) {
		(*ppDevice)->Release();
	}

	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	r = pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	if (FAILED(r)) {
		OutputDebugString("Could not get display adapter information");
		return E_FAIL;
	}

	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = bWindowed ? d3ddm.Format : fullScreenFormat;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // D3DSWAPEFFECT_COPY;
	d3dpp.hDeviceWindow = hWndTarget;
	d3dpp.Windowed = bWindowed;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.FullScreen_RefreshRateInHz = 0; // default refresh rate
	d3dpp.PresentationInterval = bWindowed ? 0 : D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	r = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWndTarget, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, ppDevice);
	if (FAILED(r)) {
		OutputDebugString("Could not create the render device");
		return E_FAIL;
	}

	return S_OK;
}

LPDIRECT3DDEVICE9 RenderEngine::GetDevice() const
{
	return mPDevice;
}

Camera* RenderEngine::GetCamera() const
{
	return mCamera;
}

Model* RenderEngine::GetSelectedModel()
{
	return mModels[mSelectedIndex - 1];
}

void RenderEngine::Update(float deltaTime)
{
	FrameCount();

	if (mSelectedIndex == -1) {
		mCamera->Update(deltaTime);
	} else {
		GetSelectedModel()->Update(deltaTime);
	}

	for (auto it = mLights.begin(); it != mLights.end(); it++) {
		(*it)->Update(mPDevice);
	}

	mParticleEngine->Update(deltaTime);
	/*if (mParticleEngine->IsDead()) {
		mParticleEngine->Reset();
	}*/
}

HRESULT RenderEngine::RenderScene()
{
	HRESULT r;
	LPDIRECT3DSURFACE9 pBackSurf = 0;
	if (!mPDevice) {
		OutputDebugString("Cannot render because there is no device");
		return E_FAIL;
	}

	// Clear the graphics device and zbuffer
	mPDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0, 1.0f, 0);

	// Gets the back buffer that will be swapped after
	r = mPDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackSurf);
	if (FAILED(r)) {
		OutputDebugString("Could not retrieve back buffer");
	}

	// Update the back buffer with the surface
	r = mPDevice->UpdateSurface(mPSurface, NULL, pBackSurf, NULL);
	if (FAILED(r)) {
		OutputDebugString("Could not update surface");
	}

	// Render the objects onto the scene
	RenderObjects();
	
	pBackSurf->Release();
	pBackSurf = nullptr;
	mPDevice->Present(NULL, NULL, NULL, NULL);
	return S_OK;
}

HRESULT RenderEngine::RenderObjects()
{
	// Begin the scene
	if (SUCCEEDED(mPDevice->BeginScene())) {
		// Display FPS counter
		std::string frameText = "FPS: " + std::to_string(mFrameRate);
		mFont->DrawText(0, frameText.c_str(), -1, NULL, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

		// Render the models
		for (auto it = mModels.begin(); it != mModels.end(); it++) {
			Model* model = *it;
			mPDevice->SetTransform(D3DTS_WORLD, &model->GetMatrix());
			model->Render(mPDevice);
		}

		// Render the mirror
		mMirror->Render(mPDevice);
		mMirror->RenderReflection(mPDevice, mModels);

		// Render particle effects
		if (mParticleEngine->IsActive()) {
			D3DXMATRIX I;
			D3DXMatrixIdentity(&I);
			mPDevice->SetTransform(D3DTS_WORLD, &I);
			mParticleEngine->Render(mPDevice);
		}

		// Updates view
		mPDevice->SetTransform(D3DTS_VIEW, &mCamera->GetMatrix());

		mPDevice->EndScene();
		return S_OK;
	}
	return E_FAIL;
}

void RenderEngine::PickModel(int x, int y)
{
	mSelectedIndex = -1;
	mPickEngine->CalcPickingRay(x, y, mPDevice);

	D3DXMATRIX viewInverse;
	D3DXMatrixInverse(&viewInverse, 0, &mCamera->GetMatrix());

	mPickEngine->TransformRay(&viewInverse);

	for (int i = 0; i < mModels.size(); i++) {
		Model* model = mModels[i];
		if (mPickEngine->RaySphereHitTest(&model->GetBoundingSphere())) {
			mSelectedIndex = i + 1;
		}
	}
}

void RenderEngine::FrameCount()
{
	INT64 newCount = 0;
	static INT64 lastCount = 0;
	INT64 difference = 0;

	// Get new count of counter
	QueryPerformanceCounter((LARGE_INTEGER*)&newCount);

	if (newCount == 0) {
		OutputDebugString("The system does not support high resolution timing");
	}

	mFrameCount++;

	difference = newCount - lastCount;

	if (difference >= mFrequency) {
		mFrameRate = mFrameCount;
		mFrameCount = 0;

		lastCount = newCount;
	}
}

HRESULT RenderEngine::CreateModels()
{
	mModels.push_back(new Model("sphere.x", mPDevice));
	if (!mModels[mModels.size() - 1]) {
		return E_FAIL;
	}
	mModels[mModels.size() - 1]->Move(-1.0f, 0.0f, 0.0f);

	mModels.push_back(new Model("tiger2.x", mPDevice));
	if (!mModels[mModels.size() - 1]) {
		return E_FAIL;
	}
	mModels[mModels.size() - 1]->Move(1.0f, 0.0f, -3.0f);
	
	return S_OK;
}

void RenderEngine::CreateLights()
{
	// Enable lighting
	mPDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	mLights.push_back(new Light(mPDevice, -1, true));
	mLights.push_back(new DirectionalLight(mPDevice, 0, false));
	mLights.push_back(new SpotLight(mPDevice, 1, false));
	mLights.push_back(new PointLight(mPDevice, 2, false));
}