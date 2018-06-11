#pragma once

#include "ParticleEngine.h"

class Snow : public ParticleEngine {
public:
	/** Constructor for objects of type Snow.

		@param boundingBox - Bounding box of the snow
		@param numParticles - Number of particles to render
	*/
	Snow(BoundingBox* boundingBox, int numParticles);

	/** Default destructor. */
	virtual ~Snow() = default;

	/** Respawns dead particles.

		@param attribute - Attribute struct of the particles
	*/
	void ResetParticle(Attribute* attribute);

	/** Updates the fireworks particles.

		@param timeDelta - Delta time
	*/
	void Update(float deltaTime);
};