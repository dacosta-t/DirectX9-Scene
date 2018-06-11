#include "SurfaceLoader.h"
#include "RenderEngine.h"

HRESULT SurfaceLoader::LoadBitmapToSurface(const char* pathName, LPDIRECT3DSURFACE9* ppSurface, LPDIRECT3DDEVICE9 pDevice)
{
	// Create surface to stretch bitmap onto.
	HRESULT r = pDevice->CreateOffscreenPlainSurface(RenderEngine::WIDTH, RenderEngine::HEIGHT, D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, ppSurface, NULL);

	if (FAILED(r)) {
		OutputDebugString("Could not create surface");
		return E_FAIL;
	}

	// Load the bitmap from file and load it onto surface.
	r = D3DXLoadSurfaceFromFile(*ppSurface, NULL, NULL, pathName, NULL, D3DX_DEFAULT, 0, NULL);
	if (FAILED(r)) {
		OutputDebugString("Unable to load surface from bitmap file");
		return E_FAIL;
	}

	return S_OK;
}