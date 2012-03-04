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
#include "../Weapons/IBaseWeapon.h"

class CPlayer : public CBaseCharacter
{
	Byte			m_byteWeapons;
	Byte			m_byteMasks;
	bool			m_bHeartPiece;
	unsigned int	m_uiCurrentWeapon;
	unsigned int	m_uiCurrentMask;
	vector<IBaseWeapon *>	m_vGameWeapons;
	int				m_sndPlayerMovement;
	ParticleWeapon	m_fxFootsteps;

	// Singleton needs trilogy
	CPlayer(const CPlayer&){}
	CPlayer* operator=(const CPlayer&){}
	// Constructor
	CPlayer(void);

public:
	enum EWeapons { WEAPON_DAGGER, WEAPON_SWORD, WEAPON_HAMMER, WEAPON_CROSSBOW, WEAPON_MAX };
	enum EMasks { MASK_NONE, MASK_SPEED, MASK_ENDURANCE, MASK_STRENGHT, MASK_LIGHT, MASK_MAX };

	// Singleton's accessor
	static CPlayer* GetInstance(void);

	// Common routines - Overloaded methods
	void Update(float fElapsedTime);
	void Render(void);
	void Attack(void);
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

	RectD GetCollisionRect(void)
	{
		return m_vGameWeapons[m_uiCurrentWeapon]->GetCollisionRect();
	}
	bool CheckCollision(IBaseInterface* pObject);
	// Destructor
	~CPlayer(void);

	const char* GetRegion(void) const;

	inline bool HasHeartPiece(void) { return m_bHeartPiece; }
};

#endif // C_PLAYER_H_