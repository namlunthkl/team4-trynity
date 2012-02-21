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
	CWorldEngine::GetInstance()->InitWorldEngine();
	CAnimationManager::GetInstance()->LoadAnimation("resource/Blue Flower.xml");
	
	//gethit=new CAnimationPlayer(0,true);
	//gethit->Play();
	//gethit2 = new CAnimationPlayer(0,false);
	//gethit2->Play();
	// attack = new CAnimationPlayer(0,true);
	// attack->Play();
	//attack2 = new CAnimationPlayer(1,false);
	//attack2->Play();

	PW.Load("resource/data/FireFlicker.xml");
}
bool CGameplayState::Input(void)
{
	// TESTING
	/*int nNewPlayerPosX = pPlayer->GetPosX();
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
*/
	if(INPUT->KeyPressed(DIK_RETURN))
		PW.Fire(10, 10);


	return true;
}
void CGameplayState::Update(float fElapsedTime)
{
	// Update the best world engine ever created
	CWorldEngine::GetInstance()->UpdateWorld(fElapsedTime);

	/*gethit->Update(fElapsedTime);*/

	CEventSystem::GetInstance()->ProcessEvents();

	//WalkUp->Update(fElapsedTime);
	//WalkDown->Update(fElapsedTime);
	//WalkRight->Update(fElapsedTime);
	//WalkLeft->Update(fElapsedTime);

	PW.Update(fElapsedTime);

}
void CGameplayState::Render(void)
{
	// Render the best world engine ever created
	CWorldEngine::GetInstance()->RenderWorld();

	//gethit->Render(200,200);
	//WalkUp->Render(pPlayer->GetPosX(), pPlayer->GetPosY());
	//WalkDown->Render(pPlayer->GetPosX(), pPlayer->GetPosY());
	//WalkLeft->Render(pPlayer->GetPosX(), pPlayer->GetPosY());
	//WalkRight->Render(pPlayer->GetPosX(), pPlayer->GetPosY());

	// TESTING
	//pPlayer->Render();

	PW.Render();
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