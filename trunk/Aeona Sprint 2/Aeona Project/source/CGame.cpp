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
#include "Game Objects\CPlayer.h"
#include "Util/ByteUtil.h"
#include "Post Process/CPostProcess.h"
#include <Shlobj.h>
#include <direct.h>
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
	//phil logo
	m_fLogoTimer = 0.0f;
	m_fDerpScroll = 0.0f;
	m_uiPic = 0;
	m_bSlowdowntime = false;
	m_dwSlowdownStamp = timeGetTime();
	//basically a char that has 3 bools whether slots contain info.
	m_cLoadedOrNot = 0;
	m_uiWhichSlotAreWeLoadingDawgQuestionMark = 0;
	m_uiYoManWhichSlotAreWePlayingInBro = 0;
	//for the loading bar
	m_uiAmountLoaded = 0;
	
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
	INPUT->InitDirectInput(hWnd, hInstance, DI_KEYBOARD | DI_MOUSE | DI_JOYSTICKS);
	AUDIO->InitXAudio2();

	//	Font
	pFont1 = new CBitmapFont;

	m_imgLoadingBackground = TEX_MNG->LoadTexture("resource/LoadingRiver.jpg");
	m_imgEnemies = TEX_MNG->LoadTexture("resource/Enemies.png", D3DCOLOR_XRGB(255, 0, 255));
	m_imgEnemiesDeath = TEX_MNG->LoadTexture("resource/EnemiesDeath.png", D3DCOLOR_XRGB(255, 0, 255));

	m_sndFleshHit = AUDIO->SFXLoadSound("resource/sound/FleshHit.wav");
	m_sndDeathSplat = AUDIO->SFXLoadSound("resource/sound/DeathSplat.wav");

	// Set gameplay variables
	//SetShowHUD(true);
	//SetMapLocation(2);	// 0 thru 2
	//SetMusicVolume(80);	// 0 thru 100
	//SetSoundVolume(100);	// 0 thru 100

	ReadOptionsFromFile();

	AUDIO->MusicSetMasterVolume( GAME->GetMusicVolume()/100.0f );
	AUDIO->SFXSetMasterVolume( GAME->GetSoundVolume()/100.0f );

	CPlayer::GetInstance()->SetMaxHealth(5);
	CPlayer::GetInstance()->SetCurHealth(5);

	// Change state to Main Menu
	ChangeState(CMainMenuState::GetInstance());


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
	HRESULT hr = D3D->GetDirect3DDevice()->TestCooperativeLevel();
	if(hr != D3D_OK)
	{
		if(hr == D3DERR_DEVICENOTRESET || hr == D3DERR_DEVICELOST)
		{
			CPostProcess::GetInstance()->ReleaseTexture();
			D3D->Clear();
			CPostProcess::GetInstance()->ReCreateTexture();
		}
	}

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
				
				if( CPlayer::GetInstance()->GetCurHealth() > 0 )
				{
					if( GAME->m_uiYoManWhichSlotAreWePlayingInBro == 1 )
					{
						SaveSlot1();
					}
					else if( GAME->m_uiYoManWhichSlotAreWePlayingInBro == 2 )
					{
						SaveSlot2();
					}
					else if( GAME->m_uiYoManWhichSlotAreWePlayingInBro == 3 )
					{
						SaveSlot3();
					}
				}

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
	m_Timer.m_fGameTime += m_Timer.m_fElapsedTime;

	AUDIO->Update();

	if(m_bSlowdowntime)
	{
		if(timeGetTime() - m_dwSlowdownStamp > 2000)
			m_bSlowdowntime = false;
	}

	if(m_pCurrentState != NULL)
	{
		if(!m_bSlowdowntime)
			m_pCurrentState->Update(m_Timer.m_fElapsedTime);
		else
			m_pCurrentState->Update(m_Timer.m_fElapsedTime * 0.1f);
	}
}

void CGame::SlowDownFreakingTimeBro(void)
{
	m_bSlowdowntime = true;
	m_dwSlowdownStamp = timeGetTime();
}


////////////////////////////////////////////////////////////////////////
//	Purpose		:	Call the current state's Render method, thus
//					rendering the game independent of each state it's in
////////////////////////////////////////////////////////////////////////
void CGame::Render(void)
{
	//TODO enhance when we have an actual inventory screen
	/*if(m_bPaused == true)
	{
		//D3D->Clear(10,10,10);
	}
	else */


	if(dynamic_cast<CGameplayState*>(m_pCurrentState))
	{
		m_pCurrentState->Render();
	}
	else if(m_pCurrentState != nullptr)
	{
		// This code is clearing the screen to a dark grey color
		// When DirectX has a problem and is not rendering anything,
		// the screen is just cleared as black, so we'll be able to
		// differentiate
		D3D->Clear(0,0,0);
		D3D->DeviceBegin();
		D3D->SpriteBegin();

		m_pCurrentState->Render();

		D3D->GetSprite()->Flush();

#if 0
		char buffer[100];
		sprintf_s(buffer, 100, "FPS: %i", m_Timer.m_nFPS);
		D3D->DrawTextA(&buffer[0], 0, 0, 255, 0, 0);
#endif

		D3D->SpriteEnd();
		D3D->DeviceEnd();
		D3D->Present();
	}
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

	AUDIO->SFXUnloadSound(m_sndFleshHit);
	AUDIO->SFXUnloadSound(m_sndDeathSplat);
	TEX_MNG->UnloadTexture(m_imgEnemies);
	TEX_MNG->UnloadTexture(m_imgEnemiesDeath);

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
	string tempFP;
	size_t temp = 0;
	
	wchar_t* localAppData = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppData);

	char buffer[100];
	wcstombs_s(&temp,buffer,100,localAppData,100);

	CoTaskMemFree(static_cast<void*>(localAppData));
	tempFP = buffer;
	tempFP += "\\Aeona";
	_mkdir(tempFP.c_str());
	tempFP += "\\option.txt";
	ofstream foutOptions(tempFP.c_str(), ios_base::out | ios_base::trunc);

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
	string tempFP;
	size_t temp = 0;

	wchar_t* localAppData = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE , NULL, &localAppData);

	char buffer[100];
	wcstombs_s(&temp,buffer,100,localAppData,100);

	CoTaskMemFree(static_cast<void*>(localAppData));

	tempFP = buffer;
	tempFP += "\\Aeona";
	_mkdir(tempFP.c_str());
	tempFP += "\\option.txt";
	ifstream finOptions(tempFP.c_str(), ios_base::in);

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
		if(cTempMapLocation == 0 || cTempMapLocation == 1)
			GAME->SetMapLocation( cTempMapLocation == 1 ? true : false );
		else
			GAME->SetMapLocation( 1 );
		if(cTempMusicVolume >= 0 && cTempMusicVolume <= 100)
			GAME->SetMusicVolume( cTempMusicVolume );
		else
			GAME->SetMusicVolume( 80 );
		if(cTempSoundVolume >= 0 && cTempSoundVolume <= 100)
			GAME->SetSoundVolume( cTempSoundVolume );
		else
			GAME->SetSoundVolume( 100 );
	}
	else
	{
			GAME->SetShowHUD( true );
			GAME->SetMapLocation( 1 );
			GAME->SetMusicVolume( 50 );
			GAME->SetSoundVolume( 80 );
	}
}

void CGame::LoadSlot1()
{
	string tempFP;
	size_t temp = 0;

	wchar_t* localAppData = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppData);

	char buffer[100];
	wcstombs_s(&temp,buffer,100,localAppData,100);

	CoTaskMemFree(static_cast<void*>(localAppData));
	tempFP = buffer;
	tempFP += "\\Aeona";
	_mkdir(tempFP.c_str());
	tempFP += "\\save1.txt";

	ifstream finStuff(tempFP.c_str(), ios_base::in);
	if(finStuff.is_open())
	{
		bool nope;
		finStuff >> nope;
		finStuff >> CPlayer::GetInstance()->m_byteWeapons;
		finStuff >> CPlayer::GetInstance()->m_byteMasks;
		finStuff >> CPlayer::GetInstance()->m_uiCurrentWeapon;
		finStuff >> CPlayer::GetInstance()->m_uiCurrentMask;
		finStuff >> CPlayer::GetInstance()->m_uiNumPotions;

		finStuff.close();
	}
}
void CGame::LoadSlot2()
{
	string tempFP;
	size_t temp = 0;

	wchar_t* localAppData = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppData);

	char buffer[100];
	wcstombs_s(&temp,buffer,100,localAppData,100);

	CoTaskMemFree(static_cast<void*>(localAppData));
	tempFP = buffer;
	tempFP += "\\Aeona";
	_mkdir(tempFP.c_str());
	tempFP += "\\save2.txt";

	ifstream finStuff(tempFP.c_str(), ios_base::in);
	if(finStuff.is_open())
	{
		bool nope;
		finStuff >> nope;
		finStuff >> CPlayer::GetInstance()->m_byteWeapons;
		finStuff >> CPlayer::GetInstance()->m_byteMasks;
		finStuff >> CPlayer::GetInstance()->m_uiCurrentWeapon;
		finStuff >> CPlayer::GetInstance()->m_uiCurrentMask;
		finStuff >> CPlayer::GetInstance()->m_uiNumPotions;

		finStuff.close();
	}
}
void CGame::LoadSlot3()
{
	string tempFP;
	size_t temp = 0;

	wchar_t* localAppData = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppData);

	char buffer[100];
	wcstombs_s(&temp,buffer,100,localAppData,100);

	CoTaskMemFree(static_cast<void*>(localAppData));
	tempFP = buffer;
	tempFP += "\\Aeona";
	_mkdir(tempFP.c_str());
	tempFP += "\\save3.txt";

	ifstream finStuff(tempFP.c_str(), ios_base::in);
	if(finStuff.is_open())
	{
		bool nope;
		finStuff >> nope;
		finStuff >> CPlayer::GetInstance()->m_byteWeapons;
		finStuff >> CPlayer::GetInstance()->m_byteMasks;
		finStuff >> CPlayer::GetInstance()->m_uiCurrentWeapon;
		finStuff >> CPlayer::GetInstance()->m_uiCurrentMask;
		finStuff >> CPlayer::GetInstance()->m_uiNumPotions;

		finStuff.close();
	}
}

char CGame::ReadSaveSlots()
{
	Byte cLoadedOrNot = 0;
	string tempFP;
	size_t temp = 0;

	wchar_t* localAppData = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppData);

	char buffer[100];
	wcstombs_s(&temp,buffer,100,localAppData,100);

	CoTaskMemFree(static_cast<void*>(localAppData));
	tempFP = buffer;
	tempFP += "\\Aeona";
	_mkdir(tempFP.c_str());
	string currentslot;
	currentslot += tempFP;
	currentslot += "\\save1.txt";

	ifstream finSlot1(currentslot.c_str(), ios_base::in);
	if(finSlot1.is_open())
	{
		bool bHasData = false;
		finSlot1 >> bHasData;
		if(bHasData == true)
			TurnBitOn(cLoadedOrNot, 0);
		else
			TurnBitOff(cLoadedOrNot, 0);
	}
	currentslot.clear();
	currentslot += tempFP;
	currentslot += "\\Save2.txt";

	ifstream finSlot2(currentslot.c_str(), ios_base::in);
	if(finSlot2.is_open())
	{
		bool bHasData = false;
		finSlot2 >> bHasData;
		if(bHasData == true)
			TurnBitOn(cLoadedOrNot, 1);
		else
			TurnBitOff(cLoadedOrNot, 1);
	}
	currentslot.clear();
	currentslot += tempFP;
	currentslot += "\\Save3.txt";
	ifstream finSlot3(currentslot.c_str(), ios_base::in);
	if(finSlot3.is_open())
	{
		bool bHasData = false;
		finSlot3 >> bHasData;
		if(bHasData == true)
			TurnBitOn(cLoadedOrNot, 2);
		else
			TurnBitOff(cLoadedOrNot, 2);
	}

	finSlot1.close();
	finSlot2.close();
	finSlot3.close();

	return cLoadedOrNot;
}

void CGame::DeleteSlot1()
{
	string tempFP;
	size_t temp = 0;

	wchar_t* localAppData = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppData);

	char buffer[100];
	wcstombs_s(&temp,buffer,100,localAppData,100);

	CoTaskMemFree(static_cast<void*>(localAppData));
	tempFP = buffer;
	tempFP += "\\Aeona";
	_mkdir(tempFP.c_str());
	tempFP += "\\save1.txt";

	ofstream fout(tempFP.c_str(), ios_base::out | ios_base::trunc);

	if(fout.is_open())
	{
		fout << 0;
		
		fout.close();
	}
	TurnBitOff(m_cLoadedOrNot, 0);
}
void CGame::DeleteSlot2()
{
	string tempFP;
	size_t temp = 0;

	wchar_t* localAppData = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppData);

	char buffer[100];
	wcstombs_s(&temp,buffer,100,localAppData,100);

	CoTaskMemFree(static_cast<void*>(localAppData));
	tempFP = buffer;
	tempFP += "\\Aeona";
	_mkdir(tempFP.c_str());
	tempFP += "\\save2.txt";

	ofstream fout(tempFP.c_str(), ios_base::out | ios_base::trunc);

	if(fout.is_open())
	{
		fout << 0;
		
		fout.close();
	}
	TurnBitOff(m_cLoadedOrNot, 1);
}
void CGame::DeleteSlot3()
{
	string tempFP;
	size_t temp = 0;

	wchar_t* localAppData = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppData);

	char buffer[100];
	wcstombs_s(&temp,buffer,100,localAppData,100);

	CoTaskMemFree(static_cast<void*>(localAppData));
	tempFP = buffer;
	tempFP += "\\Aeona";
	_mkdir(tempFP.c_str());
	tempFP += "\\save3.txt";

	ofstream fout(tempFP.c_str(), ios_base::out | ios_base::trunc);

	if(fout.is_open())
	{
		fout << 0;
		
		fout.close();
	}
	TurnBitOff(m_cLoadedOrNot, 2);
}

void CGame::SaveSlot1()
{
	string tempFP;
	size_t temp = 0;

	wchar_t* localAppData = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppData);

	char buffer[100];
	wcstombs_s(&temp,buffer,100,localAppData,100);

	CoTaskMemFree(static_cast<void*>(localAppData));
	tempFP = buffer;
	tempFP += "\\Aeona";
	_mkdir(tempFP.c_str());
	tempFP += "\\save1.txt";

	ofstream fout(tempFP.c_str(), ios_base::out | ios_base::trunc);

	if(fout.is_open())
	{
		fout << 1;											fout << '\n';
		fout << CPlayer::GetInstance()->m_byteWeapons;		fout << '\n';
		fout << CPlayer::GetInstance()->m_byteMasks;		fout << '\n';
		fout << CPlayer::GetInstance()->m_uiCurrentWeapon;	fout << '\n';
		fout << CPlayer::GetInstance()->m_uiCurrentMask;	fout << '\n';
		fout << CPlayer::GetInstance()->m_uiNumPotions;
		
		fout.close();
	}
	TurnBitOn(m_cLoadedOrNot, 0);
}
void CGame::SaveSlot2()
{
	string tempFP;
	size_t temp = 0;

	wchar_t* localAppData = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppData);

	char buffer[100];
	wcstombs_s(&temp,buffer,100,localAppData,100);

	CoTaskMemFree(static_cast<void*>(localAppData));
	tempFP = buffer;
	tempFP += "\\Aeona";
	_mkdir(tempFP.c_str());
	tempFP += "\\save2.txt";

	ofstream fout(tempFP.c_str(), ios_base::out | ios_base::trunc);

	if(fout.is_open())
	{
		fout << 1;											fout << '\n';
		fout << CPlayer::GetInstance()->m_byteWeapons;		fout << '\n';
		fout << CPlayer::GetInstance()->m_byteMasks;		fout << '\n';
		fout << CPlayer::GetInstance()->m_uiCurrentWeapon;	fout << '\n';
		fout << CPlayer::GetInstance()->m_uiCurrentMask;	fout << '\n';
		fout << CPlayer::GetInstance()->m_uiNumPotions;
		
		fout.close();
	}
	TurnBitOn(m_cLoadedOrNot, 1);
}
void CGame::SaveSlot3()
{
	string tempFP;
	size_t temp = 0;

	wchar_t* localAppData = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppData);

	char buffer[100];
	wcstombs_s(&temp,buffer,100,localAppData,100);

	CoTaskMemFree(static_cast<void*>(localAppData));
	tempFP = buffer;
	tempFP += "\\Aeona";
	_mkdir(tempFP.c_str());
	tempFP += "\\save3.txt";

	ofstream fout(tempFP.c_str(), ios_base::out | ios_base::trunc);

	if(fout.is_open())
	{
		fout << 1;											fout << '\n';
		fout << CPlayer::GetInstance()->m_byteWeapons;		fout << '\n';
		fout << CPlayer::GetInstance()->m_byteMasks;		fout << '\n';
		fout << CPlayer::GetInstance()->m_uiCurrentWeapon;	fout << '\n';
		fout << CPlayer::GetInstance()->m_uiCurrentMask;	fout << '\n';
		fout << CPlayer::GetInstance()->m_uiNumPotions;
		
		fout.close();
	}
	TurnBitOn(m_cLoadedOrNot, 2);
}

void CGame::RenderLoadingScreen(unsigned int uiAmountLoaded, unsigned int uiLoadScreen)
{
	D3D->Clear(0,0,0);
	D3D->DeviceBegin();
	D3D->SpriteBegin();

	//	Draw some loading screen background
	TEX_MNG->Draw(m_imgLoadingBackground, 0, 0, 1.0f, 1.0f);
	//	Necessary to render rect
	D3D->GetSprite()->Flush();

	switch(uiLoadScreen)
	{
		case 0:
		{
			RECT r;
			r.left = 128-4;
			r.top = 300-8;
			r.right = 800-128+4;
			r.bottom = 300+8;
			
			D3D->DrawRect(r, 0, 0, 0);

			RECT r2;
			r2.left = 128;
			r2.top = 300-4;
			r2.right = 128;
			while(uiAmountLoaded > 0)
			{
				--uiAmountLoaded;
				r2.right += (long)(((800-r2.right-128) * 0.175f));
			}
			r2.bottom = 300+4;

			D3D->DrawRect(r2, 160, 160, 160);
		}
	}

	D3D->SpriteEnd();
	D3D->DeviceEnd();
	D3D->Present();
}