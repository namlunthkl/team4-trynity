#ifndef DEMO_APP_H_
#define DEMO_APP_H_

#include "stdafx.h"
#include "Timer.h"
#include "CCameraControl.h"

class DEMO_APP
{
	HINSTANCE					application;
	WNDPROC						appWndProc;
	HWND						window;
	IDirect3D9					*d3dObject;
	IDirect3DDevice9			*d3dDevice;
	IDirect3DVertexBuffer9		*groundbuff;
	IDirect3DIndexBuffer9		*groundindex;
	IDirect3DVertexDeclaration9	*grounddecl;
	Timer						time;
	CCameraControl				camera;
	D3DXMATRIX					ground; 
	D3DXMATRIX					Sphere;
	// TODO: Create variables needed here
	
	DWORD mNumGridVertices;
	DWORD mNumGridTriangles;

	ID3DXMesh					*sphereMesh;

	ID3DXEffect					*sphereEffect;
	ID3DXEffect					*groundEffect;

	IDirect3DCubeTexture9		*sphereTexture;
	IDirect3DTexture9			*groundTexture;

public:
	struct VERTUV
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR2 uv;
	};

	// constructor, need application instance and wndProc
	DEMO_APP(HINSTANCE hinst, WNDPROC proc);
	// run application
	void InitGround();
	bool Run();
	void RenderGround();
	void RenderSphere();
	// builds triangle grid
	void GenTriGrid(int numVertRows, int numVertCols,
		float dx, float dz, 
		const D3DXVECTOR3& center, 
		std::vector<D3DXVECTOR3>& verts,
		std::vector<DWORD>& indices);
	// destructor
	~DEMO_APP();
};

#endif