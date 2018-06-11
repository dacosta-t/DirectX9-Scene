#include "Model.h"

Model::Model(std::string fileName, LPDIRECT3DDEVICE9 pDevice)
	: mNumMaterials(0L)
{
	LPD3DXBUFFER pD3DXMtrlBuffer;

	if (FAILED(D3DXLoadMeshFromXA(fileName.c_str(), D3DXMESH_SYSTEMMEM, pDevice, NULL, &pD3DXMtrlBuffer, NULL, &mNumMaterials, &mPMesh))) {
		if (FAILED(D3DXLoadMeshFromXA(("..\\" + fileName).c_str(), D3DXMESH_SYSTEMMEM, pDevice, NULL, &pD3DXMtrlBuffer, NULL, &mNumMaterials, &mPMesh))) {
			OutputDebugString(("Could not find " + fileName).c_str());
		}
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	mPMaterials = new D3DMATERIAL9[mNumMaterials];
	mPTextures = new LPDIRECT3DTEXTURE9[mNumMaterials];


	// Extract material properties and texture names from the pD3DXMtrlBuffer
	for (DWORD i = 0; i < mNumMaterials; i++) {
		// Copy the material
		mPMaterials[i] = d3dxMaterials[i].MatD3D;

		// Set the ambient colour for the material
		mPMaterials[i].Ambient = mPMaterials[i].Diffuse;

		mPTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL && lstrlen(d3dxMaterials[i].pTextureFilename) > 0) {
			// Create the texture
			if (FAILED(D3DXCreateTextureFromFile(pDevice, d3dxMaterials[i].pTextureFilename, &mPTextures[i]))) {
				// If texture is not in current folder, try parent folder
				const TCHAR* strPrefix = TEXT("..\\");
				const int lenPrefix = lstrlen(strPrefix);
				TCHAR strTexture[MAX_PATH];
				lstrcpyn(strTexture, strPrefix, MAX_PATH);
				lstrcpyn(strTexture + lenPrefix, d3dxMaterials[i].pTextureFilename, MAX_PATH - lenPrefix);
				if (FAILED(D3DXCreateTextureFromFile(pDevice, strTexture, &mPTextures[i]))) {
					OutputDebugString("Could not find texture map");
				}
			}
		}
	}

	D3DXMatrixTranslation(&mMatrix, 0, 0, 0);
	byte* v = 0;
	mPMesh->LockVertexBuffer(0, (void**)&v);
	D3DXComputeBoundingSphere((D3DXVECTOR3*)v, mPMesh->GetNumVertices(),
		D3DXGetFVFVertexSize(mPMesh->GetFVF()), &mBoundSphere.center, &mBoundSphere.radius);
	mPMesh->UnlockVertexBuffer();
	D3DXCreateSphere(pDevice, mBoundSphere.radius, 20, 20, &mPSphereMesh, 0);
	pD3DXMtrlBuffer->Release();
}

Model::~Model()
{
	if (mPMesh) {
		mPMesh->Release();
	}

	if (mPMaterials) {
		delete[] mPMaterials;
	}

	if (mPTextures) {
		for (DWORD i = 0; i < mNumMaterials; i++) {
			if (mPTextures[i]) {
				mPTextures[i]->Release();
			}
		}
		delete[] mPTextures;
	}
}

LPD3DXMESH Model::GetMesh() const
{
	return mPMesh;
}

D3DMATERIAL9* Model::GetMaterials() const
{
	return mPMaterials;
}

LPDIRECT3DTEXTURE9* Model::GetTextures() const
{
	return mPTextures;
}

DWORD Model::GetNumMaterials() const
{
	return mNumMaterials;
}

D3DXMATRIX Model::GetMatrix() const
{
	return mMatrix;
}

BoundingSphere Model::GetBoundingSphere() const
{
	return mBoundSphere;
}

void Model::Update(double deltaTime)
{
	if (GetAsyncKeyState('D')) {
		Move(TRANSFORM_SPEED * deltaTime, 0.0f, 0.0f);
	}
	if (GetAsyncKeyState('A')) {
		Move(-TRANSFORM_SPEED * deltaTime, 0.0f, 0.0f);
	}
	if (GetAsyncKeyState('W')) {
		Move(0.0f, TRANSFORM_SPEED * deltaTime, 0.0f);
	}
	if (GetAsyncKeyState('S')) {
		Move(0.0f, -TRANSFORM_SPEED * deltaTime, 0.0f);
	}
	if (GetAsyncKeyState('Z')) {
		Move(0.0f, 0.0f, TRANSFORM_SPEED * deltaTime);
	}
	if (GetAsyncKeyState('X')) {
		Move(0.0f, 0.0f, -TRANSFORM_SPEED * deltaTime);
	}
	if (GetAsyncKeyState('R')) {
		Rotate(TRANSFORM_SPEED * deltaTime, 0.0f, 0.0f);
	}
	if (GetAsyncKeyState('F')) {
		Rotate(-TRANSFORM_SPEED * deltaTime, 0.0f, 0.0f);
	}
	if (GetAsyncKeyState('C')) {
		Rotate(0.0f, TRANSFORM_SPEED * deltaTime, 0.0f);
	}
	if (GetAsyncKeyState('V')) {
		Rotate(0.0f, -TRANSFORM_SPEED * deltaTime, 0.0f);
	}
	if (GetAsyncKeyState('Q')) {
		Rotate(0.0f, 0.0f, TRANSFORM_SPEED * deltaTime);
	}
	if (GetAsyncKeyState('E')) {
		Rotate(0.0f, 0.0f, -TRANSFORM_SPEED * deltaTime);
	}
}

void Model::Render(LPDIRECT3DDEVICE9 pDevice) const
{
	/*D3DMATERIAL9 material;
	material.Ambient = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.25f);
	material.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.25f);
	material.Specular = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.25f);
	material.Emissive = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.25f);
	pDevice->SetMaterial(&material);
	mPSphereMesh->DrawSubset(0);*/

	for (DWORD i = 0; i < mNumMaterials; i++) {
		// Set the material and texture for this subset
		pDevice->SetMaterial(&mPMaterials[i]);
		pDevice->SetTexture(0, mPTextures[i]);

		// Draw the mesh subset
		mPMesh->DrawSubset(i);
	}
}

void Model::Move(float x, float y, float z)
{
	D3DXMATRIXA16 temp;
	D3DXMatrixTranslation(&temp, x, y, z);
	D3DXMatrixMultiply(&mMatrix, &mMatrix, &temp);
	mBoundSphere.center = D3DXVECTOR3(mMatrix(3, 0), mMatrix(3, 1), mMatrix(3, 2));
}

void Model::Rotate(float x, float y, float z)
{
	D3DXMATRIXA16 xRotation;
	D3DXMatrixRotationX(&xRotation, x);
	D3DXMATRIXA16 yRotation;
	D3DXMatrixRotationY(&yRotation, y);
	D3DXMATRIXA16 zRotation;
	D3DXMatrixRotationZ(&zRotation, z);
	D3DXMATRIXA16 temp;
	D3DXMatrixMultiply(&temp, &xRotation, &yRotation);
	D3DXMatrixMultiply(&temp, &temp, &zRotation);
	D3DXMatrixMultiply(&mMatrix, &temp, &mMatrix);
}