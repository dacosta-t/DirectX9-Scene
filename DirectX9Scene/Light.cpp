#include "Light.h"

Light::Light(const LPDIRECT3DDEVICE9 pDevice, const int index, bool enabled)
	: mIndex(index)
	, mEnabled(enabled)
{
	// -1 index is ambient light
	if (index == -1) {
		pDevice->SetRenderState(D3DRS_AMBIENT, 0x999999);
	}
}

void Light::Update(const LPDIRECT3DDEVICE9 pDevice)
{
	if (!(GetAsyncKeyState(VK_F1) & 0x8000) && mWasToggled) {
		mEnabled = !mEnabled;
		mWasToggled = !mWasToggled;
		pDevice->SetRenderState(D3DRS_AMBIENT, mEnabled ? 0x999999 : 0);
	} else if ((GetAsyncKeyState(VK_F1) & 0x8000) && !mWasToggled) {
		mWasToggled = true;
	}
}