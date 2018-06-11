#include "ParticleEngine.h"

ParticleEngine::~ParticleEngine()
{
	if (mVertexBuffer) {
		mVertexBuffer->Release();
	}
	if (mTexture) {
		mTexture->Release();
	}
}

HRESULT ParticleEngine::Init(LPDIRECT3DDEVICE9 pDevice, const char* texFileName)
{
	// vertex buffer's size does not equal the number of particles in our system.  We
	// use the vertex buffer to draw a portion of our particles at a time.  The arbitrary
	// size we choose for the vertex buffer is specified by the _vbSize variable.

	HRESULT hr = 0;

	hr = pDevice->CreateVertexBuffer(
		mVBufferSize * sizeof(Particle),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		D3DFVF_XYZ | D3DFVF_DIFFUSE,
		D3DPOOL_DEFAULT, // D3DPOOL_MANAGED can't be used with D3DUSAGE_DYNAMIC 
		&mVertexBuffer,
		0);

	if (FAILED(hr)) {
		OutputDebugString("Failed to load particle vertex buffer");
		return E_FAIL;
	}

	hr = D3DXCreateTextureFromFile(pDevice, texFileName, &mTexture);

	if (FAILED(hr)) {
		OutputDebugString("Failed to load particle texture");
		return E_FAIL;
	}

	return S_OK;
}

bool ParticleEngine::IsActive() {
	return mActive;
}

void ParticleEngine::Reset()
{
	std::list<Attribute>::iterator i;
	for (i = mParticles.begin(); i != mParticles.end(); i++) {
		ResetParticle(&(*i));
	}
}

void ParticleEngine::AddParticle()
{
	Attribute attribute;
	ResetParticle(&attribute);
	mParticles.push_back(attribute);
}

void ParticleEngine::PreRender(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	pDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(mSize));
	pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));

	// control the size of the particle relative to distance
	pDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	pDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
	pDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));

	// use alpha from texture
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void ParticleEngine::PostRender(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void ParticleEngine::Render(LPDIRECT3DDEVICE9 pDevice)
{
	//
	// Remarks:  The render method works by filling a section of the vertex buffer with data,
	//           then we render that section.  While that section is rendering we lock a new
	//           section and begin to fill that section.  Once that sections filled we render it.
	//           This process continues until all the particles have been drawn.  The benifit
	//           of this method is that we keep the video card and the CPU busy.  
	if (!mParticles.empty()) {
		// set render states
		PreRender(pDevice);

		pDevice->SetTexture(0, mTexture);
		pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		pDevice->SetStreamSource(0, mVertexBuffer, 0, sizeof(Particle));

		// render batches one by one

		// start at beginning if we're at the end of the vb
		if (mVBufferOffset >= mVBufferSize) {
			mVBufferOffset = 0;
		}

		Particle* v = 0;

		mVertexBuffer->Lock(
			mVBufferOffset * sizeof(Particle),
			mVBufferBatchSize * sizeof(Particle),
			(void**)&v,
			mVBufferOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticlesInBatch = 0;

		// Until all particles have been rendered.
		std::list<Attribute>::iterator i;
		for (i = mParticles.begin(); i != mParticles.end(); i++) {
			if (i->isAlive) {
				// Copy a batch of the living particles to the
				// next vertex buffer segment
				v->position = i->position;
				v->color = (D3DCOLOR)i->color;
				v++; // next element;

				numParticlesInBatch++; //increase batch counter

									   // if this batch full?
				if (numParticlesInBatch == mVBufferBatchSize) {
					// Draw the last batch of particles that was
					// copied to the vertex buffer. 
					mVertexBuffer->Unlock();

					pDevice->DrawPrimitive(
						D3DPT_POINTLIST,
						mVBufferOffset,
						mVBufferBatchSize);

					// While that batch is drawing, start filling the
					// next batch with particles.

					// move the offset to the start of the next batch
					mVBufferOffset += mVBufferBatchSize;

					// don't offset into memory thats outside the vb's range.
					// If we're at the end, start at the beginning.
					if (mVBufferOffset >= mVBufferSize) {
						mVBufferOffset = 0;
					}

					mVertexBuffer->Lock(
						mVBufferOffset * sizeof(Particle),
						mVBufferBatchSize * sizeof(Particle),
						(void**)&v,
						mVBufferOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0; // reset for new batch
				}
			}
		}

		mVertexBuffer->Unlock();

		// its possible that the LAST batch being filled never 
		// got rendered because the condition 
		// (numParticlesInBatch == _vbBatchSize) would not have
		// been satisfied.  We draw the last partially filled batch now.

		if (numParticlesInBatch) {
			pDevice->DrawPrimitive(
				D3DPT_POINTLIST,
				mVBufferOffset,
				numParticlesInBatch);
		}

		// next block
		mVBufferOffset += mVBufferBatchSize;

		// reset render states
		PostRender(pDevice);
	}
}

bool ParticleEngine::IsEmpty()
{
	return mParticles.empty();
}

bool ParticleEngine::IsDead()
{
	std::list<Attribute>::iterator i;
	for (i = mParticles.begin(); i != mParticles.end(); i++) {
		// is there at least one living particle?  If yes,
		// the system is not dead.
		if (i->isAlive) {
			return false;
		}
	}
	// no living particles found, the system must be dead.
	return true;
}

void ParticleEngine::RemoveDeadParticles()
{
	std::list<Attribute>::iterator i;
	i = mParticles.begin();

	while (i != mParticles.end()) {
		if (i->isAlive == false) {
			// erase returns the next iterator, so no need to
			// incrememnt to the next one ourselves.
			i = mParticles.erase(i);
		}
		else {
			i++; // next in list
		}
	}
}

float ParticleEngine::GetRandomFloat(float lowBound, float highBound)
{
	if (lowBound >= highBound) { // bad input
		return lowBound;
	}

	// get random float in [0, 1] interval
	float f = (rand() % 10000) * 0.0001f;

	// return float in [lowBound, highBound] interval. 
	return (f * (highBound - lowBound)) + lowBound;
}

void ParticleEngine::GetRandomVector(D3DXVECTOR3* out,	D3DXVECTOR3* min, D3DXVECTOR3* max)
{
	out->x = GetRandomFloat(min->x, max->x);
	out->y = GetRandomFloat(min->y, max->y);
	out->z = GetRandomFloat(min->z, max->z);
}

DWORD ParticleEngine::FtoDw(float f)
{
	return *((DWORD*)&f);
}


BoundingBox::BoundingBox()
{
	// infinite small 
	min.x = INFINITY;
	min.y = INFINITY;
	min.z = INFINITY;

	max.x = -INFINITY;
	max.y = -INFINITY;
	max.z = -INFINITY;
}

bool BoundingBox::isPointInside(D3DXVECTOR3& p)
{
	if (p.x >= min.x && p.y >= min.y && p.z >= min.z &&
		p.x <= max.x && p.y <= max.y && p.z <= max.z) {
		return true;
	} else {
		return false;
	}
}