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

void CGameplayState::Enter(void)
{
	CreateMaps();
	CreatePuzzles();
	CAnimationManager::GetInstance()->LoadAnimation("resource/Animation.xml");
	gethit=new CAnimationPlayer(0);
}
bool CGameplayState::Input(void)
{
	gethit->Play();
	return true;
}
void CGameplayState::Update(float fElapsedTime)
{
	gethit->Update(fElapsedTime);
}
void CGameplayState::Render(void)
{
	gethit->Render();
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