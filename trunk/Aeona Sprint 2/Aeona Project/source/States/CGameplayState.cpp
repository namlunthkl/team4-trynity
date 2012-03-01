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

	CNPC* pNPC = new CNPC(true, 150, -1, pFont, 400, 200, 20, -1, 0, 0, true, 100, 0);
	pNPC->LoadAnimations("resource/npc walk2.xml");
	pNPC->ChangeAIState(CRandomAIState::GetInstance());
	pNPC->SetDebugMode(false);
	pNPC->LoadText("Hello. I am the first NPC of this game.");
	OBJECTS->AddObject(pNPC);
	pNPC->Release();

	CNPC* pNPC2 = new CNPC(false, 150, -1, pFont, 700, 500, 20, -1, 0, 0, true, 100, 0);
	pNPC2->LoadAnimations("resource/npc walk2.xml");
	pNPC2->ChangeAIState(CRandomAIState::GetInstance());
	pNPC2->SetDebugMode(false);
	pNPC2->LoadText("I am so confused");
	OBJECTS->AddObject(pNPC2);
	pNPC2->Release();


	PLAYER->SetPosX(600);
	PLAYER->SetPosY(200);
	PLAYER->SetSpeed(100);
	//PLAYER->SetDebugMode(true);
	OBJECTS->AddObject(PLAYER);




	//	TODO  Temporary, just to demonstrate that the options work
	m_imgHUD = TEX_MNG->LoadTexture("resource/HUD_Graphic.bmp", D3DCOLOR_XRGB(255, 0, 255));
	AUDIO->MusicPlaySong( AUDIO->MusicLoadSong("resource/KSC_Beginning.xwm"),true );

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
	unsigned int tempMaxH = 10;
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
			//	(Rect already defined!)
		}
		else if(i >= tempMaxH)
		{
			//	Define an invisible heart
			r1.top += 64;
			r1.bottom += 64;
		}
		else
		{
			//	Define a broken heart
			r1.top += 32;
			r1.bottom += 32;
		}
		TEX_MNG->Draw(m_imgHUD, 39+(i*32), 4, 1.0f, 1.0f, &r1);
	}

	//	Define the minimap frame
	r1.left = 0;
	r1.top = 0;
	r1.right = 96;
	r1.bottom = 96;

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