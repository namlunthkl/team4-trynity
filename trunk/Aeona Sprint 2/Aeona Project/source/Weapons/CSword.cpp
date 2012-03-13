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
	CBaseCharacter::LoadAnimations("resource/AeonaFireSword.xml");
	SetAttacking(false);
	SetSound(new Sound("resource/sound/Sword.wav"));

	m_fSlashTimer = 0.0f;
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

	if( GetAttacking() == true )
		m_fSlashTimer += fElapsedTime;
}
void CSword::Attack(void)
{
	SetAttacking(true);
	if(m_fSlashTimer == 0.0f)
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
		rectCollision.top = -15 - 76;
		rectCollision.bottom = -15;
		if(m_fSlashTimer < 0.1f)
		{
			rectCollision.left = -32;
			rectCollision.right = 0;
		}
		else if(m_fSlashTimer < 0.2f)
		{
			rectCollision.left = -22;
			rectCollision.right = 22;
		}
		else if(m_fSlashTimer < 0.3f)
		{
			rectCollision.left = 0;
			rectCollision.right = 32;
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
		rectCollision.top = 15;
		rectCollision.bottom = 15 + 76;
		if(m_fSlashTimer < 0.1f)
		{
			rectCollision.left = 0;
			rectCollision.right = 32;
		}
		else if(m_fSlashTimer < 0.2f)
		{
			rectCollision.left = -22;
			rectCollision.right = 22;
		}
		else if(m_fSlashTimer < 0.3f)
		{
			rectCollision.left = -32;
			rectCollision.right = 0;
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
		rectCollision.left = -15 - 76;
		rectCollision.right = -15;
		if(m_fSlashTimer < 0.1f)
		{
			rectCollision.top = 0;
			rectCollision.bottom = 32;
		}
		else if(m_fSlashTimer < 0.2f)
		{
			rectCollision.top = -22;
			rectCollision.bottom = 22;
		}
		else if(m_fSlashTimer < 0.3f)
		{
			rectCollision.top = -32;
			rectCollision.bottom = 0;
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
		rectCollision.left = 15;
		rectCollision.right = 15 + 76;
		if(m_fSlashTimer < 0.1f)
		{
			rectCollision.top = -32;
			rectCollision.bottom = 0;
		}
		else if(m_fSlashTimer < 0.2f)
		{
			rectCollision.top = -22;
			rectCollision.bottom = 22;
		}
		else if(m_fSlashTimer < 0.3f)
		{
			rectCollision.top = 0;
			rectCollision.bottom = 32;
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