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

	SetSound(new Sound("resource/sound/Hammer.wav"));

	m_fSlashTimer = 0.0f;
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
	GetSound()->Play();
}
void CHammer::ChargedAttack(void)
{

}

RectD CHammer::GetCollisionRect(void)
{
	RectD rectCollision;
	if(ANM_ATK_UP == GetCurrentAnimation())
	{
		rectCollision.left = -15;
		rectCollision.top = -62;
		rectCollision.right = 15;
		rectCollision.bottom = -32;
	}
	else if(ANM_ATK_DOWN == GetCurrentAnimation())
	{
		rectCollision.left = -15;
		rectCollision.top = 32;
		rectCollision.right = 15;
		rectCollision.bottom = 62;
	}
	else if(ANM_ATK_LEFT == GetCurrentAnimation())
	{
		rectCollision.left = -62;
		rectCollision.top = -15;
		rectCollision.right = -32;
		rectCollision.bottom = 15;
	}
	else if(ANM_ATK_RIGHT == GetCurrentAnimation())
	{
		rectCollision.left = 32;
		rectCollision.top = -15;
		rectCollision.right = 62;
		rectCollision.bottom = 15;
	}
	return rectCollision;
}