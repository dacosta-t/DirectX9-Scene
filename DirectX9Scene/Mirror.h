#pragma once
#include <vector>

#include "Includes.h"
#include "Model.h"

struct Vertex {
	Vertex() {
	}

	Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v) {
		_x = x;
		_y = y;
		_z = z;
		_nx = nx;
		_ny = ny;
		_nz = nz;
		_u = u;
		_v = v;
	}

	// x, y, z coords
	float _x, _y, _z;
	// normalized x, y, z coords
	float _nx, _ny, _nz;
	// u, v coords
	float _u, _v;
};

/**
	Mirror
	Emulates a mirror to reflect models off of.
*/
class Mirror {
public:
	/** Constructor for objects of type Mirror. 
	
		@param pDevice - The graphics device
	*/
	Mirror(const LPDIRECT3DDEVICE9 pDevice);

	/** Destructor for objects of type Mirror.
		Releases all memory allocated by the mirror.
	*/
	virtual ~Mirror();

	/** Renders the mirror faces. 
	
		@param pDevice - The graphics device
	*/
	void Render(const LPDIRECT3DDEVICE9 pDevice);

	/** Renders the reflections of the models. 
	
		@param pDevice - The graphics device
		@param models - List of models to render
	*/
	void RenderReflection(const LPDIRECT3DDEVICE9 pDevice, std::vector<Model*> models);

private:
	IDirect3DVertexBuffer9* mVertexBuffer = 0; // Vertex buffer
	IDirect3DTexture9* mTexture = 0; // Mirror texture
	D3DMATERIAL9 mMaterial; // Mirror material
};