#pragma once
#include "Includes.h"

/**
	Light
	Emulates a light. The default light type is ambient light.
*/
class Light {
public:
	/** Constructor for objects type Light. 
	
		@param pDevice - The graphics device
		@param index - The index of the light in the graphics device
		@param enabled - Initial status of light
	*/
	Light(const LPDIRECT3DDEVICE9 pDevice, const int index, const bool enabled);

	/** Default destructor. */
	virtual ~Light() = default;
	
	/** Updates the light's on/off status.

		@param pDevice - The graphics device
	*/
	virtual void Update(const LPDIRECT3DDEVICE9 pDevice);

protected:
	D3DLIGHT9 mLight; // Light structure
	int mIndex;  // Index of the light in the graphics device
	bool mEnabled; // Light is on/off
	bool mWasToggled = false; // Light was recently toggled
};