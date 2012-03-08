////////////////////////////////////////////////////////////////////////
//    File Name				:	"CSword.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	3/01/12
//    Purpose				:	CSword
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CSword.h"
#include "../Game Objects/CPlayer.h"
CSword::CSword()
{
	//Load the Animation
	CBaseCharacter::LoadAnimations("resource/PlayerWSword.xml");
	SetAttacking(false);

	SetSound(new Sound("resource/sound/Sword.wav"));
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
void CSword::Attack(void)
{
	SetAttacking(true);
	GetSound()->Play();
}

void CSword::ChargedAttack(void)
{
	
}
RectD CSword::GetCollisionRect(void)
{
	RectD rectCollision;
	if(ANM_ATK_UP == GetCurrentAnimation())
	{
		rectCollision.left = -36;
		rectCollision.top = -66;
		rectCollision.right = 36;
		rectCollision.bottom = -5;
	}
	else if(ANM_ATK_DOWN == GetCurrentAnimation())
	{
		rectCollision.left = -36;
		rectCollision.top = 5;
		rectCollision.right = 36;
		rectCollision.bottom = 66;
	}
	else if(ANM_ATK_LEFT == GetCurrentAnimation())
	{
		rectCollision.left = -66;
		rectCollision.top = -36;
		rectCollision.right = -5;
		rectCollision.bottom = 30;
	}
	else if(ANM_ATK_RIGHT == GetCurrentAnimation())
	{
		rectCollision.left = 5;
		rectCollision.top = -36;
		rectCollision.right = 66;
		rectCollision.bottom = 30;
	}
	return rectCollision;
}