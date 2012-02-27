////////////////////////////////////////////////////////////////////////
//    File Name				:	"CPlayer.h"
//
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 3:34 AM
//    Purpose				:	Game player character class
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef C_PLAYER_H_
#define C_PLAYER_H_

// Include parent class
#include "CBaseCharacter.h"

#include "../Particle Engine/ParticleWeapon.h"

// TODO: When weapon class is done, replace this forward
// declaration by actually including the weapon
class CWeapon
{
	int a;
};

class CPlayer : public CBaseCharacter
{
	Byte			m_byteWeapons;
	Byte			m_byteMasks;
	bool			m_bHeartPiece;
	unsigned int	m_uiCurrentWeapon;
	unsigned int	m_uiCurrentMask;
	vector<CWeapon>	m_vGameWeapons;
	int				m_sndPlayerMovement;
	ParticleWeapon	m_footsteps;


	// Singleton needs trilogy
	CPlayer(const CPlayer&){}
	CPlayer* operator=(const CPlayer&){}
	// Constructor
	CPlayer(void);

public:
	enum EWeapons { WEAPON_DAGGER, WEAPON_BLADE, WEAPON_HAMMER, WEAPON_CROSSBOW, WEAPON_MAX };
	enum EMasks { MASK_NONE, MASK_SPEED, MASK_ENDURANCE, MASK_STRENGHT, MASK_LIGHT, MASK_MAX };

	// Singleton's accessor
	static CPlayer* GetInstance(void);

	// Common routines - Overloaded methods
	void Update(float fElapsedTime);
	void Attack(CBaseCharacter* pTarget);
	void ChargedAttack(void);
	void Die(void);
	unsigned int GetType(void) const { return TYPE_CHAR_PLAYER; }

	// Get input for the player
	void Input(void);
	// Cycle through the weapons
	void CycleWeapon(void);
	// Cycle through the masks
	void CycleMask(void);
	// Set the bit for a weapon on
	void AquireWeapon(unsigned int uiWeaponType);
	// Set bit of a mask on
	void AquireMask(unsigned int uiMaskType);
	// Set bool for heart piece on or increase health
	void AquireHeartPiece(void);

	// Desturctor
	~CPlayer(void);


	inline bool HasHeartPiece(void) { return m_bHeartPiece; }
};

#endif // C_PLAYER_H_