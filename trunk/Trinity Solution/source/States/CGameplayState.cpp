////////////////////////////////////////////////////////////////////////
//    File Name				:	"CGameplayState.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09/12 - 1:00 AM
//    Purpose				:	Contains the GameplayState
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "CGameplayState.h"

void CGameplayState::Enter(void)
{
	CWorldEngine::GetInstance()->InitWorldEngine();
}
bool CGameplayState::Input(void)
{
	return true;
}
void CGameplayState::Update(float fElapsedTime)
{
	CWorldEngine::GetInstance()->UpdateWorld(fElapsedTime);
}
void CGameplayState::Render(void)
{
	CWorldEngine::GetInstance()->RenderWorld();
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
