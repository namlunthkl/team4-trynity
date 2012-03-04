////////////////////////////////////////////////////////////////////////
//    File Name				:	"CSword.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	3/01/12
//    Purpose				:	CSword
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CSword.h"
#include "../Game Objects/CPlayer.h"
#include "../States/CGameplayState.h"
#include "../Messaging/CMessageSystem.h"
#include "../Game Objects/CObjectManager.h"
CSword::CSword()
{
	
	//Load the Animation
	CBaseCharacter::LoadAnimations("resource/PlayerAnimationsAnchorBased.xml");
	SetAttacking(false);
	//CObjectManager::GetInstance()->AddObject(this);
}
void CSword::Render(PointD nPos)
{
	SetPosX(nPos.x);
	SetPosY(nPos.y);
	
	CBaseCharacter::Render();
}
//void CSword::Render(void)
//{
//
//}
void CSword::Update(float fElapsedTime)
{
	CBaseCharacter::Update(fElapsedTime);
	
}
void CSword::Attack(void)
{
	SetAttacking(true);

}
void CSword::ChargedAttack(void)
{
	
}
