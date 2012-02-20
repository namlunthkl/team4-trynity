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

void CGameplayState::Enter(void)
{
	CreateMaps();
	CreatePuzzles();
	CAnimationManager::GetInstance()->LoadAnimation("resource/Animation.xml");
	
	gethit=new CAnimationPlayer(0,true);
	gethit->Play();
	gethit2 = new CAnimationPlayer(0,false);
	gethit2->Play();
	attack = new CAnimationPlayer(1,true);
	attack->Play();
	attack2 = new CAnimationPlayer(1,false);
	attack2->Play();
}
bool CGameplayState::Input(void)
{
	return true;
}
void CGameplayState::Update(float fElapsedTime)
{
	
	gethit->Update(fElapsedTime);
	gethit2->Update(fElapsedTime);
	attack->Update(fElapsedTime);
	attack2->Update(fElapsedTime);
	
	CEventSystem::GetInstance()->ProcessEvents();
}
void CGameplayState::Render(void)
{
	gethit->Render(200,200);
	gethit2->Render(400,200);
	attack->Render(200,400);
	attack2->Render(400,400);
	
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