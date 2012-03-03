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
#include "Animation\CAnimationManager.h"
#include "Input Manager/CInputManager.h"

#include "Util/ByteUtil.h"

	///////////////////////////
	//ARI EXTRA CODE
	///////////////////////////
	#include "Camera\CCameraControl.h"
	///////////////////////////
	//END ARI EXTRA CODE
	///////////////////////////


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
	///////////////////////////
	//ARI EXTRA CODE
	///////////////////////////
	m_fCharge = 0.0f;
	///////////////////////////
	//END ARI EXTRA CODE
	///////////////////////////
	
	//basically a char that has 3 bools whether slots contain info.
	m_cLoadedOrNot = 0;
	
	// Set window variables
	m_hWnd = hWnd;
	SetScreenWidth(nScreenWidth);
	SetScreenHeight(nScreenHeight);
	SetIsWindowed(bIsWindowed);

	//	Set paused false
	m_bPaused = false;

	// Initialize all the resource managers
	D3D->InitDirect3D(hWnd, nScreenWidth, nScreenHeight, bIsWindowed, true);
	TEX_MNG->InitTextureManager(D3D->GetDirect3DDevice(), D3D->GetSprite());
	INPUT->InitDirectInput(hWnd, hInstance, DI_KEYBOARD | DI_MOUSE);
	AUDIO->InitXAudio2();

	//	Font
	pFont1 = new CBitmapFont;

	// Set gameplay variables
	//SetShowHUD(true);
	//SetMapLocation(2);	// 0 thru 2
	//SetMusicVolume(80);	// 0 thru 100
	//SetSoundVolume(100);	// 0 thru 100

	ReadOptionsFromFile();

	AUDIO->MusicSetMasterVolume( GAME->GetMusicVolume()/100.0f );
	AUDIO->SFXSetMasterVolume( GAME->GetSoundVolume()/100.0f );

	// Change state to Main Menu
	ChangeState(CMainMenuState::GetInstance());


	// Get time stamps
	// It's more accurate if it's on the end
	m_Timer.m_dwTimeStamp = timeGetTime();
	m_Timer.m_dwPreviousTimeStamp = timeGetTime();

	///////////////////////////
	//ARI EXTRA CODE
	///////////////////////////
	CCameraControl::GetInstance()->InitializeCamera( GetScreenWidth(), GetScreenHeight() );
	///////////////////////////
	//END ARI EXTRA CODE
	///////////////////////////


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
	if(m_bPaused == false)
	{
		Update();
	}
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

	///////////////////////////
	//ARI EXTRA CODE
	///////////////////////////
		if( INPUT->KeyPressed( DIK_T ) )
		{
			CCameraControl::GetInstance()->SetKillCam(true);
		}
		if( INPUT->KeyDown( DIK_C ) )
		{
			m_fCharge += 1.0f * CGame::GetInstance()->GetTimer().m_fElapsedTime;
		}
		if( INPUT->KeyUp( DIK_C ) )
		{
			m_fCharge = 0.0f;
			CCameraControl::GetInstance()->SetReleaseButton( true );
		}
		if( INPUT->KeyDown ( DIK_I ) )
		{
			CCameraControl::GetInstance()->SetPositionY( CCameraControl::GetInstance()->GetPositionY() + 0.5f );
		}
		if( INPUT->KeyDown ( DIK_K ) )
		{
			CCameraControl::GetInstance()->SetPositionY( CCameraControl::GetInstance()->GetPositionY() - 0.5f );
		}
		if( INPUT->KeyDown ( DIK_J ) )
		{
			CCameraControl::GetInstance()->SetPositionX( CCameraControl::GetInstance()->GetPositionX() + 0.5f );
		}
		if( INPUT->KeyDown ( DIK_L ) )
		{
			CCameraControl::GetInstance()->SetPositionX( CCameraControl::GetInstance()->GetPositionX() - 0.5f );
		}
	///////////////////////////
	//END ARI EXTRA CODE
	///////////////////////////

	//TODO Change later when we have actual inventory.
	if(m_bPaused == true)
	{
		if(m_pCurrentState != NULL)
		{
			if(CInputManager::GetInstance()->GetPressedPause())
			{
				m_bPaused = false;
			}
			else if(CInputManager::GetInstance()->GetPressedBack())
			{
				AUDIO->SilenceAll();
				m_bPaused = false;
				GAME->ChangeState(CMainMenuState::GetInstance());
			}
		}
	}
	else if(m_pCurrentState != NULL)
	{
		return m_pCurrentState->Input();
	}	return true;
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Call the current state's Update method, thus
//					updating the game independent of each state it's in
////////////////////////////////////////////////////////////////////////
void CGame::Update(void)
{
	if(m_pCurrentState != NULL)
	{
		m_pCurrentState->Update(m_Timer.m_fElapsedTime);
			///////////////////////////
	//ARI EXTRA CODE
	///////////////////////////
		CCameraControl::GetInstance()->Update( m_Timer.m_fElapsedTime );
		if( !CCameraControl::GetInstance()->GetKillCam() )
		{
			CCameraControl::GetInstance()->ChargeCamSequence( m_fCharge );
		}
	///////////////////////////
	//END ARI EXTRA CODE
	///////////////////////////
	}
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
	
	///////////////////////////
	//ARI EXTRA CODE
	///////////////////////////
	CCameraControl::GetInstance()->SetSpriteProjection();
	///////////////////////////
	//END ARI EXTRA CODE
	///////////////////////////
	
	D3D->SpriteBegin();
	
	///////////////////////////
	//ARI EXTRA CODE
	///////////////////////////
	D3D->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
	D3D->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);
	D3D->GetSprite()->SetTransform( &CCameraControl::GetInstance()->GetView() );
	///////////////////////////
	//END ARI EXTRA CODE
	///////////////////////////

	//TODO enhance when we have an actual inventory screen
	/*if(m_bPaused == true)
	{
		//D3D->Clear(10,10,10);
	}
	else */if(m_pCurrentState != NULL)
	{
		m_pCurrentState->Render();

		if(GAME->GetPaused() == true)
		{
			pFont1->Write("GAME IS PAUSED", 24, 2 * pFont1->GetCharHeight(), D3DCOLOR_XRGB(255, 0, 0));
			pFont1->Write("Press ESC again to resume", 32, 3 * pFont1->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
			pFont1->Write("ESC brings up player inventory!", 32, 4 * pFont1->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
			pFont1->Write("PRESS DELETE FOR MAIN MENU", 32, 6 * pFont1->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
		}
	}


	D3D->SpriteEnd();
	D3D->DeviceEnd();
	D3D->Present();
}



////////////////////////////////////////////////////////////////////////
//	Purpose		:	Shutdown everything that was initialized
////////////////////////////////////////////////////////////////////////
void CGame::Shutdown(void)
{
	if(pFont1)
	{
		delete pFont1;
		pFont1 = NULL;
	}

	CAnimationManager::GetInstance()->UnloadAll();

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

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Send the game's options to an outputted file
//	Parameters	:	
////////////////////////////////////////////////////////////////////////
void CGame::OutputOptionsToFile()
{
	ofstream foutOptions("option.txt", ios_base::out | ios_base::trunc);

	if(foutOptions.is_open())
	{
		foutOptions << GAME->GetShowHUD() << '\n' <<
		(unsigned int)(GAME->GetMapLocation()) << '\n' <<
		(unsigned int)(GAME->GetMusicVolume()) << '\n' <<
		(unsigned int)(GAME->GetSoundVolume());
		
		foutOptions.close();
	}
}

void CGame::ReadOptionsFromFile()
{
	ifstream finOptions("option.txt", ios_base::in);

	if(finOptions.is_open())
	{
		//	Make some temporary values for loading
		bool bTempShowHUD;
		unsigned int cTempMapLocation;
		unsigned int cTempMusicVolume;
		unsigned int cTempSoundVolume;
		//	Load from the txt option file, into the temporary values
		finOptions >> bTempShowHUD;
		finOptions >> cTempMapLocation;
		finOptions >> cTempMusicVolume;
		finOptions >> cTempSoundVolume;
		//	Error-check the txt option file's values, and then set them
		if(bTempShowHUD == true || bTempShowHUD == false)
			GAME->SetShowHUD( bTempShowHUD );
		else
			GAME->SetShowHUD( true );
		if(cTempMapLocation == 0 || cTempMapLocation == 1 || cTempMapLocation == 2)
			GAME->SetMapLocation( cTempMapLocation );
		else
			GAME->SetMapLocation( 2 );
		if(cTempMusicVolume >= 0 && cTempMusicVolume <= 100)
			GAME->SetMusicVolume( cTempMusicVolume );
		else
			GAME->SetMusicVolume( 80 );
		if(cTempSoundVolume >= 0 && cTempSoundVolume <= 100)
			GAME->SetSoundVolume( cTempSoundVolume );
		else
			GAME->SetSoundVolume( 100 );
	}
}

char CGame::ReadSaveSlots()
{
	Byte cLoadedOrNot = 0;

	ifstream finSlot1("save1.txt", ios_base::in);
	if(finSlot1.is_open())
	{
		bool bHasData = false;
		finSlot1 >> bHasData;
		if(bHasData == true)
			TurnBitOn(cLoadedOrNot, 0);
		else
			TurnBitOff(cLoadedOrNot, 0);
	}

	ifstream finSlot2("save2.txt", ios_base::in);
	if(finSlot2.is_open())
	{
		bool bHasData = false;
		finSlot2 >> bHasData;
		if(bHasData == true)
			TurnBitOn(cLoadedOrNot, 1);
		else
			TurnBitOff(cLoadedOrNot, 1);
	}

	ifstream finSlot3("save3.txt", ios_base::in);
	if(finSlot3.is_open())
	{
		bool bHasData = false;
		finSlot3 >> bHasData;
		if(bHasData == true)
			TurnBitOn(cLoadedOrNot, 2);
		else
			TurnBitOff(cLoadedOrNot, 2);
	}

	return cLoadedOrNot;
}

void CGame::DeleteSlot1()
{
	ofstream fout("save1.txt", ios_base::out | ios_base::trunc);

	if(fout.is_open())
	{
		fout << 0;
		
		fout.close();
	}
	TurnBitOff(m_cLoadedOrNot, 0);
}
void CGame::DeleteSlot2()
{
	ofstream fout("save2.txt", ios_base::out | ios_base::trunc);

	if(fout.is_open())
	{
		fout << 0;
		
		fout.close();
	}
	TurnBitOff(m_cLoadedOrNot, 1);
}
void CGame::DeleteSlot3()
{
	ofstream fout("save3.txt", ios_base::out | ios_base::trunc);

	if(fout.is_open())
	{
		fout << 0;
		
		fout.close();
	}
	TurnBitOff(m_cLoadedOrNot, 2);
}

void CGame::SaveSlot1()
{
	ofstream fout("save1.txt", ios_base::out | ios_base::trunc);

	if(fout.is_open())
	{
		fout << 1;
		
		fout.close();
	}
	TurnBitOn(m_cLoadedOrNot, 0);
}
void CGame::SaveSlot2()
{
	ofstream fout("save2.txt", ios_base::out | ios_base::trunc);

	if(fout.is_open())
	{
		fout << 1;
		
		fout.close();
	}
	TurnBitOn(m_cLoadedOrNot, 1);
}
void CGame::SaveSlot3()
{
	ofstream fout("save3.txt", ios_base::out | ios_base::trunc);

	if(fout.is_open())
	{
		fout << 1;
		
		fout.close();
	}
	TurnBitOn(m_cLoadedOrNot, 2);
}