#pragma once

#include <list>
#include <string>

#include "Includes.h"

struct Particle
{
	D3DXVECTOR3 position;
	D3DCOLOR    color;
};

struct BoundingBox
{
	BoundingBox();

	bool isPointInside(D3DXVECTOR3& p);

	D3DXVECTOR3 min;
	D3DXVECTOR3 max;
};

struct Attribute
{
	Attribute()
	{
		lifeTime = 0.0f;
		age = 0.0f;
		isAlive = true;
	}

	D3DXVECTOR3 position;
	D3DXVECTOR3 velocity;
	D3DXVECTOR3 acceleration;
	float       lifeTime;     // how long the particle lives for before dying  
	float       age;          // current age of the particle  
	D3DXCOLOR   color;        // current color of the particle   
	D3DXCOLOR   colorFade;    // how the color fades with respect to time
	bool        isAlive;
};

class ParticleEngine {
public:
	/** Constructs objects of type ParticleEngine. */
	ParticleEngine() = default;

	/** Destructor for objects of type ParticleEngine.
		Releases all memory allocated by the particle engine.
	*/
	virtual ~ParticleEngine();

	/** Initializes the particle engine. 
		
		@param device - The graphics device
		@param texFileName - Texture filename for the particle

		@return pass or fail result of initialization
	*/
	virtual HRESULT Init(LPDIRECT3DDEVICE9 device, const char* texFileName);

	/** Gets the active state of the particle system.
		
		@return whether the particle system is active or not
	*/
	bool IsActive();

	/** Resets the particle engine. */
	virtual void Reset();

	/** Respawns dead particles. 
	
		@param attribute - Attribute struct of the particles
	*/
	virtual void ResetParticle(Attribute* attribute) = 0;

	/** Adds particle to the engine. */
	virtual void AddParticle();

	/** Updates the particle engine. 
		
		@param deltaTime - Delta time
	*/
	virtual void Update(float deltaTime) = 0;

	/** Sets up the render states of the graphics device.
		
		@param pDevice - The graphics device
	*/
	virtual void PreRender(LPDIRECT3DDEVICE9 pDevice);

	/** Renders the particles.

		@param pDevice - The graphics device
	*/
	virtual void Render(LPDIRECT3DDEVICE9 pDevice);

	/** Resets the render states of the graphics device.

		@param pDevice - The graphics device
	*/
	virtual void PostRender(LPDIRECT3DDEVICE9 pDevice);

	/** Gets the particles active state in the engine.

		@return whether the particles in the engine are empty
	*/
	bool IsEmpty();

	/** Gets the engine's active state.
		
		@return whether the engine is dead or not
	*/
	bool IsDead();

	/** Gets a random float between a range. 
	
		@param lowBound - Minimum bound of range
		@param highBound - Maximum bound of range

		@return random float between specified range
	*/
	float GetRandomFloat(float lowBound, float highBound);

	/** Gets a random vector and saves it to out.
	
		@param out - Vector to save result to
		@param min - Minimum vector
		@param max - Maximum vector
	*/
	void GetRandomVector(D3DXVECTOR3* out, D3DXVECTOR3* min, D3DXVECTOR3* max);

	/** Gets the float as a DWORD
	
		@param - Float to convert

		@return specified float as a DWORD
	*/
	DWORD FtoDw(float f);

protected:
	/** Removes dead particles from the engine. */
	virtual void RemoveDeadParticles();

protected:
	D3DXVECTOR3 mOrigin;
	BoundingBox mBoundingBox;
	bool mActive;
	float mEmitRate; // rate new particles are added to system
	float mSize; // size of particles
	IDirect3DTexture9* mTexture;
	LPDIRECT3DVERTEXBUFFER9 mVertexBuffer;
	std::list<Attribute> mParticles;
	int mMaxParticles; // max allowed particles system can have
	DWORD mVBufferSize; // size of vertex buffer
	DWORD mVBufferOffset; // offset in vertex buffer to lock   
	DWORD mVBufferBatchSize; // number of vertices to lock starting at mVBufferOffset
	bool mWasToggled = false; // engine was recently toggled
};