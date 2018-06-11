#pragma once
#include "Light.h"

class DirectionalLight : public Light {
public:
	/** Constructor for objects type DirectionalLight.

		@param pDevice - The graphics device
		@param index - The index of the light in the graphics device
		@param enabled - Initial status of light
	*/
	DirectionalLight(const LPDIRECT3DDEVICE9 pDevice, const int index, const bool enabled);

	/** Default destructor. */
	virtual ~DirectionalLight() = default;

	/** Updates the light's on/off status.

		@param pDevice - The graphics device
	*/
	void Update(const LPDIRECT3DDEVICE9 pDevice);
};