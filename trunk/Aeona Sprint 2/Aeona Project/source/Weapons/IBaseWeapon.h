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
#ifndef I_BASE_WEAPON_H_
#define I_BASE_WEAPON_H_


#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class IBaseWeapon
{
public:
	enum WeaponType { TYPE_WEAPON_BASE = 0, TYPE_WEAPON_DAGGER, TYPE_WEAPON_SWORD, TYPE_WEAPON_HAMMER, TYPE_WEAPON_CROSSBOW, TYPE_MAX };

	// Destructor
	virtual ~IBaseWeapon(void) = 0 {}


	//virtual void Update(float fElapsedTime) = 0;
	//virtual void Render(void) = 0;
	//virtual void Input(void) = 0;

	virtual unsigned int GetWeaponType(void) const = 0;
	virtual void SetWeaponRotation(float fWeaponRotation) = 0;
};

#endif