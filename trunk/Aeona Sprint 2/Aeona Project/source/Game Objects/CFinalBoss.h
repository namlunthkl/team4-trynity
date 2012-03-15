////////////////////////////////////////////////////////////////////////
//    File Name				:	"CFinalBoss.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/09/12 - 4:17 AM
//    Purpose				:	THIS IS A CLASS THAT CONTAINS 
//								A EPIC BOSS ENCOUNTER
////////////////////////////////////////////////////////////////////////
#ifndef CFINALBOSS_H_
#define CFINALBOSS_H_

#include "CEnemy.h"
#include "../AI_States/IBaseAIState.h"
class CFinalBoss : public CEnemy
{
	enum EBossState { BOSS_FIRE = 0 , BOSS_EARTH, BOSS_WIND, BOSS_DAGGER, BOSS_MAX };
private:
	int m_nCurrentBossState;
	vector<IBaseAIState*> m_BossAI;
public:
	CFinalBoss(double dPositionX = 0, double dPositionY = 0, unsigned int uiSpeed = 0U,
		int nImageID = -1, unsigned int uiWidth = 0U, unsigned int uiHeight = 0U, bool bActive = false,
		unsigned int uiMaxHealth = 0, unsigned int uiAttackDamage = 0, float fRespawnTime = 0.0f);

	~CFinalBoss(void);
	void Die(void);
	inline unsigned int GetType(void) const { return TYPE_CHAR_ENEMY; }
};
#endif