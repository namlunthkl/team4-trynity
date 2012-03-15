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
	CBaseCharacter::LoadAnimations("resource/AeonaEarthHammer.xml");
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
	rectCollision.left = 1;
	rectCollision.top = 1;
	rectCollision.right = 1;
	rectCollision.bottom = 1;

	if(ANM_ATK_UP == GetCurrentAnimation())
	{
		if(m_fSlashTimer < 0.75f)
		{
			rectCollision.left = -2;
			rectCollision.top = -2;
			rectCollision.right = 2;
			rectCollision.bottom = 2;
		}
		else if(m_fSlashTimer < 1.0f)
		{
			rectCollision.left = -22;
			rectCollision.top = -22 - 60;
			rectCollision.right = 22;
			rectCollision.bottom = 22 - 60;
		}
		else
		{
			rectCollision.left = -2;
			rectCollision.top = -2;
			rectCollision.right = 2;
			rectCollision.bottom = 2;
			SetAttacking(false);
			m_fSlashTimer = 0.0f;
		}
	}
	else if(ANM_ATK_DOWN == GetCurrentAnimation())
	{
		if(m_fSlashTimer < 0.75f)
		{
			rectCollision.left = -2;
			rectCollision.top = -2;
			rectCollision.right = 2;
			rectCollision.bottom = 2;
		}
		else if(m_fSlashTimer < 1.0f)
		{
			rectCollision.left = -22;
			rectCollision.top = -22 + 60;
			rectCollision.right = 22;
			rectCollision.bottom = 22 + 60;
		}
		else
		{
			rectCollision.left = -2;
			rectCollision.top = -2;
			rectCollision.right = 2;
			rectCollision.bottom = 2;
			SetAttacking(false);
			m_fSlashTimer = 0.0f;
		}
	}
	else if(ANM_ATK_LEFT == GetCurrentAnimation())
	{
		if(m_fSlashTimer < 0.75f)
		{
			rectCollision.left = -2;
			rectCollision.top = -2;
			rectCollision.right = 2;
			rectCollision.bottom = 2;
		}
		else if(m_fSlashTimer < 1.0f)
		{
			rectCollision.left = -22 - 60;
			rectCollision.top = -22;
			rectCollision.right = 22 - 60;
			rectCollision.bottom = 22;
		}
		else
		{
			rectCollision.left = -2;
			rectCollision.top = -2;
			rectCollision.right = 2;
			rectCollision.bottom = 2;
			SetAttacking(false);
			m_fSlashTimer = 0.0f;
		}
	}
	else if(ANM_ATK_RIGHT == GetCurrentAnimation())
	{
		if(m_fSlashTimer < 0.75f)
		{
			rectCollision.left = -2;
			rectCollision.top = -2;
			rectCollision.right = 2;
			rectCollision.bottom = 2;
		}
		else if(m_fSlashTimer < 1.0f)
		{
			rectCollision.left = -22 + 60;
			rectCollision.top = -22;
			rectCollision.right = 22 + 60;
			rectCollision.bottom = 22;
		}
		else
		{
			rectCollision.left = -2;
			rectCollision.top = -2;
			rectCollision.right = 2;
			rectCollision.bottom = 2;
			SetAttacking(false);
			m_fSlashTimer = 0.0f;
		}
	}
	return rectCollision;
}