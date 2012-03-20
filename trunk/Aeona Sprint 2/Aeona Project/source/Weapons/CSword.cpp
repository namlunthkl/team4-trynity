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
	CBaseCharacter::LoadAnimations("resource/aeonaFireSword.xml");
	SetAttacking(false);

	SetSound(new Sound("resource/sound/AtkFireSlash.wav"));
	m_sndCharged = AUDIO->SFXLoadSound("resource/sound/AtkFireWhirl.wav");

	m_fSlashTimer = 0.0f;
}
CSword::~CSword()
{
	AUDIO->SFXUnloadSound(m_sndCharged);
}
void CSword::Render(PointD nPos)
{
	SetPosX(nPos.x);
	SetPosY(nPos.y);
	
	CBaseCharacter::Render();
}
void CSword::Render(PointD nPos,DWORD WHICHCOLORYOUWANTHIMTOGLOWBRO)
{
	SetPosX(nPos.x);
	SetPosY(nPos.y);

	CBaseCharacter::Render(WHICHCOLORYOUWANTHIMTOGLOWBRO);
}

void CSword::Update(float fElapsedTime)
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
void CSword::Attack(void)
{
	SetAttacking(true);
	CPlayer::GetInstance()->SetAttackDamage(24);
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
		if(m_fSlashTimer < 0.125f)
		{
			rectCollision.left = -40;
			rectCollision.right = 0;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -100;
				rectCollision.top = -100;
				rectCollision.right = 100;
				rectCollision.bottom = 100;
				CPlayer::GetInstance()->m_fBlastTimer = 0.35f;
				CPlayer::GetInstance()->SetAttackDamage(33);
			}
		}
		else if(m_fSlashTimer < 0.25f)
		{
			rectCollision.left = -27;
			rectCollision.right = 27;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -100;
				rectCollision.top = -100;
				rectCollision.right = 100;
				rectCollision.bottom = 100;
			}
		}
		else if(m_fSlashTimer < 0.375f)
		{
			rectCollision.left = 0;
			rectCollision.right = 40;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -100;
				rectCollision.top = -100;
				rectCollision.right = 100;
				rectCollision.bottom = 100;
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
		rectCollision.bottom = 15 + 76;
		if(m_fSlashTimer < 0.125f)
		{
			rectCollision.left = 0;
			rectCollision.right = 40;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -100;
				rectCollision.top = -100;
				rectCollision.right = 100;
				rectCollision.bottom = 100;
				CPlayer::GetInstance()->m_fBlastTimer = 0.35f;
				CPlayer::GetInstance()->SetAttackDamage(33);
			}
		}
		else if(m_fSlashTimer < 0.25f)
		{
			rectCollision.left = -27;
			rectCollision.right = 27;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -100;
				rectCollision.top = -100;
				rectCollision.right = 100;
				rectCollision.bottom = 100;
			}
		}
		else if(m_fSlashTimer < 0.375f)
		{
			rectCollision.left = -40;
			rectCollision.right = 0;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -100;
				rectCollision.top = -100;
				rectCollision.right = 100;
				rectCollision.bottom = 100;
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
		rectCollision.left = -15 - 76;
		rectCollision.right = -15;
		if(m_fSlashTimer < 0.125f)
		{
			rectCollision.top = 0;
			rectCollision.bottom = 40;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -100;
				rectCollision.top = -100;
				rectCollision.right = 100;
				rectCollision.bottom = 100;
				CPlayer::GetInstance()->m_fBlastTimer = 0.35f;
				CPlayer::GetInstance()->SetAttackDamage(33);
			}
		}
		else if(m_fSlashTimer < 0.25f)
		{
			rectCollision.top = -27;
			rectCollision.bottom = 27;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -100;
				rectCollision.top = -100;
				rectCollision.right = 100;
				rectCollision.bottom = 100;
			}
		}
		else if(m_fSlashTimer < 0.375f)
		{
			rectCollision.top = -40;
			rectCollision.bottom = 0;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -100;
				rectCollision.top = -100;
				rectCollision.right = 100;
				rectCollision.bottom = 100;
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
		rectCollision.right = 15 + 76;
		if(m_fSlashTimer < 0.125f)
		{
			rectCollision.top = 0;
			rectCollision.bottom = 40;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -100;
				rectCollision.top = -100;
				rectCollision.right = 100;
				rectCollision.bottom = 100;
				CPlayer::GetInstance()->m_fBlastTimer = 0.35f;
				CPlayer::GetInstance()->SetAttackDamage(33);
			}
		}
		else if(m_fSlashTimer < 0.25f)
		{
			rectCollision.top = -27;
			rectCollision.bottom = 27;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -100;
				rectCollision.top = -100;
				rectCollision.right = 100;
				rectCollision.bottom = 100;
			}
		}
		else if(m_fSlashTimer < 0.375f)
		{
			rectCollision.top = -40;
			rectCollision.bottom = 0;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -100;
				rectCollision.top = -100;
				rectCollision.right = 100;
				rectCollision.bottom = 100;
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