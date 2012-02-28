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
class IBaseAIState;

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

	// Used by AI States
	float			m_fMoveTimer;

public:
	// Enum for animations
	enum EAnimations { ANM_WALK_UP, ANM_WALK_DOWN, ANM_WALK_RIGHT, ANM_WALK_LEFT,
		ANM_ATTACK, ANM_DIE, ANM_MAX };

	// Constructor
	CBaseCharacter(double dPositionX = 0, double dPositionY = 0, unsigned int uiSpeed = 0U,
		int nImageID = -1, unsigned int uiWidth = 0U, unsigned int uiHeight = 0U, bool bActive = false,
		unsigned int uiMaxHealth = 0, unsigned int uiAttackDamage = 0);

	// Common routines
	bool LoadAnimations(char const * const szFilename);
	virtual void Update(float fElapsedTime);
	virtual void Attack(CBaseCharacter* pTarget);
	virtual void Die(void);
	virtual void ChangeAIState(IBaseAIState* pAIState);

	virtual inline unsigned int GetType(void) const { return TYPE_CHAR_BASE; }

	inline unsigned int GetMaxHealth(void)	{ return m_uiMaxHealth; }
	inline unsigned int GetCurHealth(void)	{ return m_uiCurHealth; }

	void SufferDamage(unsigned int uiDamage);
	void Heal(unsigned int uiHealAmount);

	// Destructor
	~CBaseCharacter(void);


	inline void GainHeart(void) { m_uiMaxHealth++; }
	
	inline float GetMoveTimer(void) const { return m_fMoveTimer; }
	inline void SetMoveTimer(float fMoveTimer) { m_fMoveTimer = fMoveTimer; }
};

#endif // C_BASE_CHARACTER_H_