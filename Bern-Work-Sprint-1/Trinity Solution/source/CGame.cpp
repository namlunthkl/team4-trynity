////////////////////////////////////////////////////////////////////////
//    File Name				:	"CGame.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/06 - 10:45 AM
//    Purpose				:	To contain all basic game-related data
//								and code, even though it just calls
//								a lot of functions from other classes
////////////////////////////////////////////////////////////////////////

// Precompiled header
#include "StdAfx.h"

// Include header file
#include "CGame.h"
#include "States\CMainMenuState.h"
#include "States\CGameplayState.h"

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Singleton's accessor
//	Return		:	Pointer to the singleton's instance
////////////////////////////////////////////////////////////////////////
CGame* CGame::GetInstance(void)
{
	// Lazy instantiation
	static CGame instance;
	return &instance;
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Initialize the game using window's parameters
//	Parameters	:	hWnd - Window handle, hInstance - Instance handle,
//					bIsWindowed - False means full screen
//	Return		:	False if initialization failed, true if succeeded
////////////////////////////////////////////////////////////////////////
bool CGame::Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth,
	int nScreenHeight, bool bIsWindowed)
{
	// Set window variables
	m_hWnd = hWnd;
	SetScreenWidth(nScreenWidth);
	SetScreenHeight(nScreenHeight);
	SetIsWindowed(bIsWindowed);

	// Set gameplay variables
	SetShowHUD(true);
	SetMapLocation(2);	// 0 thru 2
	SetMusicVolume(80);	// 0 thru 100
	SetSoundVolume(100);// 0 thru 100

	// Initialize all the resource managers
	D3D->InitDirect3D(hWnd, nScreenWidth, nScreenHeight, bIsWindowed, true);
	TEX_MNG->InitTextureManager(D3D->GetDirect3DDevice(), D3D->GetSprite());
	INPUT->InitDirectInput(hWnd, hInstance, DI_KEYBOARD | DI_MOUSE);
	AUDIO->InitXAudio2();

	// Change state to Main Menu
	ChangeState(CGameplayState::GetInstance());

	// Example of map initialization
#if 0
	// HACK
	// Remove later
	CTileset* tileset = new CTileset(TEX_MNG->LoadTexture("tile.png", D3DCOLOR_XRGB(255, 255, 255)), 9, 8, 32, 32);
	a.Initialize("map.txt", tileset, 0, 0);
#endif

	// Get time stamps
	// It's more accurate if it's on the end
	m_Timer.m_dwTimeStamp = timeGetTime();
	m_Timer.m_dwPreviousTimeStamp = timeGetTime();

	// If everything succeeded and Game was
	// initialized, return true
	return true;
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Run the game - call Input(), Update() and Render()
//					Also time the game to call Update with fElapsedTime
//	Return		:	True if game should continue running
//					False if game should quit
////////////////////////////////////////////////////////////////////////
bool CGame::Main(void)
{
	// Calculate elapsed time
	DWORD dwStartTimeStamp = timeGetTime();
	m_Timer.m_fElapsedTime = (float)(dwStartTimeStamp - m_Timer.m_dwPreviousTimeStamp) / 1000.0f;
	m_Timer.m_dwPreviousTimeStamp = dwStartTimeStamp;

	// If on debug mode, cap elapsed time
#ifdef _DEBUG
	if(m_Timer.m_fElapsedTime > 0.125f)
		m_Timer.m_fElapsedTime = 0.125f;
#endif // _DEBUG

	//	Execution of the Game
	//		Get Input
	//		If it returns false, quit the game
	if(!Input())
		return false;
	//		Update variables
	Update();
	//		Draw to the screen
	Render();

	// Count FPS
	m_Timer.m_nFrameCounter++;
	// Every second...
	if(timeGetTime() - m_Timer.m_dwFPSTimeStamp > 1000)
	{
		// Remember the previous frame count
		m_Timer.m_nFPS = m_Timer.m_nFrameCounter;
		// Reset the frame count
		m_Timer.m_nFrameCounter = 0;
		// Get a new time stamp
		m_Timer.m_dwFPSTimeStamp = timeGetTime();
	}

	// If everything succeeded and Game should keep
	// running, return true
	return true;
}


////////////////////////////////////////////////////////////////////////
//	Purpose		:	Call the current state's Input method and exit the
//					game if needed (Escape pressed in main menu, for
//					example)
//	Return		:	True if game should continue running
//					False if game should quit
////////////////////////////////////////////////////////////////////////
bool CGame::Input(void)
{
	INPUT->ReadDevices();
	m_pCurrentState->Input();
	return true;
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Call the current state's Update method, thus
//					updating the game independent of each state it's in
////////////////////////////////////////////////////////////////////////
void CGame::Update(void)
{
	m_pCurrentState->Update(m_Timer.m_fElapsedTime);
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Call the current state's Render method, thus
//					rendering the game independent of each state it's in
////////////////////////////////////////////////////////////////////////
void CGame::Render(void)
{
	// This code is clearing the screen to a dark grey color
	// When DirectX has a problem and is not rendering anything,
	// the screen is just cleared as black, so we'll be able to
	// differentiate
	D3D->Clear(50,50,50);
	D3D->DeviceBegin();
	D3D->SpriteBegin();

	m_pCurrentState->Render();

	
#if 0
	// HACK
	a.Render();
#endif

	D3D->SpriteEnd();
	D3D->DeviceEnd();
	D3D->Present();
}



////////////////////////////////////////////////////////////////////////
//	Purpose		:	Shutdown everything that was initialized
////////////////////////////////////////////////////////////////////////
void CGame::Shutdown(void)
{
	if(D3D)
		D3D->ShutdownDirect3D();

	if(TEX_MNG)
		TEX_MNG->ShutdownTextureManager();

	if(INPUT)
		INPUT->ShutdownDirectInput();
	
	if(AUDIO)
		AUDIO->ShutdownXAudio2();
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Shutdown the game's current state, set the pointer
//					to pNewState and initialize it
//	Parameters	:	pNewState - pointer to new state's instance
////////////////////////////////////////////////////////////////////////
void CGame::ChangeState(IGameState* pNewState)
{
	if(m_pCurrentState != NULL)
	{
		m_pCurrentState->Exit();
	}
	m_pCurrentState = pNewState;
	if(m_pCurrentState != NULL)
	{
		m_pCurrentState->Enter();
	}
}