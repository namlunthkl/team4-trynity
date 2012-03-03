////////////////////////////////////////////////////////////////////////
//    File Name				:	"CGameplayState.cpp"
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09/12 - 1:00 AM
//    Purpose				:	Contains the GameplayState
////////////////////////////////////////////////////////////////////////

// Precompiled header
#include "StdAfx.h"
#include "..\StdAfx.h"

// Header file for this state
#include "CGameplayState.h"

// Includes
#include "../Input Manager/CInputManager.h"
#include "../Camera/CCameraControl.h"
#include "../Game Objects/CPlayer.h"
#include "../AI_States/CRandomAIState.h"
#include "../Game Objects/CObjectManager.h"
#include "../Game Objects/CNPC.h"

// SINGLETON Weather Engine
#include "../Weather System/WeatherManager.h"

// Singleton Macros
#define EVENTS CEventSystem::GetInstance()
#define MESSAGES CMessageSystem::GetInstance()
#define PLAYER CPlayer::GetInstance()
#define OBJECTS CObjectManager::GetInstance()
#define CAMERA CCameraControl::GetInstance()

// Constructor
CGameplayState::CGameplayState(void)
{
}

// Initialize everything
void CGameplayState::Enter(void)
{
	// Initialize stuff
	WORLD->InitWorldEngine();

	// Register for the event
	EVENTS->RegisterForEvent("SpawnMessageBox", this);
	EVENTS->RegisterForEvent("LightTorch", this);

	// Initialize our particle weapon
	PW.Load("resource/data/FireFlicker.xml");

	//m_Rain.Load("resource/data/test.xml");
	//m_Rain.Fire();
	//CWeatherManager::GetInstance()->GetWeather()->Init();

	MESSAGES->InitMessageSystem(MessageProc);

	// Add enemies to the level
	/*for(int i=0; i < 3; ++i)
	{
	for(int j = 0; j < 3; ++j)
	{
	CEnemy* pEnemy = new CEnemy(100 * i, 100 * j, 50, -1, 0, 0, true, 100, 1);
	pEnemy->ChangeAIState(CRandomAIState::GetInstance());
	pEnemy->SetDebugMode(false);
	pEnemy->LoadAnimations("resource/npc walk.xml");
	OBJECTS->AddObject(pEnemy);
	pEnemy->Release();
	}
	}*/

	CBitmapFont* pFont = new CBitmapFont();

	CNPC* pNPC[1];

	pNPC[0] = new CNPC(false, 150, -1, pFont, 400, 200, 20, -1, 0, 0, true, 100, 0);

	for(int i=0; i < 1; ++i)
	{
		pNPC[i]->LoadAnimations("resource/npc walk3.xml");
		pNPC[i]->ChangeAIState(CRandomAIState::GetInstance());
		pNPC[i]->SetDebugMode(false);
		OBJECTS->AddObject(pNPC[i]);
		pNPC[i]->Release();
	}

	pNPC[0]->LoadText("resource/NPC Dialogue/Example.xml");


	PLAYER->SetPosX(600);
	PLAYER->SetPosY(200);
	PLAYER->SetSpeed(100);
	//PLAYER->SetDebugMode(true);
	OBJECTS->AddObject(PLAYER);


	//	TODO  Temporary, just to demonstrate that the options work
	m_imgHUD = TEX_MNG->LoadTexture("resource/HUD_Graphic.bmp", D3DCOLOR_XRGB(255, 0, 255));
	AUDIO->MusicPlaySong( AUDIO->MusicLoadSong("resource/KSC_Beginning.xwm"),true );

	///////////////////////////
	//ARI EXTRA CODE
	///////////////////////////
	CCameraControl::GetInstance()->InitializeCamera( GAME->GetScreenWidth(), GAME->GetScreenHeight(), PLAYER->GetPosX(), PLAYER->GetPosY() );
	///////////////////////////
	//END ARI EXTRA CODE
	///////////////////////////

}

bool CGameplayState::Input(void)
{
	//	Pause
	if(CInputManager::GetInstance()->GetPressedPause())
	{
		GAME->SetPaused( !GAME->GetPaused() );
	}

	// Get Input from all objects
	CObjectManager::GetInstance()->InputFromObjects();

	if( INPUT->KeyPressed( DIK_0 ) )
	{
		CWeatherManager::GetInstance()->LoadWeather( 0 );
		CWeatherManager::GetInstance()->SetIsOn( false );
	}
	if( INPUT->KeyPressed( DIK_1 ) )
	{
		CWeatherManager::GetInstance()->LoadWeather( 1 );
		CWeatherManager::GetInstance()->SetIsOn( true );
	}
	if( INPUT->KeyPressed( DIK_2 ) )
	{
		CWeatherManager::GetInstance()->LoadWeather( 2 );
		CWeatherManager::GetInstance()->SetIsOn( true );
	}
	if( INPUT->KeyPressed( DIK_3 ) )
	{
		CWeatherManager::GetInstance()->LoadWeather( 3 );
		CWeatherManager::GetInstance()->SetIsOn( true );
	}
	if( INPUT->KeyPressed( DIK_4 ) )
	{
		CWeatherManager::GetInstance()->LoadWeather( 4 );
		CWeatherManager::GetInstance()->SetIsOn( true );
	}
	if( INPUT->KeyPressed( DIK_5 ) )
	{
		CWeatherManager::GetInstance()->LoadWeather( 5 );
		CWeatherManager::GetInstance()->SetIsOn( true );
	}

	return true;
}

void CGameplayState::Update(float fElapsedTime)
{
	// Update the Camera
	CCameraControl::GetInstance()->Update( fElapsedTime );

	// Update the best world engine ever created
	WORLD->UpdateWorld(fElapsedTime);
	EVENTS->ProcessEvents();

	//m_Rain.Update(fElapsedTime);
	CWeatherManager::GetInstance()->Update( fElapsedTime );

	if(PW.GetFired())
		PW.Update(fElapsedTime);

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
}

void CGameplayState::Render(void)
{
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

	{
		WORLD->RenderWorld();

		D3D->GetSprite()->Flush();

		if(PW.GetFired())
			PW.Render();

		D3D->GetSprite()->Flush();

		OBJECTS->RenderObjects();

		D3D->GetSprite()->Flush();
	}

	D3D->GetSprite()->Flush();

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

	if(GAME->GetPaused() == true)
	{
		GAME->GetFont()->Write("GAME IS PAUSED", 24, 2 * GAME->GetFont()->GetCharHeight(), D3DCOLOR_XRGB(255, 0, 0));
		GAME->GetFont()->Write("Press ESC again to resume", 32, 3 * GAME->GetFont()->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
		GAME->GetFont()->Write("ESC brings up player inventory!", 32, 4 * GAME->GetFont()->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
		GAME->GetFont()->Write("PRESS DELETE FOR MAIN MENU", 32, 6 * GAME->GetFont()->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	}

	D3D->SpriteEnd();
	D3D->DeviceEnd();
	D3D->Present();
}

void CGameplayState::Exit(void)
{
	
	WORLD->ShutdownWorldEngine();
	WORLD->DeleteInstance();
	EVENTS->ShutdownEventSystem();
	MESSAGES->ShutdownMessageSystem();
	OBJECTS->RemoveAllObjects();
	OBJECTS->DeleteInstance();
	
	//CWeatherManager::GetInstance()->SetTypeOfWeather( 0 );
	CWeatherManager::GetInstance()->ShutDown();
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
	else if(pEvent->GetEventID() == "LightTorch")
	{
		CMap::TileInfo* eventInfo = (CMap::TileInfo*)pEvent->GetParam();

		int PosX = eventInfo->Map->GetPosX() + eventInfo->Map->GetTileset()->GetTileWidth() * eventInfo->sMapPosX;
		int PosY = eventInfo->Map->GetPosY() + eventInfo->Map->GetTileset()->GetTileHeight() * eventInfo->sMapPosY;

		PosX += 15;
		PosY -= 5;

		PW.Fire();
		PW.emitter.EmitterPosX = (float)PosX;
		PW.emitter.EmitterPosY = (float)PosY;
	}
}

void CGameplayState::MessageProc(CBaseMessage* pMsg)
{
	switch(pMsg->GetMsgID())
	{
	case MSG_CREATE_PLAYER:
		{
			//CCreatePlayerMessage* pCPM = (CCreatePlayerMessage*)pMsg;
			//CGameplayState* pGameplay = CGameplayState::GetInstance();

			//// TODO: Add code here
			//pGameplay->pPlayer = new TestPlayer();
			//pGameplay->pPlayer->Enter();
			//pGameplay->pPlayer->SetPosX(pCPM->GetPosX());
			//pGameplay->pPlayer->SetPosY(pCPM->GetPosY());
			//break;
		}
	}
}

void CGameplayState::RenderHUD()
{
	RECT r1;

	r1.left = 39;
	r1.top = 0;
	r1.right = 39+39;
	r1.bottom = 128;

	//	Draw the amulet!
	TEX_MNG->Draw(m_imgHUD, 0, 0, 1.0f, 1.0f, &r1);

	r1.left = 0;
	r1.top = 0;
	r1.right = 39;
	r1.bottom = 128;

	//	Draw the weapon!
	TEX_MNG->Draw(m_imgHUD, 800-39, 0, 1.0f, 1.0f, &r1);

	//	Draw some life hearts
	unsigned int tempMaxH = 8;
	unsigned int tempCurH = 6;

	r1.left = 78;
	r1.top = 0;
	r1.right = 78+32;
	r1.bottom = 32;

	for(unsigned int i = 0; i < 10; ++i)
	{
		if(i < tempCurH)
		{
			//	Define a solid heart
			r1.top = 0;
			r1.bottom = 32;
		}
		else if(i >= tempMaxH)
		{
			//	Define an invisible heart
			r1.top = 64;
			r1.bottom = 96;
		}
		else
		{
			//	Define a broken heart
			r1.top = 32;
			r1.bottom = 64;
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

	float tempXP = 0.7f;

	//	Draw the weapon XP bar foreground
	r1.left = 110 + (320 * (1.0f - tempXP));
	r1.top = 0;
	r1.bottom = 32;

	TEX_MNG->Draw(m_imgHUD, 800-39-(320*tempXP), 4, 1.0f, 1.0f, &r1);

	//	Define the potion spot
	r1.left = 206;
	r1.top = 64;
	r1.right = 206+64;
	r1.bottom = 64+64;

	//	Draw the potion spot
	TEX_MNG->Draw(m_imgHUD, 800-400-32, 4, 1.0f, 1.0f, &r1);

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