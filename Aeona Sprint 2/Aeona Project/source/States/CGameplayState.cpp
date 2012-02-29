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

// Singleton Macros
#define EVENTS CEventSystem::GetInstance()
#define MESSAGES CMessageSystem::GetInstance()
#define PLAYER CPlayer::GetInstance()
#define OBJECTS CObjectManager::GetInstance()

// Constructor
CGameplayState::CGameplayState(void)
{
	m_nCameraPosX = 0;
	m_nCameraPosY = 0;
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
	m_Rain.Load("resource/data/rain.xml");
	m_Rain.Fire((int)(GAME->GetScreenWidth()*.5f),(int)(GAME->GetScreenHeight()*.5f));
	MESSAGES->InitMessageSystem(MessageProc);

	// Add enemies to the level
	for(int i=0; i < 5; ++i)
	{
		for(int j = 0; j < 5; ++j)
		{
			CEnemy* pEnemy = new CEnemy(100 * i, 100 * j, 50, -1, 0, 0, true, 100, 1);
			pEnemy->ChangeAIState(CRandomAIState::GetInstance());
			pEnemy->SetDebugMode(false);
			OBJECTS->AddObject(pEnemy);
			pEnemy->Release();
		}
	}

	PLAYER->SetPosX(100);
	PLAYER->SetPosY(100);
	PLAYER->SetSpeed(100);
	//PLAYER->SetDebugMode(true);
	OBJECTS->AddObject(PLAYER);




	//	TODO  Temporary, just to demonstrate that the options work
	m_imgHUD = TEX_MNG->LoadTexture("resource/HUD.png", D3DCOLOR_XRGB(255, 255, 255));
	AUDIO->MusicPlaySong( AUDIO->MusicLoadSong("resource/KSC_Beginning.xwm"),true );

}

bool CGameplayState::Input(void)
{
	//	Pause
	if(CInputManager::GetInstance()->GetPressedPause())
	{
		GAME->SetPaused( !GAME->GetPaused() );
	}

	// Move player
	if(PLAYER)
		PLAYER->Input();

	return true;
}

void CGameplayState::Update(float fElapsedTime)
{
	// Update the best world engine ever created
	WORLD->UpdateWorld(fElapsedTime);
	EVENTS->ProcessEvents();
	m_Rain.Update(fElapsedTime);

	if(PW.GetFired())
		PW.Update(fElapsedTime);

	MESSAGES->ProcessMessages();
	OBJECTS->UpdateObjects(fElapsedTime);
	OBJECTS->CheckCollisions();

	///////////////////
	// Update camera
	///////////////////
	if(PLAYER)
	{
		int nNewCameraPosX = (int)PLAYER->GetPosX() - GAME->GetScreenWidth() / 2;
		int nNewCameraPosY = (int)PLAYER->GetPosY() - GAME->GetScreenHeight() / 2;

		m_nCameraPosX = nNewCameraPosX;
		m_nCameraPosY = nNewCameraPosY;

		if(m_nCameraPosX < 0)
			m_nCameraPosX = 0;
		if(m_nCameraPosY < 0)
			m_nCameraPosY = 0;
		if(m_nCameraPosX > WORLD->GetWorldWidth() - GAME->GetScreenWidth())
			m_nCameraPosX = WORLD->GetWorldWidth() - GAME->GetScreenWidth();
		if(m_nCameraPosY > WORLD->GetWorldHeight() - GAME->GetScreenHeight())
			m_nCameraPosY = WORLD->GetWorldHeight() - GAME->GetScreenHeight();
	}
}

void CGameplayState::Render(void)
{
	//	Render the best world engine ever created
	//	Daniel's just such a cool guy!
	WORLD->RenderWorld();

	if(PW.GetFired())
		PW.Render(m_nCameraPosX, m_nCameraPosY);
	
	D3D->GetSprite()->Flush();

	if(PLAYER)
		PLAYER->Render();

	OBJECTS->RenderObjects();

	if(CInputManager::GetInstance()->GetAttack())
	{
		D3D->DrawText("Button is Down",(int)(GAME->GetScreenWidth()*0.5f),(int)(GAME->GetScreenHeight()*0.5f));
		char buffer[100];
		sprintf_s(&buffer[0],100,"Value %f",CInputManager::GetInstance()->Timeheld());
		D3D->DrawText(buffer,(int)(GAME->GetScreenWidth()*0.5f+20),(int)(GAME->GetScreenHeight()*0.5f+20));
	}

	D3D->GetSprite()->Flush();

	m_Rain.Render();

	//	Render a neato HUD
	if(GAME->GetShowHUD() == true)		//	But why wouldn't you want to show it??!?
	{
		RenderHUD();
	}
}

void CGameplayState::Exit(void)
{
	WORLD->ShutdownWorldEngine();
	WORLD->DeleteInstance();
	EVENTS->ShutdownEventSystem();
	MESSAGES->ShutdownMessageSystem();
	OBJECTS->RemoveAllObjects();
	OBJECTS->DeleteInstance();
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

		PW.Fire(PosX, PosY);
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
	RECT rFace;
	rFace.left = 112;
	rFace.top = 0;
	rFace.right = 112+66;
	rFace.bottom = 66;

	RECT rItem;
	rItem.left = 112+66;
	rItem.top = 0;
	rItem.right = 112+66+66;
	rItem.bottom = 66;

	RECT rHeart;
	rHeart.left = 64;
	rHeart.top = 0;
	rHeart.right = 64+24;
	rHeart.bottom = 22;

	RECT rBroke;
	rBroke.left = 64+24;
	rBroke.top = 0;
	rBroke.right = 64+24+24;
	rBroke.bottom = 22;

	//	Draw the face thing
	TEX_MNG->Draw(m_imgHUD, 4, 4, 1.0f, 1.0f, &rFace);

	//	Draw the item box thing
	TEX_MNG->Draw(m_imgHUD, 64+128, 4, 1.0f, 1.0f, &rItem);

	//	Draw some lil hearts inbetween the two boxes
	unsigned int tempMaxH = 10;
	unsigned int tempCurH = 6;

	//	Draw the first row of 5 hearts
	for(unsigned int i = 1; i < 6; ++i)
	{
		if(i <= tempCurH)
			TEX_MNG->Draw(m_imgHUD, 4+66+1 + (i-1)*24, 4, 1.0f, 1.0f, &rHeart);
		else
			TEX_MNG->Draw(m_imgHUD, 4+66+1 + (i-1)*24, 4, 1.0f, 1.0f, &rBroke);
	}
	//	Draw the second row of 5 hearts
	for(unsigned int i = 1; i < 6; ++i)
	{
		if(i+5 <= tempCurH)
			TEX_MNG->Draw(m_imgHUD, 4+66+1 + (i-1)*24, 4+22, 1.0f, 1.0f, &rHeart);
		else
			TEX_MNG->Draw(m_imgHUD, 4+66+1 + (i-1)*24, 4+22, 1.0f, 1.0f, &rBroke);
	}

	RECT rMap;
	rMap.left = 112;
	rMap.top = 66;
	rMap.right = 112+96;
	rMap.bottom = 66+96;

	//	Draw the minimap frame
	if(GAME->GetMapLocation() == 0)
	{
		TEX_MNG->Draw(m_imgHUD, 800-96-4, 4, 1.0f, 1.0f, &rMap);
	}
	else if(GAME->GetMapLocation() == 1)
	{
		TEX_MNG->Draw(m_imgHUD, 4, 600-96-4, 1.0f, 1.0f, &rMap);
	}
	else
	{
		TEX_MNG->Draw(m_imgHUD, 800-96-4, 600-96-4, 1.0f, 1.0f, &rMap);
	}
}