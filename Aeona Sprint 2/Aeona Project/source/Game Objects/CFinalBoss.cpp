////////////////////////////////////////////////////////////////////////
//    File Name				:	"CFinalBoss.cpp"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/09/12 - 4:24 AM
//    Purpose				:	THIS IS A CLASS THAT CONTAINS 
//								A EPIC BOSS ENCOUNTER
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CFinalBoss.h"
#include "../Game Objects/CPlayer.h"
#include "../AI_States/CBossAirAI.h"
#include "../AI_States/CBossEarthAI.h"
#include "../AI_States/CBossFireAI.h"
#include "../AI_States/CBossDaggerAI.h"
CFinalBoss::CFinalBoss(double dPositionX, double dPositionY, unsigned int uiSpeed, int nImageID, unsigned int uiWidth, unsigned int uiHeight, bool bActive,
	unsigned int uiMaxHealth, unsigned int uiAttackDamage, float fRespawnTime) : CEnemy(dPositionX,dPositionY,uiSpeed,nImageID,uiWidth,uiHeight,bActive,uiMaxHealth,uiAttackDamage,fRespawnTime)
{
	m_nCurrentBossState = 0;
	m_fOuchTimer = 0.0f;
}
CFinalBoss::~CFinalBoss()
{

}
void CFinalBoss::SufferDamage(unsigned int uiDamage)
{
	AUDIO->SFXPlaySound( CGame::GetInstance()->m_sndFleshHit );
	if(m_uiMiniState > 1)	//	States 0 and 1 are "Ow+knockedback" and "I'm still hurting, ow", so don't allow him to take damage again while he's already hurt
	{
		philEnemyColor = D3DCOLOR_XRGB(255, 0, 0);	//	Send a red color, because he got hit
		SetMoveTimer( 0.0f );	//	Required for my ai thing
		m_uiMiniState = 0;		//	State 0 is "ouch+knockedback"

		if((m_nCurrentBossState == BOSS_FIRE && CPlayer::GetInstance()->GetCurrentWeapon() == CPlayer::WEAPON_SWORD )||
			(m_nCurrentBossState == BOSS_EARTH && CPlayer::GetInstance()->GetCurrentWeapon() == CPlayer::WEAPON_HAMMER) ||
			(m_nCurrentBossState == BOSS_WIND && CPlayer::GetInstance()->GetCurrentWeapon() == CPlayer::WEAPON_CROSSBOW) ||
			(m_nCurrentBossState == BOSS_DAGGER && CPlayer::GetInstance()->GetCurrentWeapon() == CPlayer::WEAPON_DAGGER))
		{
			if(uiDamage < GetCurHealth())
			{
				SetCurHealth(GetCurHealth() - uiDamage);
			}
			else
			{
				Die();
			}
		}
	}
}
void CFinalBoss::Die(void)
{
	if(m_nCurrentBossState == BOSS_FIRE)
	{
		ChangeAIState(CBossEarthAI::GetInstance());
		SetCurHealth(GetMaxHealth());
		m_nCurrentBossState++;
	}
	else if(m_nCurrentBossState == BOSS_EARTH)
	{
		ChangeAIState(CBossAirAI::GetInstance());
		SetCurHealth(GetMaxHealth());
		m_nCurrentBossState++;
	}
	else if(m_nCurrentBossState == BOSS_WIND)
	{
		ChangeAIState(CBossDaggerAI::GetInstance());
		SetCurHealth(GetMaxHealth());
		m_nCurrentBossState++;
	}
	else if(m_nCurrentBossState == BOSS_DAGGER)
		CEnemy::Die();
}
void CFinalBoss::Render()
{
	if(m_fOuchTimer == 0.0f )
	{
		if(m_nCurrentBossState == BOSS_FIRE)
		{
			CBaseObject::Render(D3DCOLOR_ARGB(255,255,0,0));
		}
		else if(m_nCurrentBossState == BOSS_EARTH)
		{
			CBaseObject::Render(D3DCOLOR_ARGB(255,0,255,0));
		}
		else if(m_nCurrentBossState == BOSS_WIND)
		{
			CBaseObject::Render(D3DCOLOR_ARGB(255,0,0,255));
		}
		else if(m_nCurrentBossState == BOSS_DAGGER)
			CBaseObject::Render();
	}
	else
	{
		CBaseObject::Render(D3DCOLOR_ARGB(155,255,0,0));
	}
	
}
void CFinalBoss::Update(float fElapsedTime)
{
	if(m_fOuchTimer > 0.0f)
		m_fOuchTimer -= fElapsedTime;
	if( m_fOuchTimer < 0.0f )
		m_fOuchTimer = 0.0f;
	CEnemy::Update(fElapsedTime);

}