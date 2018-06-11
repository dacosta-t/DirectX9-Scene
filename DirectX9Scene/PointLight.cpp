#include "PointLight.h"

PointLight::PointLight(const LPDIRECT3DDEVICE9 pDevice, const int index, const bool enabled)
	: Light::Light(pDevice, index, enabled)
{
	ZeroMemory(&mLight, sizeof(D3DLIGHT9));
	mLight.Type = D3DLIGHT_POINT;
	mLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	mLight.Position = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	mLight.Range = 1000.0f;
	mLight.Attenuation2 = 0.125f;
	pDevice->SetLight(index, &mLight);
	pDevice->LightEnable(index, enabled);
}

void PointLight::Update(const LPDIRECT3DDEVICE9 pDevice) {
	if (!(GetAsyncKeyState(VK_F3) & 0x8000) && mWasToggled) {
		mEnabled = !mEnabled;
		mWasToggled = !mWasToggled;
		pDevice->LightEnable(mIndex, mEnabled);
	} else if ((GetAsyncKeyState(VK_F3) & 0x8000) && !mWasToggled) {
		mWasToggled = true;
	}
}