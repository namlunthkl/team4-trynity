////////////////////////////////////////////////////////////////////////
//    File Name				:	"CGameplayState.cpp"
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09/12 - 1:00 AM
//    Purpose				:	Contains the GameplayState
////////////////////////////////////////////////////////////////////////

// Precompiled header
#include "StdAfx.h"
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
#include "../Game Objects/CObjectManager.h"
#include "../Game Objects/CNPC.h"
#include "../Puzzles/CPuzzleManager.h"
#include "../Game Objects/CChest.h"
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
	WORLD->InitWorldEngine();
	PUZZLES->InitPuzzleManager();

	// Reset variables
	m_fHeartTimer = 0.0f;
	m_bGameOver = false;
	m_bVictory = false;
	
	// Register for events
	EVENTS->RegisterForEvent("SpawnMessageBox", this);
	EVENTS->RegisterForEvent("Teleport.Cave", this);
	EVENTS->RegisterForEvent("Teleport.Map", this);
	EVENTS->RegisterForEvent("destroy", this);
	EVENTS->RegisterForEvent("game.over", this);
	EVENTS->RegisterForEvent("victory", this);

	// CWeatherManager::GetInstance()->GetWeather()->Init();

	//	Load all assets
	//		Textures
	m_imgMessageBox = TEX_MNG->LoadTexture("resource/MessageBox.png");
	m_imgHUD = TEX_MNG->LoadTexture("resource/HUD_Graphic.png", D3DCOLOR_XRGB(255, 0, 255));
	m_nGameOverID = TEX_MNG->LoadTexture("resource/GameOver.png");
	m_nVictoryID = TEX_MNG->LoadTexture("resource/Victory.png");
	//		Sounds
	SetBGMusic(AUDIO->MusicLoadSong("resource/KSC_Beginning.xwm"));

	// Initialize Player
	PLAYER->SetPosX(600);
	PLAYER->SetPosY(200);
	PLAYER->SetSpeed(100);
	PLAYER->SetWidth(30);
	PLAYER->SetHeight(30);
	PLAYER->SetAttackDamage(20);
	PLAYER->SetDebugMode(false);
	OBJECTS->AddObject(PLAYER);

	// Initialize Enemies
	CEnemy* pEnemy = new CEnemy(700, 600, 40,  -1, 50, 50, true, 100, 1);
	pEnemy->LoadAnimations("resource/Enemy Animation.xml");
	pEnemy->ChangeAIState(CJumperAIState::GetInstance());
	pEnemy->SetDebugMode(true);
	OBJECTS->AddObject(pEnemy);
	pEnemy->Release();

	// Initialize NPCs
	CNPC* pNPC;
	pNPC = new CNPC("Person 2", false, 150, -1, 290, 1000, 20, -1, 50, 50, true, 100, 0);
	pNPC->LoadAnimations("resource/npc walk3.xml");
	pNPC->LoadText("resource/NPC Dialogue/Example.xml");
	OBJECTS->AddObject(pNPC);
	pNPC->Release();

	// Initialize chests
	CChest* pChest;
	pChest = new CChest("PotionChest", false, 150, -1, 600, 250, 20, -1, 32,32, true, 100, 0);
	pChest->LoadAnimations("resource/chest.xml");
	OBJECTS->AddObject(pChest);
	pChest->Release();

	// Initialize Camera and post process
	CAMERA->InitializeCamera( GAME->GetScreenWidth(), GAME->GetScreenHeight(),
		(float)PLAYER->GetPosX(), (float)PLAYER->GetPosY() );
	POSTPROCESS->Initialize();

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

	///////////////////////////
	//ARI EXTRA CODE
	///////////////////////////
	CPostProcess::GetInstance()->Input();
	///////////////////////////
	//END ARI EXTRA CODE
	///////////////////////////

#if 1
	if(INPUT->KeyPressed(DIK_V))
	{
		EVENTS->SendEvent("victory");
	}
	else if(INPUT->KeyPressed(DIK_B))
	{
		EVENTS->SendEvent("game.over");
	}
#endif // Victory/Lose keys



	//TEMPORARY CODE TO SHOW SWITCHING WEAPONS AND AMULETS AND STUFF TODO
	if(INPUT->KeyPressed(DIK_Q))
	{
		PLAYER->CycleMask();
		/*PLAYER->m_uiCurrentMask++;
		if(PLAYER->m_uiCurrentMask == 4)
			PLAYER->m_uiCurrentMask = 0;*/
	}
	if(INPUT->KeyPressed(DIK_E))
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

	//m_Rain.Update(fElapsedTime);
	CWeatherManager::GetInstance()->Update( fElapsedTime );

	// DANIEL CODE BEGIN
	PLAYER->CheckWorldCollision();
	// DANIEL CODE END

	MESSAGES->ProcessMessages();
	OBJECTS->UpdateObjects(fElapsedTime);
	OBJECTS->CheckCollisions();

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

void CGameplayState::Render(void)
{

	///////////////////////////
	//ARI EXTRA CODE
	///////////////////////////
	CPostProcess::GetInstance()->BeginPostProcess();
	///////////////////////////
	//END ARI EXTRA CODE
	///////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	////////////////////////// RENDER GAME OBJECTS AND WORLD //////////////////////////
	///////////////////////////////////////////////////////////////////////////////////

	D3D->Clear(50,50,50);
	D3D->DeviceBegin();
	
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

	///////////////////////////
	//ARI EXTRA CODE
	///////////////////////////
	CPostProcess::GetInstance()->EndPostProcess();
	///////////////////////////
	//END ARI EXTRA CODE
	///////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////// RENDER HUD AND WEATHER ////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////

	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);
	D3D->GetSprite()->SetTransform(&identity);

	if(CInputManager::GetInstance()->GetAttack())
	{
		D3D->DrawText("Button is Down",(int)(GAME->GetScreenWidth()*0.5f),(int)(GAME->GetScreenHeight()*0.5f));
		char buffer[100];
		sprintf_s(&buffer[0],100,"Value %f",CInputManager::GetInstance()->Timeheld());
		D3D->DrawText(buffer,(int)(GAME->GetScreenWidth()*0.5f+20),(int)(GAME->GetScreenHeight()*0.5f+20));
	}

	//m_Rain.Render();
	CWeatherManager::GetInstance()->Render();

	//	Render a neato HUD
	if(GAME->GetShowHUD() == true)		//	But why wouldn't you want to show it??!?
		RenderHUD();

	// Render the message box
	RenderMessageBox();

	if(GAME->GetPaused() == true)
	{
		GAME->GetFont()->Write("GAME IS PAUSED", 24, 2 * GAME->GetFont()->GetCharHeight(), D3DCOLOR_XRGB(255, 0, 0));
		GAME->GetFont()->Write("Press ESC again to resume", 32, 3 * GAME->GetFont()->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
		GAME->GetFont()->Write("ESC brings up player inventory!", 32, 4 * GAME->GetFont()->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
		GAME->GetFont()->Write("PRESS DELETE FOR MAIN MENU", 32, 6 * GAME->GetFont()->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	}

	D3D->GetSprite()->Flush();

	RenderGameOverScreens();

	char buffer[100];
	sprintf_s(&buffer[0], 100, "Player PosX:%f, PosY:%f" , PLAYER->GetPosX(), PLAYER->GetPosY());
	D3D->DrawTextA(&buffer[0], 120, 550, 255, 0, 0);

	D3D->SpriteEnd();
	D3D->DeviceEnd();
	D3D->Present();
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
	if(m_bNPCTalking && m_pFont && m_imgMessageBox != -1 && m_szCurrentMessage != "")
	{
		int nDrawLocationX = GAME->GetMapLocation() ? 5 : 105;
		int nDrawLocationY = 468;

		// Draw the box
		if(m_imgMessageBox != -1)
			TEX_MNG->Draw(m_imgMessageBox, nDrawLocationX, nDrawLocationY);

		// Flush it so that the box is already rendered on screen
		D3D->GetSprite()->Flush();

		// Write the text using the bitmap font
		m_pFont->Write(m_szCharName.c_str(), nDrawLocationX + 30, nDrawLocationY + 15, D3DCOLOR_XRGB(255, 255, 255)); 
		m_pFont->Write(m_szCurrentMessage.c_str(), nDrawLocationX + 8, nDrawLocationY + 51, D3DCOLOR_XRGB(255, 255, 255));

		// If there's a current option
		if(m_szCurrentOption != "")
			m_pFont->Write(m_szCurrentOption.c_str(), nDrawLocationX + 8, nDrawLocationY + 88, D3DCOLOR_XRGB(255, 0, 0));
	}
}

void CGameplayState::Exit(void)
{
	AUDIO->MusicStopSong(GetBGMusic());

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
}

CGameplayState* CGameplayState::GetInstance(void)
{
	static CGameplayState pInstance;
	return &pInstance;
}

void CGameplayState::HandleEvent(CEvent* pEvent)
{
	if(pEvent->GetEventID() == "SpawnMessageBox")
	{
		MessageBox(GAME->GetWindowHandle(),"I Punched You","Program Name: PUNCH!",MB_OK);
	}
	if(pEvent->GetEventID() == "Teleport.Cave")
	{
		PLAYER->SetPosX(300);
		PLAYER->SetPosY(1830);
	}
	if(pEvent->GetEventID() == "Teleport.Map")
	{
		PLAYER->SetPosX(1715);
		PLAYER->SetPosY(340);
	}
	if(pEvent->GetEventID() == "destroy")
	{
		CMap::TileInfo* eventInfo = (CMap::TileInfo*)pEvent->GetParam();

		eventInfo->Tile->SetPosX(-1);
		eventInfo->Tile->SetPosY(-1);
		eventInfo->Tile->SetInfo(0);
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

	float tempXP = CInputManager::GetInstance()->Timeheld();
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
	if(GAME->GetMapLocation() == 0)
	{
		TEX_MNG->Draw(m_imgHUD, 4, 600-96-4, 1.0f, 1.0f, &r1);
	}
	else
	{
		TEX_MNG->Draw(m_imgHUD, 800-96-4, 600-96-4, 1.0f, 1.0f, &r1);
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