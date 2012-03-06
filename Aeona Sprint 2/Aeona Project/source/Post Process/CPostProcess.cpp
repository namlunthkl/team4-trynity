#include "StdAfx.h"
#include "..\Post Process\CPostProcess.h"
#include "..\Light System\LightEngine.h"

CPostProcess::CPostProcess(void){}
CPostProcess::~CPostProcess(void)
{
	ShutDown();
}
CPostProcess* CPostProcess::GetInstance(void)
{
	static CPostProcess instance;
	return &instance;
}

void CPostProcess::Initialize( void )
{
	// GRAB THE ACTUAL DISPLAY WIDTH
	IDirect3DSurface9* bBuffer = 0;
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &bBuffer );
	bBuffer->GetDesc( &backbuffer );
	bBuffer->Release();  // DROP REF COUNT

	// LOAD IN AN EFFECT
	D3DXCreateEffectFromFile( CSGD_Direct3D::GetInstance()->GetDirect3DDevice(), "Resource/Shaders/post.fx", 0, 0, 0, 0, &postEffect, 0 );

	// MAKE THE RENDER TARGET TEXTURE
	D3DXCreateTexture( CSGD_Direct3D::GetInstance()->GetDirect3DDevice(), backbuffer.Width, backbuffer.Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R8G8B8, D3DPOOL_DEFAULT, &renderTarget); 

	// CREATE SCREEN SPACE QUAD WITH HALF-TEXEL OFFSET
	void *mem = 0;
	struct QUAD
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR2 uv;
	};
	QUAD quadverts[] =
	{
		{ D3DXVECTOR3( -1.0f, -1.0f, 0.0f ), D3DXVECTOR2( 0 , 1) },
		{ D3DXVECTOR3( -1.0f,  1.0f, 0.0f ), D3DXVECTOR2( 0 , 0) },
		{ D3DXVECTOR3(  1.0f,  1.0f, 0.0f ), D3DXVECTOR2( 1 , 0) },
		{ D3DXVECTOR3(  1.0f, -1.0f, 0.0f ), D3DXVECTOR2( 1 , 1) }
	};
	// INDICIES FOR QUAD
	short quadindicies[] =
	{
		0,1,2, 0,2,3
	};

	// CREATE VERTEX BUFFER FOR QUAD
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->CreateVertexBuffer( unsigned int( sizeof( QUAD ) * 4 ), 0, 0, D3DPOOL_MANAGED, &quadbuff, 0 );
	mem = 0;
	quadbuff->Lock( 0, 0, &mem, 0 );
	memcpy( mem, quadverts, 4 * sizeof( QUAD ) );
	quadbuff->Unlock();

	// CREATE INDEX BUFFER FOR QUAD
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->CreateIndexBuffer( sizeof( short ) * 6, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &quadindex, 0 );
	mem = 0;
	quadindex->Lock( 0, 0, &mem, 0 );
	memcpy( mem, quadindicies, 6 * sizeof( short ) );
	quadindex->Unlock();

	// VERTEX DECLARATIONS
	D3DVERTEXELEMENT9 decl[] = 
	{ 
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->CreateVertexDeclaration(decl, &cubedecl);

	// SHADER TYPE
	techs[0] = ( "Invert" );
	techs[1] = ( "Monochrome" );
	techs[2] = ( "Sepia" );
	techs[3] = ( "ColorLoop" );
	techs[4] = ( "TronEnergy" );
	techs[5] = ( "DayCycleEffect" );
	index = 5;

	// COLOR
	LightEngine::GetInstance()->Initialize();
	colChange = 1;
	fRed = 0;
	fGreen = 0;
	fBlue = 0;

	current = 0;
	output = 0;
}
void CPostProcess::Update( void )
{
	UpdateColor();
}
void CPostProcess::Input( void )
{
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_1 ) )
	{
		index = 0;
	}
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_2 ) )
	{
		index = 1;
	}
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_3 ) )
	{
		index = 2;
	}
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_4 ) )
	{
		index = 3;
	}
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_5 ) )
	{
		index = 4;
	}
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_6 ) )
	{
		index = 5;
	}
}
void CPostProcess::BeginPostProcess( void )
{
	// STORE BACKBUFFER
	current = 0;
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->GetRenderTarget(0,&current);

	// GET TEXTURE SURFACE AND SET RENDER TARGET
	output = 0;
	renderTarget->GetSurfaceLevel(0,&output);
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetRenderTarget(0,output);

	// CLEAR RENDERTARGET
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->Clear( 0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 ); // MODIFY FOR ZBUFFER
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->BeginScene();
}
void CPostProcess::EndPostProcess( void )
{
	// PRESENT BACKBUFFER
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->EndScene();

	// RESTORE BACKBUFFER
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetRenderTarget( 0, current );

	// DROP REF COUNTS
	current->Release();
	output->Release();

	// CLEAR BACKBUFFER
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->Clear( 0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,255,0), 1.0f, 0);	// MODIFY FOR ZBUFFER
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->BeginScene();

	// SET THE TECHNIQUE TO THE PROPER EFFECT
	postEffect->SetTechnique( techs[index] );

	// RENDER QUAD WITH POST SHADER
	unsigned passes(0);
	postEffect->Begin(&passes, 0);
	for(unsigned i(0); i<passes; ++i)
	{
		postEffect->BeginPass(i);
		postEffect->SetTexture( "gDiffuseTexture", renderTarget );

		postEffect->SetFloat( "gTime" , CGame::GetInstance()->GetTimer().m_fElapsedTime );
		postEffect->SetFloat( "gRed" , fRed );
		postEffect->SetFloat( "gGreen" , fGreen );
		postEffect->SetFloat( "gBlue" , fBlue );

		postEffect->SetFloat( "gAmbientA", LightEngine::GetInstance()->GetAmbientAlpha() );
		postEffect->SetFloat( "gAmbientR", LightEngine::GetInstance()->GetAmbientRed() );
		postEffect->SetFloat( "gAmbientG", LightEngine::GetInstance()->GetAmbientGreen() );
		postEffect->SetFloat( "gAmbientB", LightEngine::GetInstance()->GetAmbientBlue() );

		postEffect->SetFloat( "gPointA", LightEngine::GetInstance()->GetPointAlpha() );
		postEffect->SetFloat( "gPointR", LightEngine::GetInstance()->GetPointRed() );
		postEffect->SetFloat( "gPointG", LightEngine::GetInstance()->GetPointGreen() );
		postEffect->SetFloat( "gPointB", LightEngine::GetInstance()->GetPointBlue() );

		postEffect->SetFloat( "gPointPosX", LightEngine::GetInstance()->GetPointPosX() );
		postEffect->SetFloat( "gPointPosY", LightEngine::GetInstance()->GetPointPosY() );

		postEffect->CommitChanges();
		CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetVertexDeclaration(cubedecl);
		CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetStreamSource(0,quadbuff,0,20);
		CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetIndices( quadindex );
		CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2 );
		postEffect->EndPass();
	}
	postEffect->End();
}
void CPostProcess::ShutDown( void )
{
	SAFE_RELEASE( quadbuff );
	SAFE_RELEASE( quadindex );
	SAFE_RELEASE( cubedecl );
	SAFE_RELEASE( postEffect );
}

void CPostProcess::UpdateColor()
{

	switch( colChange )
	{
	case 1 :
		{
			fRed   += CGame::GetInstance()->GetTimer().m_fElapsedTime * 1.0f;
			fGreen -= CGame::GetInstance()->GetTimer().m_fElapsedTime * 1.0f;
			fBlue  -= CGame::GetInstance()->GetTimer().m_fElapsedTime * 1.0f;

			if( fBlue <= 0.0f )
			{
				fBlue = 0;
			}
			if( fGreen <= 0.0f )
			{
				fGreen = 0;
			}
			if( fRed >= 1.0f )
			{
				colChange = 2;
			}
		}
		break;	

	case 2 :
		{
			fRed   -= CGame::GetInstance()->GetTimer().m_fElapsedTime * 1.0f;
			fGreen += CGame::GetInstance()->GetTimer().m_fElapsedTime * 1.0f;
			fBlue  -= CGame::GetInstance()->GetTimer().m_fElapsedTime * 1.0f;
			if( fRed <= 0.0f )
			{
				fRed = 0;
			}
			if( fBlue <= 0.0f )
			{
				fBlue = 0;
			}
			if( fGreen >= 1.0f )
			{
				colChange = 3;
			}
		}
		break;

	case 3 :
		{
			fRed   -= CGame::GetInstance()->GetTimer().m_fElapsedTime * 1.0f;
			fGreen -= CGame::GetInstance()->GetTimer().m_fElapsedTime * 1.0f;
			fBlue  += CGame::GetInstance()->GetTimer().m_fElapsedTime * 1.0f;
			if( fRed <= 0.0f )
			{
				fRed = 0;
			}
			if( fGreen <= 0.0f )
			{
				fGreen = 0;
			}
			if( fBlue >= 1.0f )
			{
				colChange = 1;
			}
		}
		break;
	}
}