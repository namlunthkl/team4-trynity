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
	CBaseCharacter::LoadAnimations("resource/aeonaEarthHammer.xml");
	SetAttacking(false);

	SetSound(new Sound("resource/sound/AtkHammerHit.wav"));
	m_sndCharged = AUDIO->SFXLoadSound("resource/sound/AtkHammerBlast.wav");

	m_fSlashTimer = 0.0f;
}
CHammer::~CHammer()
{
	AUDIO->SFXUnloadSound(m_sndCharged);
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
	CPlayer::GetInstance()->SetAttackDamage(50);
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
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack == false)
			{
				GetSound()->Play();

				rectCollision.left = -22;
				rectCollision.top = -22 - 60;
				rectCollision.right = 22;
				rectCollision.bottom = 22 - 50;
			}
			else
			{
				if(AUDIO->SFXIsSoundPlaying(m_sndCharged) == false)
				{
					AUDIO->SFXPlaySound(m_sndCharged);
				}
				rectCollision.left = -110;
				rectCollision.top = -110;
				rectCollision.right = 110;
				rectCollision.bottom = 110;
				CPlayer::GetInstance()->m_fBlastTimer = 0.35f;
				CPlayer::GetInstance()->SetAttackDamage(76);
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
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack == false)
			{
				GetSound()->Play();

				rectCollision.left = -22;
				rectCollision.top = -22 + 50;
				rectCollision.right = 22;
				rectCollision.bottom = 22 + 60;
			}
			else
			{
				if(AUDIO->SFXIsSoundPlaying(m_sndCharged) == false)
				{
					AUDIO->SFXPlaySound(m_sndCharged);
				}
				rectCollision.left = -110;
				rectCollision.top = -110;
				rectCollision.right = 110;
				rectCollision.bottom = 110;
				CPlayer::GetInstance()->m_fBlastTimer = 0.35f;
				CPlayer::GetInstance()->SetAttackDamage(76);
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
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack == false)
			{
				GetSound()->Play();

				rectCollision.left = -22 - 60;
				rectCollision.top = -22;
				rectCollision.right = 22 - 50;
				rectCollision.bottom = 22;
			}
			else
			{
				if(AUDIO->SFXIsSoundPlaying(m_sndCharged) == false)
				{
					AUDIO->SFXPlaySound(m_sndCharged);
				}
				rectCollision.left = -110;
				rectCollision.top = -110;
				rectCollision.right = 110;
				rectCollision.bottom = 110;
				CPlayer::GetInstance()->m_fBlastTimer = 0.35f;
				CPlayer::GetInstance()->SetAttackDamage(76);
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
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack == false)
			{
				GetSound()->Play();

				rectCollision.left = -22 + 50;
				rectCollision.top = -22;
				rectCollision.right = 22 + 60;
				rectCollision.bottom = 22;
			}
			else
			{
				if(AUDIO->SFXIsSoundPlaying(m_sndCharged) == false)
				{
					AUDIO->SFXPlaySound(m_sndCharged);
				}
				rectCollision.left = -110;
				rectCollision.top = -110;
				rectCollision.right = 110;
				rectCollision.bottom = 110;
				CPlayer::GetInstance()->m_fBlastTimer = 0.35f;
				CPlayer::GetInstance()->SetAttackDamage(76);
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