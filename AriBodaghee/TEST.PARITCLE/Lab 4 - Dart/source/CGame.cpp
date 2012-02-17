/////////////////////////////////////////////////////////
//	File Name	:	"CGame.h"
//
//	Author Name	:	David Brown (DB)
//
//	Purpose		:	To contain all game related code.
/////////////////////////////////////////////////////////
#include "CGame.h"
#include "TestingState.h"

CGame::CGame(void)
{
	m_pD3D	= NULL;
	m_pTM	= NULL;
	m_pDI	= NULL;
	m_pCurState = NULL;
	m_dwTimeStamp = GetTickCount();

}
CGame::~CGame(void)
{
}
CGame* CGame::GetInstance(void)
{
	static CGame instance;
	return &instance;
}
void CGame::Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed)
{
	//	Get pointers to singletons:
	m_pD3D	= CSGD_Direct3D::GetInstance();
	m_pTM	= CSGD_TextureManager::GetInstance();
	m_pDI	= CSGD_DirectInput::GetInstance();
	m_pOM	= CSGD_ObjectManager::GetInstance();
	m_pOF	= CSGD_ObjectFactory<string, CBase>::GetInstance();

	//	Initialize singletons:
	m_pD3D->InitDirect3D(hWnd, nScreenWidth, nScreenHeight, bIsWindowed, false);
	m_pTM->InitTextureManager( m_pD3D->GetDirect3DDevice(), m_pD3D->GetSprite() );
	m_pDI->InitDirectInput(hWnd, hInstance, DI_KEYBOARD  | DI_MOUSE, DI_MOUSE );


	//ChangeState( CMainMenuState::GetInstance() );
	ChangeState( TestingState::GetInstance() );

	m_pOF->RegisterClassType<CBase>("CBase");

	m_nScreenH = nScreenHeight;
	m_nScreenW = nScreenWidth;
	m_bWindowed = bIsWindowed;

	m_dwPreviousTimeStamp = GetTickCount();
}
bool CGame::Main(void)
{
	DWORD dwStartTimeStamp = GetTickCount();
	m_fElapsedTime = (float)(dwStartTimeStamp - m_dwPreviousTimeStamp) / 1000;
	m_dwPreviousTimeStamp = dwStartTimeStamp;

	m_fGameTime += m_fElapsedTime;

	if( m_fGameTime > 2.0f )
	{
		m_fGameTime = 0.0f;
	}
	//	3 steps a game does EVERY FRAME
	//	Input
	if(Input() == false)
		return false;

	//	Update
	Update();
	//	Draw
	Render();

	return true;
}
void CGame::Shutdown(void)
{
	ChangeState( NULL );

	m_pOF->UnregisterClassType("CBase");

	m_pOF->ShutdownObjectFactory();

	if (m_pOM)
	{
		m_pOM->RemoveAllObjects();
		CSGD_ObjectManager::DeleteInstance();
		m_pOM = NULL;
	}
	//	Shutdown in opposite order
	if (m_pDI)
	{
		m_pDI->ShutdownDirectInput();
		m_pDI = NULL;
	}
	if (m_pTM)
	{
		m_pTM->ShutdownTextureManager();
		m_pTM = NULL;
	}
	if (m_pD3D)
	{
		m_pD3D->ShutdownDirect3D();
		m_pD3D = NULL;
	}

}
bool CGame::Input(void)
{
	m_pDI->ReadDevices();	// called ONLY ONCE a frame

	if (m_pDI->KeyPressed(DIK_RETURN) && (m_pDI->KeyDown(DIK_LALT) || m_pDI->KeyDown(DIK_RALT)))
	{
		m_bWindowed = !m_bWindowed;
		m_pD3D->ChangeDisplayParam(m_nScreenW, m_nScreenH, m_bWindowed);
		m_pDI->ReadDevices();
	}

	return m_pCurState->Input();
}
void CGame::Update(void)
{
		m_pCurState->Update();
}
void CGame::Render(void)
{
	m_pD3D->Clear(0, 0, 0);
	m_pD3D->DeviceBegin();
	m_pD3D->SpriteBegin();

	m_pCurState->Render();

	m_pD3D->SpriteEnd();
	m_pD3D->DeviceEnd();
	m_pD3D->Present();
}
void CGame::ChangeState( IGameState* pNewState )
{
	if( m_pCurState ) { m_pCurState->Exit(); }
	m_pCurState = pNewState;
	if( m_pCurState ) { m_pCurState->Enter(); }
}