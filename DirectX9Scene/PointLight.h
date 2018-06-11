#pragma once
#include "Light.h"

class PointLight : public Light {
public:
	/** Constructor for objects type PointLight.

		@param pDevice - The graphics device
		@param index - The index of the light in the graphics device
		@param enabled - Initial status of light
	*/
	PointLight(const LPDIRECT3DDEVICE9 pDevice, const int index, const bool enabled);

	/** Default destructor. */
	virtual ~PointLight() = default;

	/** Updates the light's on/off status.

		@param pDevice - The graphics device
	*/
	void Update(const LPDIRECT3DDEVICE9 pDevice);
};