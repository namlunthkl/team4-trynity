////////////////////////////////////////////////////////////////////////
//    File Name				:	"IBaseWeapon.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the IBaseWeapon
//
//    Last Updater Name		:   Bryan Schotanes
//    Last Update Date      :   
//    Last Update Notes     :   
//								
//								
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef IBASEWEAPON_H_
#define IBASEWEAPON_H_


#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "../Game Objects/CBaseObject.h"
class IBaseWeapon : public CBaseObject
{
private:
	string m_szEvent;
	float m_frotation;
	Point m_weaponAnchor;
	
	int m_nDamage;

public:
	enum WeaponType { TYPE_WEAPON_BASE = 0, TYPE_WEAPON_DAGGER, TYPE_WEAPON_SWORD, TYPE_WEAPON_HAMMER, TYPE_WEAPON_CROSSBOW, TYPE_MAX };

	virtual void Attack(void) = 0;
	virtual void ChargedAttack(void) = 0;

	virtual unsigned int GetWeaponType(void) const = 0;
	virtual void SetWeaponRotation(float fWeaponRotation) = 0;
	float GetRotation() const { return m_frotation; }
	void SetRotation(float val) { m_frotation = val; }
	Point GetWeaponAnchor() const { return m_weaponAnchor; }
	void SetWeaponAnchor(Point val) { m_weaponAnchor = val; }
};

#endif