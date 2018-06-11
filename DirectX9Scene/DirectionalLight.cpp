#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const LPDIRECT3DDEVICE9 pDevice, const int index, const bool enabled)
	: Light::Light(pDevice, index, enabled)
{
	ZeroMemory(&mLight, sizeof(D3DLIGHT9));
	mLight.Type = D3DLIGHT_DIRECTIONAL;
	mLight.Diffuse = D3DXCOLOR(0.75f, 0.25f, 0.5f, 1.0f);
	D3DXVECTOR3 vecDir = D3DXVECTOR3(5.0f, -3.0f, 1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&mLight.Direction, &vecDir);
	pDevice->SetLight(index, &mLight);
	pDevice->LightEnable(index, enabled);
}

void DirectionalLight::Update(const LPDIRECT3DDEVICE9 pDevice) {
	if (!(GetAsyncKeyState(VK_F2) & 0x8000) && mWasToggled) {
		mEnabled = !mEnabled;
		mWasToggled = !mWasToggled;
		pDevice->LightEnable(mIndex, mEnabled);
	} else if ((GetAsyncKeyState(VK_F2) & 0x8000) && !mWasToggled) {
		mWasToggled = true;
	}
}