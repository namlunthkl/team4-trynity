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
	CBaseCharacter::LoadAnimations("resource/aeonaDagger.xml");
	SetAttacking(false);

	SetSound(new Sound("resource/sound/AtkDaggerSlash.wav"));
	m_sndCharged = AUDIO->SFXLoadSound("resource/sound/AtkDaggerWhirl.wav");

	m_fSlashTimer = 0.0f;
}
CDagger::~CDagger()
{
	AUDIO->SFXUnloadSound(m_sndCharged);
}
void CDagger::Render(PointD nPos)
{
	SetPosX(nPos.x);
	SetPosY(nPos.y);

	CBaseCharacter::Render();
}
void CDagger::Render(PointD nPos,DWORD WHICHCOLORYOUWANTHIMTOGLOWBRO)
{
	SetPosX(nPos.x);
	SetPosY(nPos.y);

	CBaseCharacter::Render(WHICHCOLORYOUWANTHIMTOGLOWBRO);
}
void CDagger::Update(float fElapsedTime)
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
void CDagger::Attack(void)
{
	SetAttacking(true);
	CPlayer::GetInstance()->SetAttackDamage(16);
	if(m_fSlashTimer == 0.0f)
	{
		if(CPlayer::GetInstance()->m_bPhilSpecialAttack == false)
		{
			GetSound()->Play();
		}
		else
		{
			AUDIO->SFXPlaySound(m_sndCharged);
		}
	}
}
void CDagger::ChargedAttack(void)
{

}
RectD CDagger::GetCollisionRect(void)
{	
	RectD rectCollision;
	if(ANM_ATK_UP == GetCurrentAnimation())
	{
		rectCollision.top = -15 - 68;
		rectCollision.bottom = -15;
		if(m_fSlashTimer < 0.125f)
		{
			rectCollision.left = -34;
			rectCollision.right = 0;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -90;
				rectCollision.top = -90;
				rectCollision.right = 90;
				rectCollision.bottom = 90;
			}
		}
		else if(m_fSlashTimer < 0.25f)
		{
			rectCollision.left = -22;
			rectCollision.right = 22;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -90;
				rectCollision.top = -90;
				rectCollision.right = 90;
				rectCollision.bottom = 90;
			}
		}
		else if(m_fSlashTimer < 0.375f)
		{
			rectCollision.left = 0;
			rectCollision.right = 34;
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
		rectCollision.top = 15;
		rectCollision.bottom = 15 + 68;
		if(m_fSlashTimer < 0.125f)
		{
			rectCollision.left = 0;
			rectCollision.right = 34;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -90;
				rectCollision.top = -90;
				rectCollision.right = 90;
				rectCollision.bottom = 90;
			}
		}
		else if(m_fSlashTimer < 0.25f)
		{
			rectCollision.left = -22;
			rectCollision.right = 22;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -90;
				rectCollision.top = -90;
				rectCollision.right = 90;
				rectCollision.bottom = 90;
			}
		}
		else if(m_fSlashTimer < 0.375f)
		{
			rectCollision.left = -34;
			rectCollision.right = 0;
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
		rectCollision.left = -15 - 68;
		rectCollision.right = -15;
		if(m_fSlashTimer < 0.125f)
		{
			rectCollision.top = 0;
			rectCollision.bottom = 34;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -90;
				rectCollision.top = -90;
				rectCollision.right = 90;
				rectCollision.bottom = 90;
			}
		}
		else if(m_fSlashTimer < 0.25f)
		{
			rectCollision.top = -22;
			rectCollision.bottom = 22;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -90;
				rectCollision.top = -90;
				rectCollision.right = 90;
				rectCollision.bottom = 90;
			}
		}
		else if(m_fSlashTimer < 0.375f)
		{
			rectCollision.top = -34;
			rectCollision.bottom = 0;
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
		rectCollision.left = 15;
		rectCollision.right = 15 + 68;
		if(m_fSlashTimer < 0.125f)
		{
			rectCollision.top = 0;
			rectCollision.bottom = 34;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -90;
				rectCollision.top = -90;
				rectCollision.right = 90;
				rectCollision.bottom = 90;
			}
		}
		else if(m_fSlashTimer < 0.25f)
		{
			rectCollision.top = -22;
			rectCollision.bottom = 22;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -90;
				rectCollision.top = -90;
				rectCollision.right = 90;
				rectCollision.bottom = 90;
			}
		}
		else if(m_fSlashTimer < 0.375f)
		{
			rectCollision.top = -34;
			rectCollision.bottom = 0;
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