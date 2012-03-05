////////////////////////////////////////////////////////////////////////
//    File Name				:	"CDagger.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	3/01/12
//    Purpose				:	CDagger
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CDagger.h"
#include "../Game Objects/CPlayer.h"
CDagger::CDagger()
{

	//Load the Animation
	CBaseCharacter::LoadAnimations("resource/PlayerWDagger.xml");
	SetAttacking(false);
}
void CDagger::Render(PointD nPos)
{
	SetPosX(nPos.x);
	SetPosY(nPos.y);

	CBaseCharacter::Render();
}

void CDagger::Update(float fElapsedTime)
{
	CBaseCharacter::Update(fElapsedTime);

}
void CDagger::Attack(void)
{
	SetAttacking(true);

}
void CDagger::ChargedAttack(void)
{

}
