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
	m_fTime = 0;

	SetSound(new Sound("resource/sound/Bow.wav"));

	m_fSlashTimer = 0.0f;
}
void CCrossBow::Render(PointD nPos)
{
	SetPosX(nPos.x);
	SetPosY(nPos.y);

	CBaseCharacter::Render();
}

void CCrossBow::Update(float fElapsedTime)
{
	m_fTime += fElapsedTime;
	CBaseCharacter::Update(fElapsedTime);

}
void CCrossBow::Attack(void)
{
	if(m_fTime >= 0.5f)
	{
		SetAttacking(true);
		GetSound()->Play();
		m_fTime = 0;
		ShootArrow();
	}
}
void CCrossBow::ChargedAttack(void)
{

}
//RectD CCrossBow::GetCollisionRect(void)
//{
//	RectD rectCollision;
//	if(ANM_ATK_UP == GetCurrentAnimation())
//	{
//		rectCollision.left = -30;
//		rectCollision.top = -35;
//		rectCollision.right = 30;
//		rectCollision.bottom = -5;
//	}
//	else if(ANM_ATK_DOWN == GetCurrentAnimation())
//	{
//		rectCollision.left = -30;
//		rectCollision.top = 5;
//		rectCollision.right = 30;
//		rectCollision.bottom = 35;
//	}
//	else if(ANM_ATK_LEFT == GetCurrentAnimation())
//	{
//		rectCollision.left = -35;
//		rectCollision.top = -30;
//		rectCollision.right = -5;
//		rectCollision.bottom = 30;
//	}
//	else if(ANM_ATK_RIGHT == GetCurrentAnimation())
//	{
//		rectCollision.left = 5;
//		rectCollision.top = -30;
//		rectCollision.right = 35;
//		rectCollision.bottom = 30;
//	}
//	return rectCollision;
//}
void CCrossBow::ShootArrow(void)
{
	m_pArrow = new CArrow();
	m_pArrow->SetSpeed(580);
	m_pArrow->SetImageID(TEX_MNG->LoadTexture("resource/BlueArrow.png", D3DCOLOR_XRGB(0,0,0)));
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