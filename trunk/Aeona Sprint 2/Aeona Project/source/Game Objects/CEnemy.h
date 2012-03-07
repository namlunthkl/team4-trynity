////////////////////////////////////////////////////////////////////////
//    File Name				:	"CEnemy.h"
//
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 4:17 AM
//    Purpose				:	Enemy character class
////////////////////////////////////////////////////////////////////////

#ifndef C_ENEMY_H_
#define C_ENEMY_H_

#include "CBaseCharacter.h"
#include "../AI_States/IBaseAIState.h"

class CEnemy : public CBaseCharacter
{
public:
	// Constructor
	CEnemy(double dPositionX = 0, double dPositionY = 0, unsigned int uiSpeed = 0U,
		int nImageID = -1, unsigned int uiWidth = 0U, unsigned int uiHeight = 0U, bool bActive = false,
		unsigned int uiMaxHealth = 0, unsigned int uiAttackDamage = 0);

	~CEnemy(void);

	void Die(void);

	bool CEnemy::CheckCollision(IBaseInterface* pObject);

	inline unsigned int GetType(void) const { return TYPE_CHAR_ENEMY; }
};

#endif // C_ENEMY_H_