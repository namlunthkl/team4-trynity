////////////////////////////////////////////////////////////////////////
//    File Name				:	"CCrossBow.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	3/01/12
//    Purpose				:	CCrossBow
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CCrossBow.h"
#include "../Game Objects/CPlayer.h"
#include "../Game Objects/CObjectManager.h"
#include "../Game Objects/CArrow.h"
CCrossBow::CCrossBow()
{
	//Load the Animation
	CBaseCharacter::LoadAnimations("resource/AeonaAirCrossBow.xml");
	SetAttacking(false);
	m_pArrow = NULL;
	//m_fTime = 0;
	m_imgArrow = TEX_MNG->LoadTexture("resource/BlueArrow.png", D3DCOLOR_XRGB(0,0,0));
	SetSound(new Sound("resource/sound/Bow.wav"));

	m_fSlashTimer = 0.0f;
}
void CCrossBow::Render(PointD nPos)
{
	SetPosX(nPos.x);
	SetPosY(nPos.y);

	CBaseCharacter::Render();
}
void CCrossBow::Render(PointD nPos,DWORD WHICHCOLORYOUWANTHIMTOGLOWBRO)
{
	SetPosX(nPos.x);
	SetPosY(nPos.y);

	CBaseCharacter::Render(WHICHCOLORYOUWANTHIMTOGLOWBRO);
}
void CCrossBow::Update(float fElapsedTime)
{
	
	CBaseCharacter::Update(fElapsedTime);

	if(GetAttacking() == true)
	{
		m_fSlashTimer+= fElapsedTime;
	}
	else
	{
		if(CPlayer::GetInstance()->m_bPhilCharging == true)
		{
			CPlayer::GetInstance()->m_fPhilChargeIdkman += fElapsedTime;
		}
	}

}
void CCrossBow::Attack(void)
{
	SetAttacking(true);
	if(m_fSlashTimer == 0.0f)
	{
		GetSound()->Play();
		if(CPlayer::GetInstance()->m_bPhilSpecialAttack == false)
		{
			//m_fSlashTimer = 0.0f;
			ShootArrow();
		}
	}
}
void CCrossBow::ChargedAttack(void)
{

}

RectD CCrossBow::GetCollisionRect(void)
{
	RectD rectCollision;
	if(ANM_ATK_UP == GetCurrentAnimation())
	{
		if(m_fSlashTimer < 0.5f)
		{
			rectCollision.left = -2;
			rectCollision.top = -2;
			rectCollision.right = 2;
			rectCollision.bottom = 2;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -24;
				rectCollision.top = -500;
				rectCollision.right = 24;
				rectCollision.bottom = 500;
			}
		}
		else
		{
			SetAttacking(false);
			m_fSlashTimer = 0.0f;
			CPlayer::GetInstance()->m_bPhilSpecialAttack = false;
		}
	}
	else if(ANM_ATK_DOWN == GetCurrentAnimation())
	{
		if(m_fSlashTimer < 0.5f)
		{
			rectCollision.left = -2;
			rectCollision.top = -2;
			rectCollision.right = 2;
			rectCollision.bottom = 2;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -24;
				rectCollision.top = -500;
				rectCollision.right = 24;
				rectCollision.bottom = 500;
			}
		}
		else
		{
			SetAttacking(false);
			m_fSlashTimer = 0.0f;
			CPlayer::GetInstance()->m_bPhilSpecialAttack = false;
		}
	}
	else if(ANM_ATK_LEFT == GetCurrentAnimation())
	{
		if(m_fSlashTimer < 0.5f)
		{
			rectCollision.left = -2;
			rectCollision.top = -2;
			rectCollision.right = 2;
			rectCollision.bottom = 2;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -500;
				rectCollision.top = -24;
				rectCollision.right = 500;
				rectCollision.bottom = 24;
			}
		}
		else
		{
			SetAttacking(false);
			m_fSlashTimer = 0.0f;
			CPlayer::GetInstance()->m_bPhilSpecialAttack = false;
		}
	}
	else if(ANM_ATK_RIGHT == GetCurrentAnimation())
	{
		if(m_fSlashTimer < 0.5f)
		{
			rectCollision.left = -2;
			rectCollision.top = -2;
			rectCollision.right = 2;
			rectCollision.bottom = 2;
			if(CPlayer::GetInstance()->m_bPhilSpecialAttack)
			{
				rectCollision.left = -500;
				rectCollision.top = -24;
				rectCollision.right = 500;
				rectCollision.bottom = 24;
			}
		}
		else
		{
			SetAttacking(false);
			m_fSlashTimer = 0.0f;
			CPlayer::GetInstance()->m_bPhilSpecialAttack = false;
		}
	}
	return rectCollision;
}

void CCrossBow::ShootArrow(void)
{
	m_pArrow = new CArrow();
	m_pArrow->SetSpeed(580);
	m_pArrow->SetImageID(m_imgArrow);
	m_pArrow->SetHeight(128);
	m_pArrow->SetWidth(32);
	m_pArrow->Activate();
	CObjectManager::GetInstance()->AddObject(m_pArrow);
	PointD temp = CPlayer::GetInstance()->GetPosition();
	if(GetCurrentAnimation() == ANM_ATK_UP)
	{
		m_pArrow->SetVelX(0.0f);
		m_pArrow->SetVelY(-1.0f *m_pArrow->GetSpeed());
		m_pArrow->SetPosX(temp.x - 11 - 16);
		m_pArrow->SetPosY(temp.y - 67 - 64);
	}
	else if(GetCurrentAnimation() == ANM_ATK_DOWN)
	{
		m_pArrow->SetVelX(0.0f);
		m_pArrow->SetVelY(1.0f * m_pArrow->GetSpeed());
		m_pArrow->SetPosX(temp.x + 12 - 16);
		m_pArrow->SetPosY(temp.y - 20 - 64);
	}
	else if(GetCurrentAnimation() == ANM_ATK_LEFT)
	{
		m_pArrow->SetVelX(-1.0f *(int)m_pArrow->GetSpeed());
		m_pArrow->SetVelY(0.0f);
		m_pArrow->SetPosX(temp.x - 44 - 64);
		m_pArrow->SetPosY(temp.y - 48 - 64);
	}
	else if(GetCurrentAnimation() == ANM_ATK_RIGHT)
	{
		m_pArrow->SetVelX(1.0f *m_pArrow->GetSpeed());
		m_pArrow->SetVelY(0.0f);
		m_pArrow->SetPosX(temp.x + 43 - 64);
		m_pArrow->SetPosY(temp.y - 51 - 64);
	}
} 