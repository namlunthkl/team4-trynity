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
CSword::CSword()
{
	
	//Load the Animation
	CBaseCharacter::LoadAnimations("resource/PlayerAnimations.xml");
	SetAttacking(false);
}
void CSword::Attack(void)
{
	//
	SetAttacking(true);

}
void CSword::Render(PointD nPos)
{
	SetPosX(nPos.x);
	SetPosY(nPos.y);
	
	CBaseCharacter::Render();
}
void CSword::Update(float fElapsedTime)
{
	CBaseCharacter::Update(fElapsedTime);
	
}
void CSword::ChargedAttack(void)
{
	//
}
//void CSword::SetWeaponRotation(float fWeaponRotation)
//{
//	SetRotation(fWeaponRotation);
//}