////////////////////////////////////////////////////////////////////////
//    File Name				:	"CGameplayState.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09/12 - 1:00 AM
//    Purpose				:	Contains the GameplayState
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "CGameplayState.h"
#include "..\Animation\CAnimationManager.h"
#include "..\Messaging\CEventSystem.h"

#include "..\Tile Mapping\CWorldEngine.h"


CGameplayState::CGameplayState(void)
{
	CEventSystem::GetInstance()->RegisterForEvent("SpawnMessageBox", this);
}
void CGameplayState::Enter(void)
{
	// Initialize the best world engine ever created
	CWorldEngine::GetInstance()->InitWorldEngine();
	
	//	How to load an animation using Bern's crappy animation editor
	//		CAnimationManager::GetInstance()->LoadAnimation("resource/Animation.xml");	
	//		gethit=new CAnimationPlayer(0,true);
	//		gethit->Play();

	CAnimationManager* pAM = CAnimationManager::GetInstance();

	pAM->LoadAnimation("resource/character_walking.xml");
	WalkUp = new CAnimationPlayer(0, true);
	WalkDown = new CAnimationPlayer(1, true);
	WalkLeft = new CAnimationPlayer(2, true);
	WalkRight = new CAnimationPlayer(3, true);

	// TESTING
	pPlayer = new TestPlayer();
	pPlayer->Enter();
}
bool CGameplayState::Input(void)
{
	// TESTING
	int nNewPlayerPosX = pPlayer->GetPosX();
	int nNewPlayerPosY = pPlayer->GetPosY();

	if(INPUT->KeyDown(DIK_UP))
	{
		nNewPlayerPosY--;
		WalkUp->Play();
	}
	else
		WalkUp->Stop();

	if(INPUT->KeyDown(DIK_DOWN))
	{
		nNewPlayerPosY++;
		WalkDown->Play();
	}
	else
		WalkDown->Stop();

	if(INPUT->KeyDown(DIK_LEFT))
	{
		nNewPlayerPosX--;
		WalkLeft->Play();
	}
	else
		WalkLeft->Stop();

	if(INPUT->KeyDown(DIK_RIGHT))
	{
		nNewPlayerPosX++;
		WalkRight->Play();
	}
	else
		WalkRight->Stop();

	TestPlayer* pTempPlayer = new TestPlayer();
	pTempPlayer->Enter();
	pTempPlayer->SetPosX(nNewPlayerPosX);
	pTempPlayer->SetPosY(nNewPlayerPosY);

	if(!CWorldEngine::GetInstance()->CheckCollisions(pTempPlayer))
	{
		pPlayer->SetPosX(nNewPlayerPosX);
		pPlayer->SetPosY(nNewPlayerPosY);
	}

	delete pTempPlayer;

	return true;
}
void CGameplayState::Update(float fElapsedTime)
{
	// Update the best world engine ever created
	CWorldEngine::GetInstance()->UpdateWorld(fElapsedTime);

	/*gethit->Update(fElapsedTime);*/

	CEventSystem::GetInstance()->ProcessEvents();

	WalkUp->Update(fElapsedTime);
	WalkDown->Update(fElapsedTime);
	WalkRight->Update(fElapsedTime);
	WalkLeft->Update(fElapsedTime);

}
void CGameplayState::Render(void)
{
	// Render the best world engine ever created
	CWorldEngine::GetInstance()->RenderWorld();

	//gethit->Render(200,200);
	WalkUp->Render(pPlayer->GetPosX(), pPlayer->GetPosY());
	WalkDown->Render(pPlayer->GetPosX(), pPlayer->GetPosY());
	WalkLeft->Render(pPlayer->GetPosX(), pPlayer->GetPosY());
	WalkRight->Render(pPlayer->GetPosX(), pPlayer->GetPosY());

	// TESTING
	//pPlayer->Render();
}

void CGameplayState::Exit(void)
{
	CWorldEngine::GetInstance()->ShutdownWorldEngine();
	CWorldEngine::GetInstance()->DeleteInstance();
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
}