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
CFinalBoss::CFinalBoss(double dPositionX, double dPositionY, unsigned int uiSpeed, int nImageID, unsigned int uiWidth, unsigned int uiHeight, bool bActive,
	unsigned int uiMaxHealth, unsigned int uiAttackDamage, float fRespawnTime) : CEnemy(dPositionX,dPositionY,uiSpeed,nImageID,uiWidth,uiHeight,bActive,uiMaxHealth,uiAttackDamage,fRespawnTime)
{

}
CFinalBoss::~CFinalBoss()
{

}
void CFinalBoss::Die(void)
{
	if(m_nCurrentBossState == BOSS_DAGGER)
		CEnemy::Die();
	else
		m_nCurrentBossState++;
}