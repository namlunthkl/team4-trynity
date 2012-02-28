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

// Includes
#include "../Input Manager/CInputManager.h"
#include "../Camera/CCameraControl.h"
#include "../Game Objects/CPlayer.h"
#include "../AI_States/CRandomAIState.h"
#include "../Game Objects/CObjectManager.h"

// Singleton Macros
#define EVENTS CEventSystem::GetInstance()
#define MESSAGES CMessageSystem::GetInstance()
#define WORLD CWorldEngine::GetInstance()
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
	CEnemy* pEnemy = new CEnemy(50, 250, 50, -1, 0, 0, true, 100, 1);
	pEnemy->ChangeAIState(CRandomAIState::GetInstance());
	OBJECTS->AddObject(pEnemy);
	pEnemy->Release();


	PLAYER->SetPosX(100);
	PLAYER->SetPosY(100);
	PLAYER->SetSpeed(100);
	OBJECTS->AddObject(PLAYER);


	//	TODO  Temporary, just to demonstrate that the options work
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
	// Render the best world engine ever created
	WORLD->RenderWorld();

	if(PW.GetFired())
		PW.Render(m_nCameraPosX, m_nCameraPosY);
	
	D3D->GetSprite()->Flush();

	OBJECTS->RenderObjects();

	D3D->GetSprite()->Flush();

	m_Rain.Render();

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
	};
}

