#include "Camera.h"

Camera::Camera(LPDIRECT3DDEVICE9 pDevice)
{
	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye five units back along the z-axis and up three units, look at the 
	// origin, and define "up" to be in the y-direction.
	D3DXVECTOR3 vEyePt(0.0f, 3.0f, -10.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&mViewMatrix, &vEyePt, &vLookatPt, &vUpVec);
	pDevice->SetTransform(D3DTS_VIEW, &mViewMatrix);

	// For the projection matrix, we set up a perspective transform (which
	// transforms geometry from 3D view space to 2D viewport space, with
	// a perspective divide making objects smaller in the distance). To build
	// a perpsective transform, we need the field of view (1/4 pi is common),
	// the aspect ratio, and the near and far clipping planes (which define at
	// what distances geometry should be no longer be rendered).
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

D3DXMATRIXA16 Camera::GetMatrix() const
{
	return mViewMatrix;
}

void Camera::Update(double deltaTime)
{
	if (GetAsyncKeyState('D')) {
		Move(TRANSFORM_SPEED * deltaTime, 0.0f, 0.0f);
	}
	if (GetAsyncKeyState('A')) {
		Move(-TRANSFORM_SPEED * deltaTime, 0.0f, 0.0f);
	}
	if (GetAsyncKeyState('W')) {
		Move(0.0f, TRANSFORM_SPEED * deltaTime, 0.0f);
	}
	if (GetAsyncKeyState('S')) {
		Move(0.0f, -TRANSFORM_SPEED * deltaTime, 0.0f);
	}
	if (GetAsyncKeyState('Z')) {
		Move(0.0f, 0.0f, TRANSFORM_SPEED * deltaTime);
	}
	if (GetAsyncKeyState('X')) {
		Move(0.0f, 0.0f, -TRANSFORM_SPEED * deltaTime);
	}
	if (GetAsyncKeyState('R')) {
		Rotate(TRANSFORM_SPEED * deltaTime, 0.0f, 0.0f);
	}
	if (GetAsyncKeyState('F')) {
		Rotate(-TRANSFORM_SPEED * deltaTime, 0.0f, 0.0f);
	}
	if (GetAsyncKeyState('C')) {
		Rotate(0.0f, TRANSFORM_SPEED * deltaTime, 0.0f);
	}
	if (GetAsyncKeyState('V')) {
		Rotate(0.0f, -TRANSFORM_SPEED * deltaTime, 0.0f);
	}
	if (GetAsyncKeyState('Q')) {
		Rotate(0.0f, 0.0f, TRANSFORM_SPEED * deltaTime);
	}
	if (GetAsyncKeyState('E')) {
		Rotate(0.0f, 0.0f, -TRANSFORM_SPEED * deltaTime);
	}
}

void Camera::Move(float x, float y, float z)
{
	D3DXMATRIXA16 temp;
	D3DXMatrixTranslation(&temp, x, y, z);
	D3DXMatrixMultiply(&mViewMatrix, &mViewMatrix, &temp);
}

void Camera::Rotate(float x, float y, float z)
{
	D3DXMATRIXA16 xRotation;
	D3DXMatrixRotationX(&xRotation, x);
	D3DXMATRIXA16 yRotation;
	D3DXMatrixRotationY(&yRotation, y);
	D3DXMATRIXA16 zRotation;
	D3DXMatrixRotationZ(&zRotation, z);
	D3DXMATRIXA16 temp;
	D3DXMatrixMultiply(&temp, &xRotation, &yRotation);
	D3DXMatrixMultiply(&temp, &temp, &zRotation);
	D3DXMatrixMultiply(&mViewMatrix, &temp, &mViewMatrix);
}