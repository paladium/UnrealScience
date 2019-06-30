#include "ScreenEffect.h"

Effect::Effect(IDirect3DDevice9 &device)
{
	appDevice3D = &device;


}

bool Effect::Initialize()
{
	UINT uiBufferSize = 4 * sizeof(COLORED_VERTEX);

	if (FAILED(appDevice3D->CreateVertexBuffer(uiBufferSize,

		D3DUSAGE_WRITEONLY, D3DFVF_COLOREDVERTEX, D3DPOOL_DEFAULT, &g_lpVertexBuffer, NULL)))

		return E_FAIL;


	COLORED_VERTEX* pVertices;


	if (FAILED(g_lpVertexBuffer->Lock(0, uiBufferSize, (void**)&pVertices, 0)))
	{
		return E_FAIL;
	}

	pVertices[0].x = -1.0f; //left

	pVertices[0].y = -1.0f; //bottom
	pVertices[0].z = 0.0f;

	pVertices[0].color = 0xffff0000; //red



	pVertices[1].x = -1.0f; //left

	pVertices[1].y = 1.0f; //top

	pVertices[1].z = 0.0f;

	pVertices[1].color = 0xff0000ff; //blue



	pVertices[2].x = 1.0f; //right

	pVertices[2].y = -1.0f; //bottom

	pVertices[2].z = 0.0f;

	pVertices[2].color = 0xff00ff00; //green



	pVertices[3].x = 1.0f; //right

	pVertices[3].y = 1.0f; //top

	pVertices[3].z = 0.0f;

	pVertices[3].color = 0xffffffff; //white


	g_lpVertexBuffer->Unlock();

	appDevice3D->SetFVF(D3DFVF_COLOREDVERTEX);

	appDevice3D->SetStreamSource(0, g_lpVertexBuffer, 0, sizeof(COLORED_VERTEX));


	if (FAILED(D3DXCreateEffectFromFile(appDevice3D, path.c_str(), NULL,

		NULL, D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY, NULL, &g_lpEffect, NULL)))

		return E_FAIL;

	D3DXMatrixIdentity(&g_ShaderMatrix);


	g_lpEffect->SetMatrix("ShaderMatrix", &g_ShaderMatrix);




}

void Effect::Render()
{
	UINT uiPasses = 0;

	g_lpEffect->Begin(&uiPasses, 0);


	for (UINT uiPass = 0; uiPass < uiPasses; uiPass++)

	{

		//render an effect pass

		g_lpEffect->BeginPass(uiPass);



		//render the rectangle

		appDevice3D->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);



		g_lpEffect->EndPass();

	}

	g_lpEffect->End();

}