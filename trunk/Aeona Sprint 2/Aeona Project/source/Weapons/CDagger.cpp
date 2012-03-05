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
RectD CDagger::GetCollisionRect(void)
{
	RectD rectCollision;
	if(ANM_ATK_UP == GetCurrentAnimation())
	{
		rectCollision.left = -20;
		rectCollision.top = -25;
		rectCollision.right = 20;
		rectCollision.bottom = -5;
	}
	else if(ANM_ATK_DOWN == GetCurrentAnimation())
	{
		rectCollision.left = -20;
		rectCollision.top = 5;
		rectCollision.right = 20;
		rectCollision.bottom = 25;
	}
	else if(ANM_ATK_LEFT == GetCurrentAnimation())
	{
		rectCollision.left = -25;
		rectCollision.top = -20;
		rectCollision.right = -5;
		rectCollision.bottom = 20;
	}
	else if(ANM_ATK_RIGHT == GetCurrentAnimation())
	{
		rectCollision.left = 5;
		rectCollision.top = -20;
		rectCollision.right = 25;
		rectCollision.bottom = 20;
	}
	return rectCollision;
}