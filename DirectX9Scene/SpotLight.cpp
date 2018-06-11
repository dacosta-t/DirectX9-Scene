#include "SpotLight.h"

SpotLight::SpotLight(const LPDIRECT3DDEVICE9 pDevice, const int index, const bool enabled)
	: Light::Light(pDevice, index, enabled)
{
	ZeroMemory(&mLight, sizeof(D3DLIGHT9));
	mLight.Type = D3DLIGHT_SPOT;
	mLight.Diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	mLight.Position = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
	mLight.Direction = D3DXVECTOR3(-0.5f, 1.0f, 10.0f);
	mLight.Range = 1000.0f;
	mLight.Attenuation0 = 0.0f;
	mLight.Attenuation1 = 0.0f;
	mLight.Attenuation2 = 0.125f;
	mLight.Phi = D3DXToRadian(40.0f);
	mLight.Theta = D3DXToRadian(20.0f);
	mLight.Falloff = 1.0f;
	pDevice->SetLight(index, &mLight);
	pDevice->LightEnable(index, enabled);
}

void SpotLight::Update(const LPDIRECT3DDEVICE9 pDevice) {
	if (!(GetAsyncKeyState(VK_F4) & 0x8000) && mWasToggled) {
		mEnabled = !mEnabled;
		mWasToggled = !mWasToggled;
		pDevice->LightEnable(mIndex, mEnabled);
	} else if ((GetAsyncKeyState(VK_F4) & 0x8000) && !mWasToggled) {
		mWasToggled = true;
	}
}