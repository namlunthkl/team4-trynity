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
	CreateMaps();
	CreatePuzzles();
}
bool CGameplayState::Input(void)
{
	return true;
}
void CGameplayState::Update(float fElapsedTime)
{
}
void CGameplayState::Render(void)
{
}
void CGameplayState::Exit(void)
{
}
CGameplayState* CGameplayState::GetInstance(void)
{
	static CGameplayState pInstance;
	return &pInstance;
}
void CGameplayState::CreateMaps(void)
{
}
void CGameplayState::CreatePuzzles(void)
{
}