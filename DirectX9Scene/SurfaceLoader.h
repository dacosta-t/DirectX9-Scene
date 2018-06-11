#pragma once

#include "Includes.h"

/**
	SurfaceLoader
	Loads objects onto surfaces that will be rendered to the scene.
*/
class SurfaceLoader {
public:
	/** Default constructor */
	SurfaceLoader() = default;

	/** Default destructor */
	virtual ~SurfaceLoader() = default;

	/** Loads the specified bitmap to the surface.
		Creates a surface to stretch the bitmap on to.

		@param ppSurface - Surface to load the bitmap on
		@param pDevice - Graphics device

		@return Pass or fail result of bitmap loading
	*/
	HRESULT LoadBitmapToSurface(const char* pathName, LPDIRECT3DSURFACE9* ppSurface, LPDIRECT3DDEVICE9 pDevice);

private:

};