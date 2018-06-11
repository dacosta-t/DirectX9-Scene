#include "Snow.h"

Snow::Snow(BoundingBox* boundingBox, int numParticles)
{
	mBoundingBox = *boundingBox;
	mSize = 0.25f;
	mVBufferSize = 2048;
	mVBufferOffset = 0;
	mVBufferBatchSize = 512;

	for (int i = 0; i < numParticles; i++) {
		AddParticle();
	}
}

void Snow::ResetParticle(Attribute* attribute)
{
	attribute->isAlive = true;

	// get random x, z coordinate for the position of the snow flake.
	GetRandomVector(
		&attribute->position,
		&mBoundingBox.min,
		&mBoundingBox.max);

	// no randomness for height (y-coordinate).  Snow flake
	// always starts at the top of bounding box.
	attribute->position.y = mBoundingBox.max.y;

	// snow flakes fall downwards and slightly to the right and left
	attribute->velocity.x = GetRandomFloat(-1.0f, 1.0f) * -3.0f;
	attribute->velocity.y = GetRandomFloat(0.0f, 1.0f) * -10.0f;
	attribute->velocity.z = 0.0f;

	// white snow flake
	attribute->color = D3DCOLOR_XRGB(255, 255, 255);
}

void Snow::Update(float deltaTime)
{
	if (!(GetAsyncKeyState(0x31) & 0x8000) && mWasToggled) {
		mActive = !mActive;
		mWasToggled = !mWasToggled;
	}
	else if ((GetAsyncKeyState(0x31) & 0x8000) && !mWasToggled) {
		mWasToggled = true;
	}

	if (mActive) {
		std::list<Attribute>::iterator i;
		for (i = mParticles.begin(); i != mParticles.end(); i++) {
			i->position += i->velocity * deltaTime;

			// is the point outside bounds?
			if (mBoundingBox.isPointInside(i->position) == false) {
				// nope so kill it, but we want to recycle dead 
				// particles, so respawn it instead.
				ResetParticle(&(*i));
			}
		}
	}
}