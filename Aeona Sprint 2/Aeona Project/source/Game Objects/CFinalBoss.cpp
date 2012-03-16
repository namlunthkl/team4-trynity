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
}
CFinalBoss::~CFinalBoss()
{

}
void CFinalBoss::SufferDamage(unsigned int uiDamage)
{
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