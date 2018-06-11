#pragma once
#include <string>

#include "Includes.h"

struct BoundingSphere {
	float radius;
	D3DXVECTOR3 center;
};

class Model {
public:
	/** Constructs objects of type Model.

		@param fileName - the filename/path of the mesh
		@param pDevice - The graphics device
	*/
	Model(std::string fileName, LPDIRECT3DDEVICE9 pDevice);

	/** Destructor for objects of type Model.
		Releases all memory allocated by the model.
	*/
	virtual ~Model();

	/** Gets the mesh of the model.

		@return the model's mesh
	*/
	LPD3DXMESH GetMesh() const;

	/** Gets the mesh materials of the model.

		@return the model's mesh materials
	*/
	D3DMATERIAL9* GetMaterials() const;

	/** Gets the mesh textures of the model.

		@return the model's mesh textures
	*/
	LPDIRECT3DTEXTURE9* GetTextures() const;

	/** Gets the number of materials in the model's mesh.

		@return the number of materials in the model's mesh
	*/
	DWORD GetNumMaterials() const;

	/** Gets the model's coordinate matrix.

		@return Coordinate matrix
	*/
	D3DXMATRIX GetMatrix() const;

	/** Gets the bounding sphere of the model.
		
		@return the model's bounding sphere
	*/
	BoundingSphere GetBoundingSphere() const;

	/** Updates the camera's position.

		@param deltaTime - Time in seconds
	*/
	void Update(double deltaTime);

	/** Renders the model.

		@param pDevice - Render engine graphics device
	*/
	void Render(LPDIRECT3DDEVICE9 pDevice) const;

	/** Translates the model in the specified x, y, z direction.

		@param x - Movement in x direction
		@param y - Movement in y direction
		@param z - Movement in z direction
	*/
	void Move(float x, float y, float z);

	/** Rotates the model.

		@param x - Rotation around the x-axis
		@param y - Rotation around the y-axis
		@param z - Rotation around the z-axis
	*/
	void Rotate(float x, float y, float z);

	const static int TRANSFORM_SPEED = 3; // Speed to perform transforms

private:
	LPD3DXMESH mPMesh; // Mesh
	D3DMATERIAL9* mPMaterials; // Mesh materials
	LPDIRECT3DTEXTURE9* mPTextures; // Mesh textures
	DWORD mNumMaterials; // Number of materials
	D3DXMATRIX mMatrix; // Coordinate matrix
	BoundingSphere mBoundSphere; // Bounding sphere for picking
	ID3DXMesh* mPSphereMesh; // Mesh of bounding sphere
};