#pragma once
#include "ParticleEngine.h"

class Fireworks : public ParticleEngine {
public:
	/** Constructor for objects of type Fireworks.
	
		@param origin - Origin of the particles
		@param numParticles - Number of particles to render
	*/
	Fireworks(D3DXVECTOR3* origin, int numParticles);

	/** Default destructor. */
	virtual ~Fireworks() = default;

	/** Respawns dead particles.

		@param attribute - Attribute struct of the particles
	*/
	void ResetParticle(Attribute* attribute);

	/** Updates the fireworks particles.

		@param timeDelta - Delta time
	*/
	void Update(float deltaTime);

	/** Sets up the render states of the graphics device.

		@param pDevice - The graphics device
	*/
	void PreRender(LPDIRECT3DDEVICE9 pDevice);

	/** Resets the render states of the graphics device.

		@param pDevice - The graphics device
	*/
	void PostRender(LPDIRECT3DDEVICE9 pDevice);
};