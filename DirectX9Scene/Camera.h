#pragma once

#include "Includes.h"

class Camera {
public:
	/** Constructs objects of type Camera.

		@param pDevice - The graphics device
	*/
	Camera(LPDIRECT3DDEVICE9 pDevice);

	/** Default destructor. */
	virtual ~Camera() = default;

	/** Gets the camera's view matrix.

		@return Camera's view matrix
	*/
	D3DXMATRIXA16 GetMatrix() const;

	/** Updates the camera's position.

		@param deltaTime - Time in seconds
	*/
	void Update(double deltaTime);

	/** Translates the camera in the specified x, y, z direction.

		@param x - Movement in x direction
		@param y - Movement in y direction
		@param z - Movement in z direction
	*/
	void Move(float x, float y, float z);

	/** Rotates the camera.

		@param x - Rotation around the x-axis
		@param y - Rotation around the y-axis
		@param z - Rotation around the z-axis
	*/
	void Rotate(float x, float y, float z);

	const static int TRANSFORM_SPEED = 3; // Speed to perform transforms
private:
	D3DXMATRIX mViewMatrix; // View matrix
};