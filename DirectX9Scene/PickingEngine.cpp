#include "PickingEngine.h"

void PickingEngine::CalcPickingRay(int x, int y, LPDIRECT3DDEVICE9 pDevice)
{
	float px = 0.0f;
	float py = 0.0f;

	D3DVIEWPORT9 vp;
	pDevice->GetViewport(&vp);

	D3DXMATRIX proj;
	pDevice->GetTransform(D3DTS_PROJECTION, &proj);

	px = (((2.0f*x) / vp.Width) - 1.0f) / proj(0, 0);
	py = (((-2.0f*y) / vp.Height) + 1.0f) / proj(1, 1);

	mRay.origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mRay.direction = D3DXVECTOR3(px, py, 1.0f);
}

void PickingEngine::TransformRay(D3DXMATRIX* T)
{
	// transform the ray's origin, w = 1.
	D3DXVec3TransformCoord(
		&mRay.origin,
		&mRay.origin,
		T);

	// transform the ray's direction, w = 0.
	D3DXVec3TransformNormal(
		&mRay.direction,
		&mRay.direction,
		T);

	// normalize the direction
	D3DXVec3Normalize(&mRay.direction, &mRay.direction);
}

bool PickingEngine::RaySphereHitTest(BoundingSphere* sphere)
{
	D3DXVECTOR3 v = mRay.origin - sphere->center;

	float b = 2.0f * D3DXVec3Dot(&mRay.direction, &v);
	float c = D3DXVec3Dot(&v, &v) - (sphere->radius * sphere->radius);

	// find the discriminant
	float discriminant = (b * b) - (4.0f * c);

	// test for imaginary number
	if (discriminant < 0.0f) {
		return false;
	}

	discriminant = sqrtf(discriminant);

	float s0 = (-b + discriminant) / 2.0f;
	float s1 = (-b - discriminant) / 2.0f;

	// if a solution is >= 0, then we intersected the sphere
	if (s0 >= 0.0f && s1 >= 0.0f) {
		return true;
	}

	return false;
}