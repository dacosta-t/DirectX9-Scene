#include "Mirror.h"

Mirror::Mirror(const LPDIRECT3DDEVICE9 pDevice)
{
	mMaterial.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mMaterial.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mMaterial.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mMaterial.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	mMaterial.Power = 2.0f;

	pDevice->CreateVertexBuffer(36 * sizeof(Vertex), 0, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, D3DPOOL_MANAGED, &mVertexBuffer, 0);

	Vertex* v = 0;
	
	mVertexBuffer->Lock(0, 0, (void**)&v, 0);
	// Left Face
	v[0] = Vertex(-2.5f, -3.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = Vertex(-2.5f, 2.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = Vertex(-2.5f, 2.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	v[3] = Vertex(-2.5f, -3.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[4] = Vertex(-2.5f, 2.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[5] = Vertex(-2.5f, -3.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	//Front Face
	v[6] = Vertex(-2.5f, -3.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[7] = Vertex(-2.5f, 2.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[8] = Vertex(2.5f, 2.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	v[9] = Vertex(-2.5f, -3.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[10] = Vertex(2.5f, 2.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[11] = Vertex(2.5f, -3.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	//Right Face
	v[12] = Vertex(2.5f, 2.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[13] = Vertex(2.5f, -3.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[14] = Vertex(2.5f, 2.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	v[15] = Vertex(2.5f, 2.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[16] = Vertex(2.5f, -3.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[17] = Vertex(2.5f, -3.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	//Back Face
	v[18] = Vertex(-2.5f, 2.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[19] = Vertex(-2.5f, -3.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[20] = Vertex(2.5f, 2.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	v[21] = Vertex(2.5f, 2.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[22] = Vertex(-2.5f, -3.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[23] = Vertex(2.5f, -3.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	//Top Face
	v[24] = Vertex(-2.5f, 2.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[25] = Vertex(-2.5f, 2.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[26] = Vertex(2.5f, 2.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	v[27] = Vertex(-2.5f, 2.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[28] = Vertex(2.5f, 2.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[29] = Vertex(2.5f, 2.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	//Bottom Face
	v[30] = Vertex(-2.5f, -3.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[31] = Vertex(-2.5f, -3.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[32] = Vertex(2.5f, -3.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	v[33] = Vertex(2.5f, -3.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[34] = Vertex(-2.5f, -3.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[35] = Vertex(2.5f, -3.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	mVertexBuffer->Unlock();

	D3DXCreateTextureFromFile(pDevice, "ice.bmp", &mTexture);
}

Mirror::~Mirror()
{
	if (mVertexBuffer) {
		mVertexBuffer->Release();
	}
	if (mTexture) {
		mTexture->Release();
	}
}

void Mirror::Render(const LPDIRECT3DDEVICE9 pDevice)
{
	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);
	pDevice->SetTransform(D3DTS_WORLD, &I);

	pDevice->SetStreamSource(0, mVertexBuffer, 0, sizeof(Vertex));
	pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1);

	for (int i = 0; i < 6; i++) {
		// Draw the mirror
		pDevice->SetMaterial(&mMaterial);
		pDevice->SetTexture(0, mTexture);
		pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, i * 6, 2);

		pDevice->SetRenderState(D3DRS_STENCILENABLE, true);
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_STENCILREF, i + 1);
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
		pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

		// Draw the mirror to the stencil reference
		pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, i * 6, 2);
	}
}

void Mirror::RenderReflection(const LPDIRECT3DDEVICE9 pDevice, std::vector<Model*> models)
{
	D3DXPLANE planes[6] = {
		{ 1.0f, 0.0f, 0.0f, 2.5f }, // Left
		{ 0.0f, 0.0f, 1.0f, 0.0f }, // Front
		{ -1.0f, 0.0f, 0.0f, 2.5f }, // Right
		{ 0.0f, 0.0f, -1.0f, 5.0f }, // Back
		{ 0.0f, -1.0f, 0.0f, 2.0f }, // Top
		{ 0.0f, 1.0f, 0.0f, 3.0f }, // Bottom
	};

	for (int i = 0; i < 6; i++) {
		pDevice->SetRenderState(D3DRS_STENCILENABLE, true);
		pDevice->SetRenderState(D3DRS_STENCILREF, i + 1);

		//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

		// only draw reflected teapot to the pixels where the mirror
		// was drawn to.
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

		// Clear depth buffer and blend the reflected model with the mirror
		pDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

		D3DXMATRIX W, R;
		D3DXMatrixReflect(&R, &planes[i]);

		pDevice->SetClipPlane(0, planes[i]);
		pDevice->SetRenderState(D3DRS_CLIPPLANEENABLE, D3DCLIPPLANE0);
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

		for (auto it = models.begin(); it != models.end(); it++) {
			Model* model = *it;
			W = model->GetMatrix() * R;

			// Draw reflected model
			pDevice->SetTransform(D3DTS_WORLD, &W);
			model->Render(pDevice);
		}

		// Restore render states.
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		pDevice->SetRenderState(D3DRS_CLIPPLANEENABLE, false);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		pDevice->SetRenderState(D3DRS_STENCILENABLE, false);
	}
}

//void Mirror::RenderReflection(const LPDIRECT3DDEVICE9 pDevice, std::vector<Model*> models)
//{
//	D3DXPLANE planes[6] = {
//		{ 1.0f, 0.0f, 0.0f, 2.5f }, // Left
//		{ 0.0f, 0.0f, 1.0f, 0.0f }, // Front
//		{ -1.0f, 0.0f, 0.0f, 2.5f }, // Right
//		{ 0.0f, 0.0f, -1.0f, 5.0f }, // Back
//		{ 0.0f, -1.0f, 0.0f, 2.0f }, // Top
//		{ 0.0f, 1.0f, 0.0f, 3.0f }, // Bottom
//	};
//
//	for (int i = 0; i < 6; i++) {
//		pDevice->SetRenderState(D3DRS_STENCILENABLE, true);
//		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
//		pDevice->SetRenderState(D3DRS_STENCILREF, i + 1);
//		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
//		pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
//		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
//		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
//		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
//
//		// disable writes to the depth and back buffers
//		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
//		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
//		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
//		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
//
//		// draw the mirror to the stencil buffer
//		D3DXMATRIX I;
//		D3DXMatrixIdentity(&I);
//		pDevice->SetTransform(D3DTS_WORLD, &I);
//
//		pDevice->SetStreamSource(0, mVertexBuffer, 0, sizeof(Vertex));
//		pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1);
//		pDevice->SetMaterial(&mMaterial);
//		pDevice->SetTexture(0, mTexture);
//		pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 6 * i, 2);
//
//		// re-enable depth writes
//		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
//
//		// only draw reflected teapot to the pixels where the mirror
//		// was drawn to.
//		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
//		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
//		D3DXMATRIX W, R;
//		D3DXMatrixReflect(&R, &planes[i]);
//
//		// Clear depth buffer and blend the reflected model with the mirror
//		pDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
//		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
//		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
//
//		pDevice->SetClipPlane(0, planes[i]);
//		pDevice->SetRenderState(D3DRS_CLIPPLANEENABLE, D3DCLIPPLANE0);
//		for (auto it = models.begin(); it != models.end(); it++) {
//			Model* model = *it;
//			W = model->GetMatrix() * R;
//
//			// Draw reflected model
//			pDevice->SetTransform(D3DTS_WORLD, &W);
//			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
//			model->Render(pDevice);
//		}
//
//		// Restore render states.
//		pDevice->SetRenderState(D3DRS_CLIPPLANEENABLE, false);
//		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
//		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
//		pDevice->SetRenderState(D3DRS_STENCILENABLE, false);
//		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
//	}
//}