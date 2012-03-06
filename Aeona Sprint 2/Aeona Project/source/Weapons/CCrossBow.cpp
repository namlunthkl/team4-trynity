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
	CBaseCharacter::LoadAnimations("resource/PlayerWCrossBow.xml");
	SetAttacking(false);
	m_pArrow = NULL;
}
void CCrossBow::Render(PointD nPos)
{
	SetPosX(nPos.x);
	SetPosY(nPos.y);

	CBaseCharacter::Render();
}

void CCrossBow::Update(float fElapsedTime)
{
	CBaseCharacter::Update(fElapsedTime);

}
void CCrossBow::Attack(void)
{
	SetAttacking(true);
	//if(m_pArrow == NULL)
		ShootArrow();
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
	m_pArrow->SetSpeed(40);
	m_pArrow->SetImageID(TEX_MNG->LoadTexture("resource/BrS_Arrow.png", D3DCOLOR_XRGB(255,255,255)));
	m_pArrow->SetHeight(18);
	m_pArrow->SetWidth(4);
	m_pArrow->Activate();
	CObjectManager::GetInstance()->AddObject(m_pArrow);
	PointD temp = CPlayer::GetInstance()->GetPosition();
	if(GetCurrentAnimation() == ANM_ATK_UP)
	{
		m_pArrow->SetVelX(0*m_pArrow->GetSpeed());
		m_pArrow->SetVelY(-1*(int)m_pArrow->GetSpeed());
		m_pArrow->SetPosX(temp.x);
		m_pArrow->SetPosY(temp.y- 20);
	}
	else if(GetCurrentAnimation() == ANM_ATK_DOWN)
	{
		m_pArrow->SetVelX(0*m_pArrow->GetSpeed());
		m_pArrow->SetVelY(1*m_pArrow->GetSpeed());
		m_pArrow->SetPosX(temp.x);
		m_pArrow->SetPosY(temp.y + 20);
	}
	else if(GetCurrentAnimation() == ANM_ATK_LEFT)
	{
		m_pArrow->SetVelX(-1*(int)m_pArrow->GetSpeed());
		m_pArrow->SetVelY(0*m_pArrow->GetSpeed());
		m_pArrow->SetPosX(temp.x - 20);
		m_pArrow->SetPosY(temp.y);
	}
	else if(GetCurrentAnimation() == ANM_ATK_RIGHT)
	{
		m_pArrow->SetVelX(1*m_pArrow->GetSpeed());
		m_pArrow->SetVelY(0*m_pArrow->GetSpeed());
		m_pArrow->SetPosX(temp.x + 20);
		m_pArrow->SetPosY(temp.y);
	}
} 