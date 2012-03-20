////////////////////////////////////////////////////////////////////////
//    File Name				:	"CGameplayState.cpp"
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09/12 - 1:00 AM
//    Purpose				:	Contains the GameplayState
////////////////////////////////////////////////////////////////////////

// Precompiled header
#include "StdAfx.h"
#include "../StdAfx.h"
// Header file for this state
#include "CGameplayState.h"
#include "../States/CMainMenuState.h" 
// Includes
#include "../Input Manager/CInputManager.h"
#include "../Camera/CCameraControl.h"
#include "../Game Objects/CPlayer.h"
#include "../AI_States/CRandomAIState.h"
#include "../AI_States/CSwarmAIState.h"
#include "../AI_States/CJumperAIState.h"
#include "../AI_States/CLarvaAIState.h"
#include "../AI_States/CGolemAIState.h"
#include "../AI_States/CSlimeAIState.h"
#include "../AI_States/CLilBastardAIState.h"
#include "../AI_States/CSpiderAIState.h"
#include "../AI_States/CSmallSpiderAIState.h"
#include "../AI_States/CFlowerAIState.h"
#include "../AI_States/CSnowGolemAIState.h"
#include "../AI_States/CLavAGolemAIState.h"
#include "../AI_States/CRatAIState.h"

#include "../AI_States/CBossFireAI.h"

#include "../Game Objects/CObjectManager.h"
#include "../Game Objects/CGrimirNPC.h"
#include "../Game Objects/CFinalBoss.h"
#include "../Puzzles/CPuzzleManager.h"
#include "../Game Objects/CItemChest.h"
#include "../Weather System/WeatherManager.h"
#include "../Post Process/CPostProcess.h"

// Singleton Macros
#define EVENTS		CEventSystem::GetInstance()
#define MESSAGES	CMessageSystem::GetInstance()
#define PLAYER		CPlayer::GetInstance()
#define OBJECTS		CObjectManager::GetInstance()
#define CAMERA		CCameraControl::GetInstance()
#define PUZZLES		CPuzzleManager::GetInstance()
#define POSTPROCESS CPostProcess::GetInstance()
#define WEATHER		CWeatherManager::GetInstance()


// Constructor
CGameplayState::CGameplayState(void)
{
	m_bNPCTalking		= false;
	m_imgMessageBox		= -1;
	m_pFont				= nullptr;
	m_szCharName		= "";
	m_szCurrentMessage	= "";
	m_szCurrentOption	= "";
	m_fHeartTimer		= 0.0f;
	m_bGameOver = false;
	m_bVictory = false;
	m_nGameOverID = -1;
	m_nVictoryID = -1;
	m_pFont = new CBitmapFont();
}

// Initialize everything
void CGameplayState::Enter(void)
{
	// Render the loading screen
	GAME->RenderLoadingScreen( GAME->IncrementAndReturnAmountLoaded(), 0);

	// Initialize systems
	MESSAGES->InitMessageSystem(MessageProc);
	PUZZLES->InitPuzzleManager();
	WORLD->InitWorldEngine();

	// Reset variables
	m_fHeartTimer = 0.0f;
	m_bGameOver = false;
	m_bVictory = false;
	// Register for events
	EVENTS->RegisterForEvent("SpawnMessageBox", this);
	EVENTS->RegisterForEvent("destroy", this);
	EVENTS->RegisterForEvent("game.over", this);
	EVENTS->RegisterForEvent("victory", this);
	EVENTS->RegisterForEvent("get.flower", this);
	EVENTS->RegisterForEvent("get.hammer", this);
	EVENTS->RegisterForEvent("Teleport.Dungeon", this);
	EVENTS->RegisterForEvent("Teleport.Volcano", this);
	EVENTS->RegisterForEvent("Teleport.Lake", this);

	//	Load all assets
	//		Textures
	m_imgMessageBox = TEX_MNG->LoadTexture("resource/MessageBox.png");
	m_imgHUD = TEX_MNG->LoadTexture("resource/HUD_Graphic.png", D3DCOLOR_XRGB(255, 0, 255));
	m_nGameOverID = TEX_MNG->LoadTexture("resource/GameOver.png");
	m_nVictoryID = TEX_MNG->LoadTexture("resource/Victory.png");
	
	//		Sounds
	SetBGMusic(AUDIO->MusicLoadSong("resource/KSC_Beginning.xwm"));
	//SetBGMusic(AUDIO->MusicLoadSong("resource/sound/T4_M1.xwm"));

	// Initialize Player
	// (1536, 1024)		- Boss Dungeon
	// (743, 4992)		- Snow Area
	// (743, 4000)		- Testing Chests
	// (4608, 7100)		- Forest
	//PLAYER->SetPosX(1504);
	//PLAYER->SetPosY(2720);
	// ( 6144+512 , 8192-512 )	== Actual starting spot of game
	PLAYER->SetPosX(6144+512);
	PLAYER->SetPosY(8192-512);
	PLAYER->SetSpeed(200);
	PLAYER->SetWidth(30);
	PLAYER->SetHeight(30);
	PLAYER->SetAttackDamage(18);
	PLAYER->SetMaxHealth(5);
	PLAYER->SetCurHealth(5);
//#ifdef _DEBUG
//	PLAYER->SetMaxHealth(10);
//	PLAYER->SetCurHealth(10);
//#endif
	PLAYER->SetDebugMode(false);
	OBJECTS->AddObject(PLAYER);

	CFinalBoss* BOSS = new CFinalBoss(1519, 595, 40,  -1, 32, 32, true, 100, 1);
	BOSS->LoadAnimations("resource/Grey Enemy Animation.xml");
	BOSS->ChangeAIState(CBossFireAI::GetInstance());
	BOSS->SetDebugMode(false);
	OBJECTS->AddObject(BOSS);
	BOSS->Release();

	//CEnemy* pEnemy2 = new CEnemy(850, 570, 40,  -1, 50, 50, true, 75, 1);
	////pEnemy2->LoadAnimations("resource/Grey Enemy Animation.xml");
	//pEnemy2->ChangeAIState(CRatAIState::GetInstance());
	//pEnemy2->SetDebugMode(false);
	//OBJECTS->AddObject(pEnemy2);
	//pEnemy2->Release();
	//
	//
	//CEnemy* pEnemy2f = new CEnemy(850, 600, 40,  -1, 50, 50, true, 75, 1);
	////pEnemy2->LoadAnimations("resource/Grey Enemy Animation.xml");
	//pEnemy2f->ChangeAIState(CRatAIState::GetInstance());
	//pEnemy2f->SetDebugMode(false);
	//OBJECTS->AddObject(pEnemy2f);
	//pEnemy2f->Release();

	
	// Initialize Camera and post process
	CAMERA->InitializeCamera( GAME->GetScreenWidth(), GAME->GetScreenHeight(),
		(float)PLAYER->GetPosX(), (float)PLAYER->GetPosY() );
	POSTPROCESS->Initialize();

	if(GAME->m_uiWhichSlotAreWeLoadingDawgQuestionMark != 0)
	{
		if(GAME->m_uiWhichSlotAreWeLoadingDawgQuestionMark == 1)
		{
			GAME->LoadSlot1();
		}
		else if(GAME->m_uiWhichSlotAreWeLoadingDawgQuestionMark == 2)
		{
			GAME->LoadSlot2();
		}
		else if(GAME->m_uiWhichSlotAreWeLoadingDawgQuestionMark == 3)
		{
			GAME->LoadSlot3();
		}
	}

	//	This is the last call to the loading screen
	GAME->RenderLoadingScreen( GAME->IncrementAndReturnAmountLoaded(), 0);
	GAME->ResetAmountLoaded();

	//	I'm making this the last thing, so that the music does not start playing while in the loading screen =)
	AUDIO->MusicPlaySong(GetBGMusic(), true);
}

bool CGameplayState::Input(void)
{
	if(m_bGameOver || m_bVictory)
		return true;

	//	Pause
	if(CInputManager::GetInstance()->GetPressedPause())
	{
		GAME->SetPaused( !GAME->GetPaused() );
	}

	if((INPUT->KeyDown(DIK_LALT) || INPUT->KeyDown(DIK_RALT)) && INPUT->KeyDown(DIK_TAB))
	{
		GAME->SetPaused( true );
	}
	//TEMPORARY CODE TO SHOW SWITCHING WEAPONS AND AMULETS AND STUFF TODO
	if(CInputManager::GetInstance()->GetSwapMask())
	{
		PLAYER->CycleMask();
		/*PLAYER->m_uiCurrentMask++;
		if(PLAYER->m_uiCurrentMask == 4)
			PLAYER->m_uiCurrentMask = 0;*/
	}
	if(CInputManager::GetInstance()->GetSwapWeapon())
	{
		PLAYER->CycleWeapon();
		/*PLAYER->m_uiCurrentWeapon++;
		if(PLAYER->m_uiCurrentWeapon == 4)
			PLAYER->m_uiCurrentWeapon = 0;*/
	}
	//	TEMPORARYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY

	// Get Input from all objects
	CObjectManager::GetInstance()->InputFromObjects();
	return true;
}

void CGameplayState::Update(float fElapsedTime)
{
	if(!GAME->GetPaused())
	{
		if(m_bGameOver || m_bVictory)
			return;

		//	HEART TIMER FROM STUPID PHIL
		m_fHeartTimer += fElapsedTime;
		if(m_fHeartTimer >= 4.0f)
			m_fHeartTimer = 0.0f;

		// Update the Camera
		CCameraControl::GetInstance()->Update( fElapsedTime );

		// Update the best world engine ever created
		WORLD->UpdateWorld(fElapsedTime);
		EVENTS->ProcessEvents();
		PUZZLES->UpdatePuzzles(fElapsedTime);

		// Update the Weather
		CWeatherManager::GetInstance()->Update( fElapsedTime );

		OBJECTS->CheckCollisions();
		OBJECTS->UpdateObjects(fElapsedTime);
		// DANIEL CODE BEGIN
		PLAYER->CheckWorldCollision();
		// DANIEL CODE END

		MESSAGES->ProcessMessages();

		double nNewCameraPosX = PLAYER->GetPosX() - GAME->GetScreenWidth()/2;
		double nNewCameraPosY = PLAYER->GetPosY() - GAME->GetScreenHeight()/2;

		if(nNewCameraPosX < 0)
			nNewCameraPosX = 0;
		if(nNewCameraPosY < 0)
			nNewCameraPosY = 0;
		if(nNewCameraPosX > WORLD->GetWorldWidth() - GAME->GetScreenWidth())
			nNewCameraPosX = WORLD->GetWorldWidth() - GAME->GetScreenWidth();
		if(nNewCameraPosY > WORLD->GetWorldHeight() - GAME->GetScreenHeight())
			nNewCameraPosY = WORLD->GetWorldHeight() - GAME->GetScreenHeight();

		CCameraControl::GetInstance()->SetPositionX((float)-nNewCameraPosX);
		CCameraControl::GetInstance()->SetPositionY((float)-nNewCameraPosY);

		CCameraControl::GetInstance()->Update( fElapsedTime );

		///////////////////////////
		//ARI EXTRA CODE
		///////////////////////////
		CPostProcess::GetInstance()->Update();
		///////////////////////////
		//END ARI EXTRA CODE
		///////////////////////////
	}

}

void CGameplayState::Render(void)
{


	///////////////////////////////////////////////////////////////////////////////////
	////////////////////////// RENDER GAME OBJECTS AND WORLD //////////////////////////
	///////////////////////////////////////////////////////////////////////////////////

	
	//D3D->DeviceBegin();

//#ifdef _DEBUG
//	if(PLAYER->GetAnimationPlayer(PLAYER->GetCurrentAnimation()))
//	{
//		D3D->DrawText("Frame Info",(int)(GAME->GetScreenWidth()*0.5f),(int)(GAME->GetScreenHeight()*0.5f));
//		char buffer2[100];
//		sprintf_s(&buffer2[0],100,"Time %f, FrameNumber %f ",PLAYER->GetAnimationPlayer(PLAYER->GetCurrentAnimation())->m_fTimer,PLAYER->GetAnimationPlayer(PLAYER->GetCurrentAnimation())->m_nFrameNumber);
//		D3D->DrawText(buffer2,(int)(GAME->GetScreenWidth()*0.5f+20),(int)(GAME->GetScreenHeight()*0.5f+20),255,0,255);
//	}
//#endif
	D3D->Clear(0,0,0);
	///////////////////////////
	//ARI EXTRA CODE
	///////////////////////////
	if(!GAME->GetPaused())
	{
		D3D->DeviceBegin();
		CPostProcess::GetInstance()->BeginPostProcess();
		///////////////////////////
		//END ARI EXTRA CODE
		///////////////////////////
		
		//ARI EXTRA CODE
		CCameraControl::GetInstance()->SetSpriteProjection();
		//END ARI EXTRA CODE
		
		D3D->SpriteBegin();
		
		//ARI EXTRA CODE
		D3D->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
		D3D->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);
		D3D->GetSprite()->SetTransform( &CCameraControl::GetInstance()->GetView() );
		//END ARI EXTRA CODE

		WORLD->RenderWorldBelowObjects();
		D3D->GetSprite()->Flush();

		OBJECTS->RenderObjects();
		D3D->GetSprite()->Flush();

		WORLD->RenderWorldAboveObjects();
		D3D->GetSprite()->Flush();

		PUZZLES->RenderPuzzles();

		D3D->GetSprite()->Flush();


		D3D->SpriteEnd();
		///////////////////////////
		//ARI EXTRA CODE
		///////////////////////////
		D3D->DeviceEnd();
		CPostProcess::GetInstance()->EndPostProcess();
	
		///////////////////////////
		//END ARI EXTRA CODE
		///////////////////////////



		D3D->DeviceBegin();
		D3D->SpriteBegin();

		///////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////// RENDER HUD AND WEATHER ////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////

		D3DXMATRIX identity;
		D3DXMatrixIdentity(&identity);
		D3D->GetSprite()->SetTransform(&identity);

#ifdef _DEBUG
		if(CInputManager::GetInstance()->GetAttack())
		{
			D3D->DrawText("Button is Down",(int)(GAME->GetScreenWidth()*0.5f),(int)(GAME->GetScreenHeight()*0.5f));
			char buffer[100];
			sprintf_s(&buffer[0],100,"Value %f",CInputManager::GetInstance()->Timeheld());
			D3D->DrawText(buffer,(int)(GAME->GetScreenWidth()*0.5f+20),(int)(GAME->GetScreenHeight()*0.5f+20),255,0,255);
		}
#endif

		// Render the Weather
		CWeatherManager::GetInstance()->Render();


		// If the player is talking to an NPC, render the MessageBox but not the HUD
		if(m_bNPCTalking)
		{
			RenderMessageBox();
		}
		else
		{
			//	Render a neato HUD
			if(GAME->GetShowHUD() == true)		//	But why wouldn't you want to show it??!?
				if(GAME->GetPaused() == false)
					RenderHUD();
		}
		RenderGameOverScreens();
		D3D->SpriteEnd();
		D3D->DeviceEnd();
		D3D->Present();
	}

	if(GAME->GetPaused() == true)
	{
		D3D->Clear(160, 160, 160);
		D3D->DeviceBegin();
		D3D->SpriteBegin();

		
		GAME->GetFont()->Write("GAME IS PAUSED", 24, 2 * GAME->GetFont()->GetCharHeight(), D3DCOLOR_XRGB(255, 0, 0));
		GAME->GetFont()->Write("Press ESC again to resume", 32, 3 * GAME->GetFont()->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
		//GAME->GetFont()->Write("ESC brings up player inventory!", 32, 4 * GAME->GetFont()->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
		GAME->GetFont()->Write("PRESS DELETE FOR MAIN MENU", 32, 6 * GAME->GetFont()->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
		
		RECT w;
		w.left = 270;
		w.top = 64;
		w.right = 270+39+16;
		w.bottom = 64+128+16;

		RECT map;
		map.left = 256;
		map.right = 512;
		map.top = 256;
		map.bottom = 512;
		//draw map w/e
		TEX_MNG->Draw(m_imgHUD, 800-256-32, 600-256-32, 1.0f, 1.0f, &map, 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 255));

		for(unsigned int i=0; i<4; ++i)
		{

		RECT e;
		e.left = 0;
		e.top = 0 + (i*128);
		e.right = 39;
		e.bottom = 128 + (i*128);

		TEX_MNG->Draw(m_imgHUD, 80+((39+16+8)*i), 240, 1.0f, 1.0f, &w);
		if(i == 0)
		{
		if( TestBit( PLAYER->m_byteWeapons, 0 ) )
			TEX_MNG->Draw(m_imgHUD, 80+8+((39+16+8)*0), 240+8, 1.0f, 1.0f, &e);
		}
		TEX_MNG->Draw(m_imgHUD, 80+((39+16+8)*i), 240, 1.0f, 1.0f, &w);
		if(i == 1)
		{
		if( TestBit( PLAYER->m_byteWeapons, 1 ) )
			TEX_MNG->Draw(m_imgHUD, 80+8+((39+16+8)*1), 240+8, 1.0f, 1.0f, &e);
		}
		TEX_MNG->Draw(m_imgHUD, 80+((39+16+8)*i), 240, 1.0f, 1.0f, &w);
		if(i == 2)
		{
		if( TestBit( PLAYER->m_byteWeapons, 2 ) )
			TEX_MNG->Draw(m_imgHUD, 80+8+((39+16+8)*2), 240+8, 1.0f, 1.0f, &e);
		}
		TEX_MNG->Draw(m_imgHUD, 80+((39+16+8)*i), 240, 1.0f, 1.0f, &w);
		if(i == 3)
		{
		if( TestBit( PLAYER->m_byteWeapons, 3 ) )
			TEX_MNG->Draw(m_imgHUD, 80+8+((39+16+8)*3), 240+8, 1.0f, 1.0f, &e);
		}

		RECT f;
		f.left = 39;
		f.top = 0 + (i*128);
		f.right = 39+39;
		f.bottom = 128 + (i*128);

		TEX_MNG->Draw(m_imgHUD, 80, 240+128+16+8, 1.0f, 1.0f, &w);
		if(i == 0)
		{
		if( TestBit( PLAYER->m_byteMasks, 0) )
			TEX_MNG->Draw(m_imgHUD, 80+((39+16+8)*0), 240+128+16+8, 1.0f, 1.0f, &f);
		}
		TEX_MNG->Draw(m_imgHUD, 80+((39+16+8)*1), 240+128+16+8, 1.0f, 1.0f, &w);
		if(i == 1)
		{
		if( TestBit( PLAYER->m_byteMasks, 1) )
			TEX_MNG->Draw(m_imgHUD, 80+((39+16+8)*1), 240+128+16+8, 1.0f, 1.0f, &f);
		}
		TEX_MNG->Draw(m_imgHUD, 80+((39+16+8)*2), 240+128+16+8, 1.0f, 1.0f, &w);
		if(i == 2)
		{
		if( TestBit( PLAYER->m_byteMasks, 2) )
			TEX_MNG->Draw(m_imgHUD, 80+((39+16+8)*2), 240+128+16+8, 1.0f, 1.0f, &f);
		}
		TEX_MNG->Draw(m_imgHUD, 80+((39+16+8)*3), 240+128+16+8, 1.0f, 1.0f, &w);
		if(i == 3)
		{
		if( TestBit( PLAYER->m_byteMasks, 3) )
			TEX_MNG->Draw(m_imgHUD, 80+((39+16+8)*3), 240+128+16+8, 1.0f, 1.0f, &f);
		}
		}
		D3D->SpriteEnd();
		D3D->DeviceEnd();
		D3D->Present();
	}


#if 0
#ifdef _DEBUG
	char buffer[100];
	sprintf_s(&buffer[0], 100, "Player PosX:%f, PosY:%f" , PLAYER->GetPosX(), PLAYER->GetPosY());
	D3D->DrawTextA(&buffer[0], 120, 550, 255, 0, 0);

	
	sprintf_s(buffer, 100, "FPS: %i", GAME->GetTimer().m_nFPS);
	D3D->DrawTextA(&buffer[0], 0, 0, 255, 0, 0);

	const char* szRegion = PLAYER->GetRegion();
	if(szRegion)
	{
		strcpy_s(buffer, 100, szRegion);
		D3D->DrawTextA(&buffer[0], 120, 570, 255, 0, 0);
	}
#endif
#endif

}

void CGameplayState::RenderGameOverScreens(void)
{
	if(m_bGameOver)
	{
		static int fadein = 0;
		
		if(fadein < 255)
			TEX_MNG->Draw(m_nGameOverID, 0, 0, 1.0f, 1.0f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(fadein,255,255,255));
		else
			TEX_MNG->Draw(m_nGameOverID, 0, 0, 1.0f, 1.0f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255,255,255,255));

		fadein++;

		if(fadein > 500)
		{
			fadein = 0;
			m_bGameOver = false;
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
		}
	}
	else if(m_bVictory)
	{
		static int fadein = 0;
		if(fadein < 255)
			TEX_MNG->Draw(m_nVictoryID, 0, 0, 1.0f, 1.0f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(fadein,255,255,255));
		else
			TEX_MNG->Draw(m_nVictoryID, 0, 0, 1.0f, 1.0f, nullptr, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255,255,255,255));

		fadein++;

		if(fadein > 500)
		{
			fadein = 0;
			m_bVictory = false;

			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
		}
	}

}

void CGameplayState::RenderMessageBox(void)
{
	// Safe checks
	if(m_pFont && m_imgMessageBox != -1 && m_szCurrentMessage != "")
	{
		// int nDrawLocationX = GAME->GetMapLocation() ? 5 : 105;
		// int nDrawLocationY = 468;
		RECT sourceRect;

		// Draw the box that displays the NPC's speech
		sourceRect.left = 0;
		sourceRect.top = 0;
		sourceRect.right = 720;
		sourceRect.bottom = 232;
		TEX_MNG->Draw(m_imgMessageBox, 50 - 10, 387 - 10, 1.0f, 1.0f, &sourceRect);

		// Draw the box that displays the NPC's name
		sourceRect.left = 0;
		sourceRect.top = 230;
		sourceRect.right = 248;
		sourceRect.bottom = sourceRect.top + 68;
		TEX_MNG->Draw(m_imgMessageBox, 280 - 4, 320 - 4, 1.0f, 1.0f, &sourceRect);

		// Flush it so that the box is already rendered on screen
		D3D->GetSprite()->Flush();

		// Write the text using the bitmap font

		// For the name to be centered...
		// Each character in the bitmap font has a size of 16 or less,
		// since there are usually a couple characters like "i", that are
		// smaller, I'm just using 14 as an average size
		int nNameWidth = 14 * m_szCharName.length();

		// Write name and text using the bitmap font
		m_pFont->Write(m_szCharName.c_str(), 400 - (nNameWidth / 2), 334, D3DCOLOR_XRGB(255, 255, 255)); 
		m_pFont->Write(m_szCurrentMessage.c_str(), 100, 413, D3DCOLOR_XRGB(255, 255, 255), 0.8f);

		// If there's a current option...
		if(m_szCurrentOption != "")
		{
			// Draw the box that displays the selected option
			sourceRect.left = 0;
			sourceRect.top = 300;
			sourceRect.right = sourceRect.left + 660;
			sourceRect.bottom = sourceRect.top + 72;
			TEX_MNG->Draw(m_imgMessageBox, 80 - 10, 144 - 4, 1.0f, 1.0f, &sourceRect);

			int nOptionWidth = 14 * m_szCurrentOption.length();
			// Write the selected option
			m_pFont->Write(m_szCurrentOption.c_str(), 400 - (nOptionWidth / 2), 160, D3DCOLOR_XRGB(255, 255, 128), 0.9f);

			if(true /*Should be "if there are other options"*/)
			{
				static int nArrowIndex = 0;

				// Draw the arrows
				sourceRect.left = 0 + (nArrowIndex/10) * 60;
				sourceRect.top = 410;
				sourceRect.right = sourceRect.left + 60;
				sourceRect.bottom = sourceRect.top + 44;
				TEX_MNG->Draw(m_imgMessageBox, 31 - 2, 157 - 2, 1.0f, 1.0f, &sourceRect);
				sourceRect.top = 460;
				sourceRect.bottom = sourceRect.top + 44;
				TEX_MNG->Draw(m_imgMessageBox, 720 - 2, 157 - 2, 1.0f, 1.0f, &sourceRect);

				nArrowIndex += 5;

				if(nArrowIndex >= 80)
					nArrowIndex = 0;
			}
		}
	}
}

string CGameplayState::BreakDownStrings(string szString, int nMin, int nMax)
{
	string szReturnableString;
	int horIndex = 0;
	for(unsigned int i=0; i < szString.size(); ++i, ++horIndex)
	{
		if(horIndex >= nMin &&
			(szString[i] == ' ' || szString[i] == '\t' || szString[i] == '	' || szString[i] == '-'))
		{
			szReturnableString += '\n';
			horIndex = 0;
		}
		else
		{
			szReturnableString += szString[i];
			if(horIndex >= nMax && i < szString.size() - 1)
			{
				if(szString[i+1] != ' ' && szString[i+1] != '\t' && szString[i+1] != '	' && szString[i+1] && '-')
				{
					szReturnableString += '-';
					szReturnableString += '\n';
					horIndex = 0;
				}
			}
		}
			
	}

	return szReturnableString;
}

void CGameplayState::Exit(void)
{
	AUDIO->MusicStopSong(GetBGMusic());

	EVENTS->ClearEvents();
	MESSAGES->ClearMessages();

	POSTPROCESS->ShutDown();
	WEATHER->ShutDown();
	OBJECTS->RemoveAllObjects();
	OBJECTS->DeleteInstance();

	TEX_MNG->UnloadTexture(m_imgMessageBox);
	TEX_MNG->UnloadTexture(m_imgHUD);
	TEX_MNG->UnloadTexture(m_nGameOverID);
	TEX_MNG->UnloadTexture(m_nVictoryID);
	
	AUDIO->MusicUnloadSong(GetBGMusic());

	EVENTS->UnregisterEveryone(this);
	EVENTS->ShutdownEventSystem();
	
	PUZZLES->ShutdownPuzzleManager();
	WORLD->ShutdownWorldEngine();
	WORLD->DeleteInstance();
	MESSAGES->ShutdownMessageSystem();

	CPlayer::GetInstance()->Reset();
}

CGameplayState* CGameplayState::GetInstance(void)
{
	static CGameplayState pInstance;
	return &pInstance;
}

void CGameplayState::HandleEvent(CEvent* pEvent)
{
	if(pEvent->GetEventID() == "destroy")
	{
		CMap::TileInfo* eventInfo = (CMap::TileInfo*)pEvent->GetParam();

		eventInfo->Tile->SetPosX(-1);
		eventInfo->Tile->SetPosY(-1);
		eventInfo->Tile->SetInfo(0);
		eventInfo->Tile->SetEventID(0);

		eventInfo->Map->TurnOffCollisionOnTile(eventInfo->sMapPosX, eventInfo->sMapPosY);

	}
	if(pEvent->GetEventID() == "get.flower")
	{
		PLAYER->AcquireFlower();

		CMap::TileInfo* eventInfo = (CMap::TileInfo*)pEvent->GetParam();

		eventInfo->Tile->SetPosX(-1);
		eventInfo->Tile->SetPosY(-1);
		eventInfo->Tile->SetInfo(0);
		eventInfo->Tile->SetEventID(0);

		eventInfo->Map->TurnOffCollisionOnTile(eventInfo->sMapPosX, eventInfo->sMapPosY);
	}
	if(pEvent->GetEventID() == "get.hammer")
	{
		PLAYER->AcquireWeapon(CPlayer::WEAPON_HAMMER);
		PLAYER->CycleWeapon();

		CMap::TileInfo* eventInfo = (CMap::TileInfo*)pEvent->GetParam();

		eventInfo->Tile->SetPosX(-1);
		eventInfo->Tile->SetPosY(-1);
		eventInfo->Tile->SetInfo(0);
		eventInfo->Tile->SetEventID(0);
	}
	if(pEvent->GetEventID() == "Teleport.Dungeon")
	{
		PLAYER->SetPosX(1504);
		PLAYER->SetPosY(2720);
	}
	if(pEvent->GetEventID() == "Teleport.Volcano")
	{
		PLAYER->SetPosX(4704);
		PLAYER->SetPosY(1696);
	}
	if(pEvent->GetEventID() == "Teleport.Lake")
	{
		PLAYER->SetPosX(4000);
		PLAYER->SetPosY(4736);
	}
	if(pEvent->GetEventID() == "game.over")
		m_bGameOver = true;
	if(pEvent->GetEventID() == "victory")
		m_bVictory = true;

}

void CGameplayState::MessageProc(CBaseMessage* pMsg)
{
	switch(pMsg->GetMsgID())
	{
	case MSG_DESTROY_OBJECT:
		{
			CDestroyObjectMessage* pDEM = (CDestroyObjectMessage*)pMsg;
			OBJECTS->RemoveObject(pDEM->GetObject());
			break;
		}
	case MSG_CREATE_NPC:
		{
			CCreateNPCMessage* pMsgNPC = (CCreateNPCMessage*)pMsg;

			CNPC* pNPC;
			if(pMsgNPC->GetName() == "Grimir")
			{
				pNPC = new CGrimirNPC(pMsgNPC->GetName().c_str(), false, 150, -1, pMsgNPC->GetPosX(),
					pMsgNPC->GetPosY(), 20, -1, 50, 50, true, 100, 0);
			}
			else
			{
				pNPC = new CNPC(pMsgNPC->GetName().c_str(), false, 150, -1, pMsgNPC->GetPosX(),
					pMsgNPC->GetPosY(), 20, -1, 50, 50, true, 100, 0);
			}

			string szDialogFile = "resource/NPC Dialogue/";
			szDialogFile += pMsgNPC->GetName();
			szDialogFile += ".xml";
			string szAnmFile = "resource/Animations/";
			szAnmFile += pMsgNPC->GetName();
			szAnmFile += ".xml";

			pNPC->LoadAnimations(szAnmFile.c_str());
			pNPC->LoadText(szDialogFile.c_str());
			pNPC->ChangeAIState(CRandomAIState::GetInstance());

			OBJECTS->AddObject(pNPC);
			pNPC->Release();

			break;
		}
	case MSG_CREATE_ENEMY:
		{
			CCreateEnemyMessage* pMsgEnemy = (CCreateEnemyMessage*)pMsg;

			int nRandom = rand() % 3;
			double dPosX = RandomFloat((float)pMsgEnemy->GetPosX() - 32, (float)pMsgEnemy->GetPosX() + 32);
			double dPosY = RandomFloat((float)pMsgEnemy->GetPosY() - 32, (float)pMsgEnemy->GetPosY() + 32);

			IBaseAIState* pAIState = nullptr;
			unsigned int uiSpeed = 0;
			unsigned int uiWidth = 0;
			unsigned int uiHeight = 0;
			unsigned int uiMaxHealth = 0;
			unsigned int uiAttackDamage = 0;


			if(pMsgEnemy->GetRegion() == "Forest")
			{
				switch(nRandom)
				{
				case 0:
					pAIState = CSmallSpiderAIState::GetInstance();
					uiSpeed = 40;
					uiWidth = 50;
					uiHeight = 50;
					uiMaxHealth = 75;
					uiAttackDamage = 1;
					break;
				case 1:
					pAIState = CRatAIState::GetInstance();
					uiSpeed = 40;
					uiWidth = 50;
					uiHeight = 50;
					uiMaxHealth = 75;
					uiAttackDamage = 1;
					break;
				case 2:
					pAIState = CFlowerAIState::GetInstance();
					uiSpeed = 40;
					uiWidth = 50;
					uiHeight = 50;
					uiMaxHealth = 75;
					uiAttackDamage = 1;
					break;
				}
			}
			else if(pMsgEnemy->GetRegion() == "Snow")
			{
				switch(nRandom)
				{
				case 0:
					pAIState = CSnowGolemAIState::GetInstance();
					uiSpeed = 40;
					uiWidth = 50;
					uiHeight = 50;
					uiMaxHealth = 75;
					uiAttackDamage = 1;
					break;
				default:
					pAIState = CSlimeAIState::GetInstance();
					uiSpeed = 40;
					uiWidth = 50;
					uiHeight = 50;
					uiMaxHealth = 75;
					uiAttackDamage = 1;
					break;
				}
			}
			else if(pMsgEnemy->GetRegion() == "Desert")
			{
				switch(nRandom)
				{
				case 0:
					pAIState = CGolemAIState::GetInstance();
					uiSpeed = 40;
					uiWidth = 50;
					uiHeight = 50;
					uiMaxHealth = 75;
					uiAttackDamage = 1;
					break;
				case 1:
					pAIState = CSpiderAIState::GetInstance();
					uiSpeed = 40;
					uiWidth = 50;
					uiHeight = 50;
					uiMaxHealth = 75;
					uiAttackDamage = 1;
					break;					
				case 2:
					pAIState = CLarvaAIState::GetInstance();
					uiSpeed = 40;
					uiWidth = 50;
					uiHeight = 50;
					uiMaxHealth = 75;
					uiAttackDamage = 1;
					break;
				}
			}
			else // if Volcano
			{
				switch(nRandom)
				{
				case 0:
					pAIState = CLavaGolemAIState::GetInstance();
					uiSpeed = 40;
					uiWidth = 50;
					uiHeight = 50;
					uiMaxHealth = 75;
					uiAttackDamage = 1;
					break;
				default:
					pAIState = CLilBastardAIState::GetInstance();
					uiSpeed = 40;
					uiWidth = 50;
					uiHeight = 50;
					uiMaxHealth = 75;
					uiAttackDamage = 1;
					break;
				}
			}

			if(pAIState)
			{
				CEnemy* pEnemy = new CEnemy(dPosX, dPosY, uiSpeed, -1, uiWidth, uiHeight, true, uiMaxHealth, uiAttackDamage);
				pEnemy->ChangeAIState(pAIState);
				OBJECTS->AddObject(pEnemy);
				pEnemy->Release();
			}

			break;
		}
	case MSG_CREATE_CHEST:
		{
			CCreateChestMessage* pMsgChest = (CCreateChestMessage*)pMsg;

			CItemChest* pChest = new CItemChest(pMsgChest->GetType(), pMsgChest->GetPosX(), pMsgChest->GetPosY());
			OBJECTS->AddObject(pChest);
			pChest->Release();
			break;
		}
	}
}


void CGameplayState::RenderHUD()
{
	RECT r1;

	r1.left = 39;
	r1.top = 0 + (PLAYER->m_uiCurrentMask-1)*128;
	r1.right = 39+39;
	r1.bottom = 128 + (PLAYER->m_uiCurrentMask-1)*128;

	//	Draw the amulet!
	TEX_MNG->Draw(m_imgHUD, 0, 0, 1.0f, 1.0f, &r1);

	r1.left = 0;
	r1.top = 0 + PLAYER->m_uiCurrentWeapon*128;
	r1.right = 39;
	r1.bottom = 128 + PLAYER->m_uiCurrentWeapon*128;;

	//	Draw the weapon!
	TEX_MNG->Draw(m_imgHUD, 800-39, 0, 1.0f, 1.0f, &r1);

	//	Draw some life hearts
	unsigned int tempMaxH = PLAYER->GetMaxHealth();
	unsigned int tempCurH = PLAYER->GetCurHealth();

	r1.left = 78;
	r1.top = 0;
	r1.right = 78+32;
	r1.bottom = 32;

	for(unsigned int i = 0; i < 10; ++i)
	{
		if(i < tempCurH)
		{
			//	Define a solid heart
			if(m_fHeartTimer < 3.68f)
			{
				r1.top = 0;
				r1.bottom = 32;
			}
			else if(m_fHeartTimer < 3.76f)
			{
				r1.top = 32;
				r1.bottom = 64;
			}
			else if(m_fHeartTimer < 3.84f)
			{
				r1.top = 64;
				r1.bottom = 96;
			}
			else if(m_fHeartTimer < 3.92f)
			{
				r1.top = 96;
				r1.bottom = 128;
			}
			else
			{
				r1.top = 128;
				r1.bottom = 160;
			}
		}
		else if(i >= tempMaxH)
		{
			//	Define an invisible heart
			r1.top = 64+128;
			r1.bottom = 96+128;
		}
		else
		{
			//	Define a broken heart
			r1.top = 32+128;
			r1.bottom = 64+128;
		}
		TEX_MNG->Draw(m_imgHUD, 39+(i*32), 4, 1.0f, 1.0f, &r1);
	}

	//	Draw the weapon XP bar background
	r1.left = 110;
	r1.top = 32;
	r1.right = 110+320;
	r1.bottom = 64;

	TEX_MNG->Draw(m_imgHUD, 800-39-320, 4, 1.0f, 1.0f, &r1);

	//	Value for the actual current XP

	//float tempXP = CInputManager::GetInstance()->Timeheld();
	float tempXP = CPlayer::GetInstance()->m_fPhilChargeIdkman;
	if(tempXP > 1.0f)
		tempXP = 1.0f;

	//	Draw the weapon XP bar foreground
	r1.left = (long)(110 + (320 * (1.0f - tempXP)));
	r1.top = 0;
	r1.bottom = 32;

	TEX_MNG->Draw(m_imgHUD, (int)(800-39-(320*tempXP)), 4, 1.0f, 1.0f, &r1);

	//	Define the potion spot
	r1.left = 206;
	r1.top = 64;
	r1.right = 206+64;
	r1.bottom = 64+64;

	//	Draw the potion spot
	TEX_MNG->Draw(m_imgHUD, 800-400-32, 4, 1.0f, 1.0f, &r1);

	r1.left = 78;
	r1.top = 224;
	r1.right = 78+32;
	r1.bottom = 224+32;

	if(PLAYER->GetNumPotions() > 0)
	{
		TEX_MNG->Draw(m_imgHUD, 800-400-16, 4+16, 1.0f, 1.0f, &r1);
	}

	//	Define the minimap frame
	r1.left = 110;
	r1.top = 64;
	r1.right = 110+96;
	r1.bottom = 64+96;

	//	Draw the minimap frame
	if( CPlayer::GetInstance()->m_fOuchTimer == 0.0f )
	{
		if(GAME->GetMapLocation() == 0)
		{
			TEX_MNG->Draw(m_imgHUD, 4, 600-96-4, 1.0f, 1.0f, &r1);
		}
		else
		{
			TEX_MNG->Draw(m_imgHUD, 800-96-4, 600-96-4, 1.0f, 1.0f, &r1);
		}
	}
}


// Set message box parameters
void CGameplayState::SetMessageBox(bool bNPCTalking, string szCharName,
	string szCurrentMessage, string szCurrentOption)
{
	m_bNPCTalking = bNPCTalking;
	m_szCharName = szCharName;
	m_szCurrentMessage = szCurrentMessage;
	m_szCurrentOption = szCurrentOption;
}