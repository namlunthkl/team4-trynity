////////////////////////////////////////////////////////////////////////
//    File Name				:	"CBaseCharacter.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/26 - 9:10 PM
//    Purpose				:	Class that inherits from CBaseObject and
//								contains all the functionality that is
//								common to all game characters
////////////////////////////////////////////////////////////////////////

// Standard Header Protection
#ifndef C_BASE_CHARACTER_H_
#define C_BASE_CHARACTER_H_

// Include parent class
#include "CBaseObject.h"

// For Artificial Intelligence
#include "../AI_States/IBaseAIState.h"

// CBaseCharacter
// All game characters will inherit from this class
class CBaseCharacter : public CBaseObject
{
	// Every character needs health
	unsigned int	m_uiMaxHealth;
	unsigned int	m_uiCurHealth;

	// Every character needs a base attack damage
	unsigned int	m_uiAttackDamage;

	// Every character needs an AI State
	IBaseAIState*	m_pAIState;

protected:
	// Enum for animations
	enum Animations { ANM_WALK_UP, ANM_WALK_DOWN, ANM_WALK_RIGHT, ANM_WALK_LEFT,
		ANM_ATTACK, ANM_DIE, ANM_MAX };

public:
	// Constructor
	CBaseCharacter(long lPositionX = 0, long lPositionY = 0, unsigned int uiSpeed = 0U,
		int nImageID = -1, unsigned int uiWidth = 0U, unsigned int uiHeight = 0, bool bActive = false,
		unsigned int uiMaxHealth = 0, unsigned int uiAttackDamage = 0);

	// Common routines
	bool LoadAnimations(char const * const szFilename);
	virtual void Update(float fElapsedTime);
	virtual void Attack(CBaseCharacter* pTarget);
	virtual void Die(void);
	virtual void ChangeAIState(IBaseAIState* pAIState);

	virtual inline unsigned int GetType(void) const { return TYPE_BASE_CHARACTER; }

	void SufferDamage(unsigned int uiDamage);
	void Heal(unsigned int uiHealAmount);

	// Destructor
	~CBaseCharacter(void);
};

#endif // C_BASE_CHARACTER_H_