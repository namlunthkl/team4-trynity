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
#include "../Items/CPotion.h"

#define WEAPON m_vGameWeapons[m_uiCurrentWeapon]

class CPlayer : public CBaseCharacter
{
public:
	// PHIL'S HACKS... tee-hee-hee!
	Byte			m_byteWeapons;
	Byte			m_byteMasks;
	unsigned int	m_uiCurrentWeapon;
	unsigned int	m_uiCurrentMask;
	unsigned int	m_uiNumPotions;
	bool			m_bPhilCharging;
	bool			m_bPhilSpecialAttack;
	float			m_fPhilChargeIdkman;
	bool			m_bHasFlower;
	unsigned int	m_uiGems;
	float			m_fOuchTimer;
	int				m_imgCharges;	//	the images of the charged attacks.
	float			m_fBlastTimer;

private:
	bool			m_bHeartPiece;
	vector<IBaseWeapon *>	m_vGameWeapons;
	int				m_sndPlayerMovement;

	// PARTICLE WEAPONS
	ParticleWeapon	m_fxElementalWeapon;

	RectD			m_weaponRect;
	Sound*			m_sndPotion;
	Sound*			m_sndSwitchAmulet;
	Sound*			m_sndSwitchWeapon;
	CPotion*		m_Potion;
	int				m_sndHit;
	bool			m_bDamageDecrease;
	int				m_nDamageIncrease;
	float			m_fSpeedIncrease;

	// Bool to indicate if the player is busy
	// talking with an NPC or doing something that
	// would not allow him to attack or move
	bool m_bBusy;


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

	void Reset(void);

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
	void AcquireWeapon(unsigned int uiWeaponType);
	// Set bit of a mask on
	void AcquireAmulet(unsigned int uiMaskType);
	// Set bool for heart piece on or increase health
	void AcquireHeartPiece(void);

	void SufferDamage(unsigned int uiDamage);

	// Check Collision against a specific object
	bool CheckCollision(IBaseInterface* pObject);
	// Check Collision agains the world
	bool CheckWorldCollision(void);
	
	RectD GetWeaponRect(void);
	// Destructor
	~CPlayer(void);

	const char* GetRegion(void) const;

	inline bool HasHeartPiece(void) { return m_bHeartPiece; }

	inline void AcquirePotion(void) { m_uiNumPotions++; }
	inline unsigned int GetNumPotions(void) { return m_uiNumPotions; }
	inline void AcquireGem(void) { m_uiGems++; }
	void UsePotion(void);

	// Return Point used for talking with NPCs and opening chests
	PointD GetInteractivePoint(void);
	RectD GetInteractiveRect(void);	// Better for chests

	// Accessors
	inline bool IsBusy(void) const { return m_bBusy; }
	inline bool Lock(void)
	{
		if(!m_bBusy)
		{
			m_bBusy = true;
			StopAttacking();
			return true;
		}
		return false;
	}

	inline void StopAttacking(void)
	{
		m_bPhilCharging = false;
		m_bPhilSpecialAttack = false;
		m_fPhilChargeIdkman = 0.0f;
		WEAPON->SetAttacking(false);
		WEAPON->GetAnimationPlayer(WEAPON->GetCurrentAnimation())->Pause();
	}

	inline void Unlock(void) { if(m_bBusy) m_bBusy = false; }

	Byte GetWeaponsByte(void) { return m_byteWeapons; }
	Byte GetAmuletsByte(void) { return m_byteMasks; }
	inline unsigned int GetCurrentWeapon(void) const { return m_uiCurrentWeapon; }
	inline unsigned int GetCurrentAmulet(void) const { return m_uiCurrentMask; }
	inline float GetOuchTimer(void) const { return m_fOuchTimer; }
	inline void SetOuchTimer(float fOuchTimer) { m_fOuchTimer = fOuchTimer; }
	inline void AcquireFlower(void) { m_bHasFlower = true; }
	inline bool HasFlower(void) { return m_bHasFlower; }
};

#endif // C_PLAYER_H_