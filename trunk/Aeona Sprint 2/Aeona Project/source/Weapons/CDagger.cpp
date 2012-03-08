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

	SetSound(new Sound("resource/sound/Dagger.wav"));
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
	GetSound()->Play();
}
void CDagger::ChargedAttack(void)
{

}
RectD CDagger::GetCollisionRect(void)
{
	RectD rectCollision;
	if(ANM_ATK_UP == GetCurrentAnimation())
	{
		rectCollision.left = -32;
		rectCollision.top = -50;
		rectCollision.right = 32;
		rectCollision.bottom = 0;
	}
	else if(ANM_ATK_DOWN == GetCurrentAnimation())
	{
		rectCollision.left = -32;
		rectCollision.top = 0;
		rectCollision.right = 32;
		rectCollision.bottom = 50;
	}
	else if(ANM_ATK_LEFT == GetCurrentAnimation())
	{
		rectCollision.left = -50;
		rectCollision.top = -32;
		rectCollision.right = 0;
		rectCollision.bottom = 32;
	}
	else if(ANM_ATK_RIGHT == GetCurrentAnimation())
	{
		rectCollision.left = 0;
		rectCollision.top = -32;
		rectCollision.right = 50;
		rectCollision.bottom = 32;
	}
	return rectCollision;
}