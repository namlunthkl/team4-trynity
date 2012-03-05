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
RectD CCrossBow::GetCollisionRect(void)
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
