#include "Fireworks.h"

Fireworks::Fireworks(D3DXVECTOR3* origin, int numParticles)
{
	mOrigin = *origin;
	mSize = 0.2f;
	mVBufferSize = 2048;
	mVBufferOffset = 0;
	mVBufferBatchSize = 512;

	for (int i = 0; i < numParticles; i++) {
		AddParticle();
	}
}

void Fireworks::ResetParticle(Attribute* attribute)
{
	attribute->isAlive = true;
	attribute->position = mOrigin;

	D3DXVECTOR3 min = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	D3DXVECTOR3 max = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	GetRandomVector(
		&attribute->velocity,
		&min,
		&max);

	// normalize to make spherical
	D3DXVec3Normalize(
		&attribute->velocity,
		&attribute->velocity);

	attribute->velocity *= 10.0f;

	attribute->color = D3DXCOLOR(
		GetRandomFloat(0.0f, 1.0f),
		GetRandomFloat(0.0f, 1.0f),
		GetRandomFloat(0.0f, 1.0f),
		1.0f);

	attribute->age = 0.0f;
	attribute->lifeTime = 4.0f; // lives for 2 seconds
}

void Fireworks::Update(float deltaTime)
{
	std::list<Attribute>::iterator i;

	for (i = mParticles.begin(); i != mParticles.end(); i++) {
		// only update living particles
		if (i->isAlive) {
			i->position += i->velocity * deltaTime;

			i->age += deltaTime;

			if (i->age > i->lifeTime) { // kill 
				i->isAlive = false;
			}
		}
	}
}

void Fireworks::PreRender(LPDIRECT3DDEVICE9 pDevice)
{
	ParticleEngine::PreRender(pDevice);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// read, but don't write particles to z-buffer
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

void Fireworks::PostRender(LPDIRECT3DDEVICE9 pDevice)
{
	ParticleEngine::PostRender(pDevice);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}