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

RectD CHammer::GetCollisionRect(void)
{
	RectD rectCollision;
	if(ANM_ATK_UP == GetCurrentAnimation())
	{
		rectCollision.left = -30;
		rectCollision.top = -35;
		rectCollision.right = 30;
		rectCollision.bottom = -5;
	}
	else if(ANM_ATK_DOWN == GetCurrentAnimation())
	{
		rectCollision.left = -30;
		rectCollision.top = 5;
		rectCollision.right = 30;
		rectCollision.bottom = 35;
	}
	else if(ANM_ATK_LEFT == GetCurrentAnimation())
	{
		rectCollision.left = -35;
		rectCollision.top = -30;
		rectCollision.right = -5;
		rectCollision.bottom = 30;
	}
	else if(ANM_ATK_RIGHT == GetCurrentAnimation())
	{
		rectCollision.left = 5;
		rectCollision.top = -30;
		rectCollision.right = 35;
		rectCollision.bottom = 30;
	}
	return rectCollision;
}