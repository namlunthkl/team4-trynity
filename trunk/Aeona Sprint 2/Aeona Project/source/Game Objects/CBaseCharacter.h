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
		ANM_IDLE_UP,ANM_IDLE_DOWN,ANM_IDLE_RIGHT,ANM_IDLE_LEFT,
		ANM_ATK_UP,ANM_ATK_DOWN,ANM_ATK_RIGHT,ANM_ATK_LEFT,
		ANM_CHAR_UP,ANM_CHAR_DOWN,ANM_CHAR_RIGHT,ANM_CHAR_LEFT,
		ANM_MAX };


	// Constructor
	CBaseCharacter(double dPositionX = 0, double dPositionY = 0, unsigned int uiSpeed = 0U,
		int nImageID = -1, unsigned int uiWidth = 0U, unsigned int uiHeight = 0U, bool bActive = false,
		unsigned int uiMaxHealth = 0, unsigned int uiAttackDamage = 0);

	// Common routines
	bool LoadAnimations(char const * const szFilename);
	virtual void Update(float fElapsedTime);
	virtual void Attack(void);
	virtual void Die(void);
	virtual void ChangeAIState(IBaseAIState* pAIState);

	virtual inline unsigned int GetType(void) const { return TYPE_CHAR_BASE; }

	inline unsigned int GetMaxHealth(void)	{ return m_uiMaxHealth; }
	inline unsigned int GetCurHealth(void)	{ return m_uiCurHealth; }
	inline void SetMaxHealth(unsigned int m)	{ m_uiMaxHealth = m; }
	inline void SetCurHealth(unsigned int m)	{ m_uiCurHealth = m; }
	inline unsigned int GetAttackDamage(void) { return m_uiAttackDamage; }
	inline void SetAttackDamage(unsigned int uiDamage) { m_uiAttackDamage = uiDamage; }
	void SufferDamage(unsigned int uiDamage);
	void Heal(unsigned int uiHealAmount);

	// Destructor
	~CBaseCharacter(void);


	inline void GainHeart(void) { m_uiMaxHealth++; }
	inline float GetMoveTimer(void) const { return m_fMoveTimer; }
	inline void SetMoveTimer(float fMoveTimer) { m_fMoveTimer = fMoveTimer; }

	inline unsigned int GetMiniState(void)	{ return m_uiMiniState; }
	inline void SetMiniState(unsigned int m)	{ m_uiMiniState = m; }
	inline void SetBehavior(unsigned int m)		{ m_uiEnemyBehavior = m; }

	void SetPhilDirection(void);	//	Super cool direction check! 0 = left, 1 = up, 2 = right, 3 = down

	void Ressurect(void);

	//inline unsigned int GetPhilDirection(void)	{ return m_uiPhilDirection; }
};

#endif // C_BASE_CHARACTER_H_