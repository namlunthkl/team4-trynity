////////////////////////////////////////////////////////////////////////
//    File Name				:	"CCrossBow.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	3/01/12
//    Purpose				:	CCrossBow
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CCrossBow.h"
#include "../Game Objects/CPlayer.h"
CCrossBow::CCrossBow()
{

	//Load the Animation
	CBaseCharacter::LoadAnimations("resource/PlayerWCrossBow.xml");
	SetAttacking(false);
}
void CCrossBow::Render(PointD nPos)
{
	SetPosX(nPos.x);
	SetPosY(nPos.y);

	CBaseCharacter::Render();
}

void CCrossBow::Update(float fElapsedTime)
{
	CBaseCharacter::Update(fElapsedTime);

}
void CCrossBow::Attack(void)
{
	SetAttacking(true);

}
void CCrossBow::ChargedAttack(void)
{

}
