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

#include "../Input Manager/CInputManager.h"
#include "../Camera/CCameraControl.h"
#define WORLD CWorldEngine::GetInstance()

// Singleton Macros
#define EVENTS CEventSystem::GetInstance()
#define MESSAGES CMessageSystem::GetInstance()

// Constructor
CGameplayState::CGameplayState(void)
{
	pPlayer = NULL;
	pEnemy = NULL;
	m_nCameraPosX = 0;
	m_nCameraPosY = 0;
}

// Initialize everything
void CGameplayState::Enter(void)
{
	// Initialize the world engine
	WORLD->InitWorldEngine();
	
	// Register for the event
	EVENTS->RegisterForEvent("SpawnMessageBox", this);
	EVENTS->RegisterForEvent("LightTorch", this);

	// Initialize our particle weapon
	PW.Load("resource/data/FireFlicker.xml");
	m_Rain.Load("resource/data/rain.xml");
	m_Rain.Fire((int)(GAME->GetScreenWidth()*.5f),(int)(GAME->GetScreenHeight()*.5f));
	pPlayer = NULL;
	MESSAGES->InitMessageSystem(MessageProc);

	pEnemy = new CEnemy();
	pEnemy->Initialize(50, 50, 0, 1, 0, NULL, NULL);
	//pEnemy->SetImageID( TEX_MNG->LoadTexture("resource/TempAsset2.png"));
	pEnemy->SetVelX(1);
	pEnemy->SetVelY(1);

	// CAMERA->InitializeCamera();
	
	//	TODO  Temporary, just to demonstrate that the options work
	AUDIO->MusicPlaySong( AUDIO->MusicLoadSong("resource/KSC_Beginning.xwm") );

}

bool CGameplayState::Input(void)
{
	//	Pause
	if(CInputManager::GetInstance()->GetPressedPause())
	{
		GAME->SetPaused( !GAME->GetPaused() );
	}

	// Create player
	if(!pPlayer)
		if(INPUT->KeyPressed(DIK_SPACE))
			MESSAGES->SendMsg(new CCreatePlayerMessage(600, 100));

	// Move player
	if(pPlayer)
		pPlayer->Input();

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
if(pEnemy)
	pEnemy->Update(fElapsedTime);

	MESSAGES->ProcessMessages();
	
	if(pPlayer)
		pPlayer->Update(fElapsedTime);

	///////////////////
	// Update camera
	///////////////////
	if(pPlayer)
	{
		int nNewCameraPosX = pPlayer->GetPosX() - GAME->GetScreenWidth() / 2;
		int nNewCameraPosY = pPlayer->GetPosY() - GAME->GetScreenHeight() / 2;

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
		PW.Render();
	
	D3D->GetSprite()->Flush();

	if(pPlayer)
		pPlayer->Render();
	if(pEnemy)
		pEnemy->Render();
	m_Rain.Render();

}

void CGameplayState::Exit(void)
{
	WORLD->ShutdownWorldEngine();
	WORLD->DeleteInstance();
	EVENTS->ShutdownEventSystem();
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
	else if(pEvent->GetEventID() == "LightTorch")
	{
		CMap::TileInfo* eventInfo = (CMap::TileInfo*)pEvent->GetParam();

		int PosX = eventInfo->Map->GetPosX() + eventInfo->Map->GetTileset()->GetTileWidth() * eventInfo->sMapPosX;
		int PosY = eventInfo->Map->GetPosY() + eventInfo->Map->GetTileset()->GetTileHeight() * eventInfo->sMapPosY;

		PosX = GetScreenPositionX(PosX);
		PosY = GetScreenPositionY(PosY);

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
			CCreatePlayerMessage* pCPM = (CCreatePlayerMessage*)pMsg;
			CGameplayState* pGameplay = CGameplayState::GetInstance();

			// TODO: Add code here
			pGameplay->pPlayer = new TestPlayer();
			pGameplay->pPlayer->Enter();
			pGameplay->pPlayer->SetPosX(pCPM->GetPosX());
			pGameplay->pPlayer->SetPosY(pCPM->GetPosY());
			break;
		}
	};
}

