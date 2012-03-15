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
void CHammer::Render(PointD nPos,DWORD WHICHCOLORYOUWANTHIMTOGLOWBRO)
{
	SetPosX(nPos.x);
	SetPosY(nPos.y);

	CBaseCharacter::Render(WHICHCOLORYOUWANTHIMTOGLOWBRO);
}
void CHammer::Update(float fElapsedTime)
{
	CBaseCharacter::Update(fElapsedTime);

	if( GetAttacking() == true )
	{
		m_fSlashTimer += fElapsedTime;
	}
	else
	{
		if( CPlayer::GetInstance()->m_bPhilCharging == true )
		{
			CPlayer::GetInstance()->m_fPhilChargeIdkman += fElapsedTime;
		}
	}
}

void CHammer::Attack(void)
{
	SetAttacking(true);
	if(m_fSlashTimer == 0.0f)
		GetSound()->Play();
}

void CHammer::ChargedAttack(void)
{

}

RectD CHammer::GetCollisionRect(void)
{
	RectD rectCollision;

	rectCollision.left = -2;
	rectCollision.top = -2;
	rectCollision.right = 2;
	rectCollision.bottom = 2;

	if(ANM_ATK_UP == GetCurrentAnimation())
	{
		if(m_fSlashTimer < 0.59f)
		{
		}
		else if(m_fSlashTimer < 0.75f)
		{
			rectCollision.left = -22;
			rectCollision.top = -22 - 60;
			rectCollision.right = 22;
			rectCollision.bottom = 22 - 50;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -90;
				rectCollision.top = -90;
				rectCollision.right = 90;
				rectCollision.bottom = 90;
			}
		}
		else
		{
			rectCollision.left = -2;
			rectCollision.top = -2;
			rectCollision.right = 2;
			rectCollision.bottom = 2;
			SetAttacking(false);
			m_fSlashTimer = 0.0f;
			CPlayer::GetInstance()->m_bPhilSpecialAttack = false;
		}
	}
	else if(ANM_ATK_DOWN == GetCurrentAnimation())
	{
		if(m_fSlashTimer < 0.59f)
		{
		}
		else if(m_fSlashTimer < 0.75f)
		{
			rectCollision.left = -22;
			rectCollision.top = -22 + 50;
			rectCollision.right = 22;
			rectCollision.bottom = 22 + 60;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -90;
				rectCollision.top = -90;
				rectCollision.right = 90;
				rectCollision.bottom = 90;
			}
		}
		else
		{
			rectCollision.left = -2;
			rectCollision.top = -2;
			rectCollision.right = 2;
			rectCollision.bottom = 2;
			SetAttacking(false);
			m_fSlashTimer = 0.0f;
			CPlayer::GetInstance()->m_bPhilSpecialAttack = false;
		}
	}
	else if(ANM_ATK_LEFT == GetCurrentAnimation())
	{
		if(m_fSlashTimer < 0.59f)
		{
		}
		else if(m_fSlashTimer < 0.75f)
		{
			rectCollision.left = -22 - 60;
			rectCollision.top = -22;
			rectCollision.right = 22 - 50;
			rectCollision.bottom = 22;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -90;
				rectCollision.top = -90;
				rectCollision.right = 90;
				rectCollision.bottom = 90;
			}
		}
		else
		{
			rectCollision.left = -2;
			rectCollision.top = -2;
			rectCollision.right = 2;
			rectCollision.bottom = 2;
			SetAttacking(false);
			m_fSlashTimer = 0.0f;
			CPlayer::GetInstance()->m_bPhilSpecialAttack = false;
		}
	}
	else if(ANM_ATK_RIGHT == GetCurrentAnimation())
	{
		if(m_fSlashTimer < 0.59f)
		{
		}
		else if(m_fSlashTimer < 0.75f)
		{
			rectCollision.left = -22 + 50;
			rectCollision.top = -22;
			rectCollision.right = 22 + 60;
			rectCollision.bottom = 22;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -90;
				rectCollision.top = -90;
				rectCollision.right = 90;
				rectCollision.bottom = 90;
			}
		}
		else
		{
			rectCollision.left = -2;
			rectCollision.top = -2;
			rectCollision.right = 2;
			rectCollision.bottom = 2;
			SetAttacking(false);
			m_fSlashTimer = 0.0f;
			CPlayer::GetInstance()->m_bPhilSpecialAttack = false;
		}
	}
	return rectCollision;
}