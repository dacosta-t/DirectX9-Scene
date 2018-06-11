#pragma once

#include "Includes.h"
#include "Model.h"

struct Ray {
	D3DXVECTOR3 origin;
	D3DXVECTOR3 direction;
};

/** PickingEngine
	Engine to determine model picking with the mouse using a ray.
*/
class PickingEngine {
public:
	/** Default constructor. */
	PickingEngine() = default;

	/** Default destructor. */
	virtual ~PickingEngine() = default;

	/** Calculates the ray from the origin to the mouse position.
	
		@param x - X coordinate of mouse
		@param y - Y coordinate of mouse
		@param pDevice - The graphics device
	*/
	void CalcPickingRay(int x, int y, LPDIRECT3DDEVICE9 pDevice);

	/** Transforms the ray to view space. 
		
		@param T - Space to transform to
	*/
	void TransformRay(D3DXMATRIX* T);

	/** Test if the ray hits a bounding sphere.

		@param sphere - The bounding sphere of a model
		
		@return pass or fail result of the ray hitting the sphere
	*/
	bool RaySphereHitTest(BoundingSphere* sphere);

private:
	Ray mRay; // Ray to test for picking
};