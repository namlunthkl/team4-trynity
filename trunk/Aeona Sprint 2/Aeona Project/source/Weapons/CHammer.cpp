////////////////////////////////////////////////////////////////////////
//    File Name				:	"CHammer.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	3/01/12
//    Purpose				:	CHammer
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CHammer.h"
#include "../Game Objects/CPlayer.h"
CHammer::CHammer()
{

	//Load the Animation
	CBaseCharacter::LoadAnimations("resource/PlayerWHammer.xml");
	SetAttacking(false);
}
void CHammer::Render(PointD nPos)
{
	SetPosX(nPos.x);
	SetPosY(nPos.y);

	CBaseCharacter::Render();
}

void CHammer::Update(float fElapsedTime)
{
	CBaseCharacter::Update(fElapsedTime);

}
void CHammer::Attack(void)
{
	SetAttacking(true);

}
void CHammer::ChargedAttack(void)
{

}
