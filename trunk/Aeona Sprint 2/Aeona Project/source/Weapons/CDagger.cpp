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
	CBaseCharacter::LoadAnimations("resource/AeonaDagger.xml");
	SetAttacking(false);

	SetSound(new Sound("resource/sound/Dagger.wav"));

	m_fSlashTimer = 0.0f;
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
		m_fSlashTimer += fElapsedTime;
}
void CDagger::Attack(void)
{
	SetAttacking(true);
	if(m_fSlashTimer == 0.0f)
		GetSound()->Play();
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
		rectCollision.bottom = 15 + 68;
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
		rectCollision.left = -15 - 68;
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
		rectCollision.right = 15 + 68;
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