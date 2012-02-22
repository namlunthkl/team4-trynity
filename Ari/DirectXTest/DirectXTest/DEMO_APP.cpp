#include "DEMO_APP.h"



// defines for the ground plane
#define GROUND_WIDTH	9
#define GROUND_HEIGHT	9
#define CELL_WIDTH		1.0f
#define CELL_HEIGHT		1.0f
float mod = 0.5f;
// release COM objects safely if possible
#define SAFE_RELEASE(rel) if(rel) rel->Release(); rel = 0;
// holds eveything related to the project
//************************************************************
//************ CREATION **************************************
//************************************************************
// construct application
DEMO_APP::DEMO_APP(HINSTANCE hinst, WNDPROC proc)
{
	application = hinst; // grab application handle
	appWndProc = proc; // grab application window procedure

	//************ CREATE WINDOW ********************/
	WNDCLASSEX  wndClass;
	// register a new type of window
	ZeroMemory( &wndClass, sizeof( wndClass ) );
	wndClass.cbSize         = sizeof( WNDCLASSEX );             // size of window structure
	wndClass.lpfnWndProc    = appWndProc;						// message callback
	wndClass.lpszClassName  = L"DirectXApplication";             // class name
	wndClass.hInstance      = application;		                // handle to application
	wndClass.hCursor        = LoadCursor( NULL, IDC_ARROW );    // default cursor
	wndClass.hbrBackground  = ( HBRUSH )( COLOR_WINDOWFRAME );  // background brush
	RegisterClassEx( &wndClass );

	// create window of registered type
	window = CreateWindow(	L"DirectXApplication", L"Textures & Lights Lab4",			// class name, window title 
		WS_OVERLAPPEDWINDOW,						// window style
		CW_USEDEFAULT, CW_USEDEFAULT,               // x & y coordinates
		WINDOW_WIDTH, WINDOW_HEIGHT,                // width & height of window
		NULL, NULL,                                 // parent window & menu
		application,				                // handle to application
		NULL );

	ShowWindow( window, SW_SHOW );										// technically should be nCmdShow

	//************ CREATE D3D OBJECT ********************/
	d3dObject = Direct3DCreate9(D3D_SDK_VERSION);
	//************ CREATE D3D DEVICE ********************/
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.hDeviceWindow				= window;
	d3dpp.Windowed					= true;
	d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;
	d3dpp.EnableAutoDepthStencil	= true;

	// create the D3Ddevice
	d3dObject->CreateDevice(0, D3DDEVTYPE_HAL, window, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &d3dDevice);
	//************ INIT TIMER ********************/
	time.Reset();
	//************ LOAD EFFECTS ********************/
	D3DXCreateEffectFromFile( d3dDevice, L"Resources/Shaders/Shiny.fx", 0,0,0,0, &sphereEffect,0);
	//D3DXCreateEffectFromFile( d3dDevice, L"Resources/Shaders/Textured.fx",0,0,0,0,&groundEffect,0);
	D3DXCreateEffectFromFile( d3dDevice, L"Resources/Shaders/Textured.fx",0,0,0,0,&groundEffect,0);
	//*********** LOAD TEXTURES *********************/
	D3DXCreateCubeTextureFromFile( d3dDevice, L"Resources/Textures/Default_reflection.dds", &sphereTexture);
	D3DXCreateTextureFromFile( d3dDevice, L"Resources/Textures/Weedy Lawn.jpg", &groundTexture );

	//************ LOAD/CREATE MESHES ********************/
	//	suggested sphere values are a radius of 0.75 and 20 stacks and slices
	D3DXCreateSphere( d3dDevice, 0.1f, 30, 30, &sphereMesh, 0 );
	// TODO: call InitGround here
	InitGround();

	//************ VERTEX DECLARATIONS *******************/
	// TODO: Use the IDirect3DVertexDeclaration9* given to Create the Vertex Declaration
	D3DVERTEXELEMENT9 decl[] =
	{
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};

	d3dDevice->CreateVertexDeclaration( decl, &grounddecl );
	camera.InitializeCamera();
	// TODO: Translate the ground and torusSphere to their proper locations
	D3DXMatrixIdentity( &ground );
	D3DXMatrixTranslation( &Sphere, 0, 0.5f, 0 );
	
}
void DEMO_APP::InitGround()
{
	std::vector<D3DXVECTOR3> verts;
	std::vector<DWORD> indices;
	GenTriGrid(GROUND_WIDTH, GROUND_HEIGHT, CELL_WIDTH, CELL_HEIGHT, D3DXVECTOR3(0.0f, 0.0f, 0.0f), verts, indices);
	// Save vertex count and triangle count for DrawIndexedPrimitive arguments.
	mNumGridVertices  = GROUND_WIDTH * GROUND_HEIGHT;
	mNumGridTriangles = 8*8*2;
	// Obtain a pointer to a new vertex buffer.
	d3dDevice->CreateVertexBuffer(mNumGridVertices * sizeof(VERTUV), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &groundbuff, 0);
	// Now lock it to obtain a pointer to its internal data, and write the
	// grid's vertex data.
	VERTUV* v = 0;
	groundbuff->Lock(0, 0, (void**)&v, 0);
	float texScale = 0.5f;
	for(int i = 0; i < GROUND_WIDTH; ++i)
	{
		for(int j = 0; j < GROUND_HEIGHT; ++j)
		{
			DWORD index = i * 9 + j;
			v[index].pos.x    = verts[index].x;
			v[index].pos.y    = rand()%25 * 0.01f;
			v[index].pos.z    = verts[index].z;
			v[index].uv = D3DXVECTOR2((float)j, (float)i ) * texScale;
		}
	}
	groundbuff->Unlock();
	// Obtain a pointer to a new index buffer.
	d3dDevice->CreateIndexBuffer( mNumGridTriangles * 3 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &groundindex, 0);
	// Now lock it to obtain a pointer to its internal data, and write the
	// grid's index data.
	WORD* k = 0;
	groundindex->Lock(0, 0, (void**)&k, 0);
	for(DWORD i = 0; i < mNumGridTriangles*3; ++i)
		k[i] = (WORD)indices[i];
	groundindex->Unlock();
}
//************************************************************
//************ EXECUTION *************************************
//************************************************************
// update everything
bool DEMO_APP::Run()
{
	//************ UPDATE TIMER ********************/
	time.Update();
	camera.Update( (float)time.GetDeltaTime() );
	//x -= time.GetDeltaTime();
	if( GetAsyncKeyState( VK_SPACE ) )
	{
		camera.SetKillCam( true );
	}
	if( GetAsyncKeyState( VK_LEFT ) )
	{
		D3DXMATRIX ballTranslation;
		D3DXMatrixIdentity( &ballTranslation );
		D3DXMatrixTranslation( &ballTranslation, 1 * time.GetDeltaTime() , 0, 0 );
		D3DXMatrixMultiply( &Sphere, &Sphere, &ballTranslation );
	}
	if( GetAsyncKeyState( VK_RIGHT ) )
	{
		D3DXMATRIX ballTranslation;
		D3DXMatrixIdentity( &ballTranslation );
		D3DXMatrixTranslation( &ballTranslation, -1 * time.GetDeltaTime() , 0, 0 );
		D3DXMatrixMultiply( &Sphere, &Sphere, &ballTranslation );
	}
	if( GetAsyncKeyState( VK_UP ) )
	{
		D3DXMATRIX ballTranslation;
		D3DXMatrixIdentity( &ballTranslation );
		D3DXMatrixTranslation( &ballTranslation, 0, 0, -1 * time.GetDeltaTime() );
		D3DXMatrixMultiply( &Sphere, &Sphere, &ballTranslation );
	}
	if( GetAsyncKeyState( VK_DOWN ) )
	{
		D3DXMATRIX ballTranslation;
		D3DXMatrixIdentity( &ballTranslation );
		D3DXMatrixTranslation( &ballTranslation, 0 , 0, 1 * time.GetDeltaTime() );
		D3DXMatrixMultiply( &Sphere, &Sphere, &ballTranslation );
	}

	camera.SetCameraPositionX( Sphere._41 );
	camera.SetCameraPositionY( Sphere._43 );

	// clear backbuffer
	d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);	// modify for zbuffer
	d3dDevice->BeginScene();
	// TODO: Render the Sphere here
	RenderSphere();
	// TODO: Render the ground
	RenderGround();
	// present backbuffer
	d3dDevice->EndScene();
	d3dDevice->Present(0,0,0,0);

	return true; // continue execution
}
void DEMO_APP::RenderSphere()
{
	// grab inverse camer matrix
	D3DXMATRIX camInv;
	D3DXMatrixInverse(&camInv,0,&camera.GetCamera());
	// TODO: render torusSphere with Shiny shader
	unsigned int passes(0);
	if( sphereEffect )
	{
		sphereEffect->Begin( &passes, 0 );

		for( unsigned i(0); i < passes; ++i )
		{
			sphereEffect->BeginPass(i);
			sphereEffect->SetMatrix( "gWorld", &Sphere );
			sphereEffect->SetMatrix( "gViewProjection", &( camera.GetCamera() * camera.GetProjection() ) );
			sphereEffect->SetMatrix( "gViewInverse", &camInv );
			sphereEffect->SetTexture( "gReflectTexture" , sphereTexture );
			sphereEffect->CommitChanges();
			sphereMesh->DrawSubset(0);
			sphereEffect->EndPass();
		}
		sphereEffect->End();
	}

}
void DEMO_APP::RenderGround()
{
	// grab inverse camer matrix
	D3DXMATRIX camInv;
	D3DXMatrixInverse(&camInv,0,&camera.GetCamera());
	// TODO: render ground with textured shader
	unsigned passes(0);
	groundEffect->Begin( &passes, 0 );
	for( unsigned i(0); i < passes; ++i )
	{
		groundEffect->BeginPass(i);
		groundEffect->SetMatrix( "gWorld", &(ground) );
		groundEffect->SetMatrix( "gViewProjection", &( camera.GetCamera() * camera.GetProjection() ));
		groundEffect->SetMatrix( "gViewInverse", &camInv );
		groundEffect->SetTexture( "gDiffuseTexture", groundTexture );
		groundEffect->CommitChanges();

		d3dDevice->SetVertexDeclaration( grounddecl );
		d3dDevice->SetStreamSource( 0, groundbuff, 0, sizeof( VERTUV ) );
		d3dDevice->SetIndices( groundindex );
		d3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, mNumGridVertices, 0, mNumGridTriangles );

		groundEffect->EndPass();
	}
	groundEffect->End();
}
//************************************************************
//************ DESTRUCTION ***********************************
//************************************************************
// shutdown eveything
DEMO_APP::~DEMO_APP()
{
	//release all COM objects and dynamic memory
	SAFE_RELEASE(d3dObject);
	SAFE_RELEASE(d3dDevice);
	SAFE_RELEASE(groundbuff);
	SAFE_RELEASE(groundindex);
	SAFE_RELEASE(grounddecl);
	SAFE_RELEASE(sphereMesh);
	SAFE_RELEASE(sphereEffect);
	SAFE_RELEASE(groundEffect);
	SAFE_RELEASE(sphereTexture);
	SAFE_RELEASE(groundTexture);
	// window cleanup
	UnregisterClass( L"DirectXApplication", application ); // unregister window
}
void DEMO_APP::GenTriGrid( int numVertRows, int numVertCols,float dx, float dz,	const D3DXVECTOR3& center, std::vector<D3DXVECTOR3>& verts, std::vector<DWORD>& indices )
{
	int numVertices = numVertRows*numVertCols;
	int numCellRows = numVertRows-1;
	int numCellCols = numVertCols-1;

	int numTris = numCellRows*numCellCols*2;

	float width = (float)numCellCols * dx;
	float depth = (float)numCellRows * dz;

	// Build verts
	verts.resize( numVertices );

	// Offsets to translate grid from quadrant 4 to center of 
	// coordinate system.
	float xOffset = -width * 0.5f; 
	float zOffset =  depth * 0.5f;

	int k = 0;
	for(float i = 0; i < numVertRows; ++i)
	{
		for(float j = 0; j < numVertCols; ++j)
		{
			// Negate the depth coordinate to put in quadrant four.  
			// Then offset to center about coordinate system.
			verts[k].x =  j * dx + xOffset;
			verts[k].z = -i * dz + zOffset;
			verts[k].y =  0.0f;

			// Translate so that the center of the grid is at the
			// specified 'center' parameter.
			D3DXMATRIX T;
			D3DXMatrixTranslation(&T, center.x, center.y, center.z);
			D3DXVec3TransformCoord(&verts[k], &verts[k], &T);

			++k; // Next vertex
		}
	}

	//===========================================
	// Build indices.

	indices.resize(numTris * 3);

	// Generate indices for each quad.
	k = 0;
	for(DWORD i = 0; i < (DWORD)numCellRows; ++i)
	{
		for(DWORD j = 0; j < (DWORD)numCellCols; ++j)
		{
			indices[k]     =   i   * numVertCols + j;
			indices[k + 1] =   i   * numVertCols + j + 1;
			indices[k + 2] = (i+1) * numVertCols + j;

			indices[k + 3] = (i+1) * numVertCols + j;
			indices[k + 4] =   i   * numVertCols + j + 1;
			indices[k + 5] = (i+1) * numVertCols + j + 1;

			// next quad
			k += 6;
		}
	}
}