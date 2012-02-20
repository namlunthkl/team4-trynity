////////////////////////////////////////////////////////////////////////
//    File Name				:	"CGameplayState.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09/12 - 1:00 AM
//    Purpose				:	Contains the GameplayState
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "CGameplayState.h"
#include "../TestPlayer.h"

void CGameplayState::Enter(void)
{
	CWorldEngine::GetInstance()->InitWorldEngine();
	

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
		nNewPlayerPosY--;
	if(INPUT->KeyDown(DIK_DOWN))
		nNewPlayerPosY++;
	if(INPUT->KeyDown(DIK_LEFT))
		nNewPlayerPosX--;
	if(INPUT->KeyDown(DIK_RIGHT))
		nNewPlayerPosX++;

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
	CWorldEngine::GetInstance()->UpdateWorld(fElapsedTime);
}
void CGameplayState::Render(void)
{
	CWorldEngine::GetInstance()->RenderWorld();

	// TESTING
	pPlayer->Render();
}
void CGameplayState::Exit(void)
{
	CWorldEngine::DeleteInstance();
}
CGameplayState* CGameplayState::GetInstance(void)
{
	static CGameplayState pInstance;
	return &pInstance;
}
