////////////////////////////////////////////////////////////////////////
//    File Name				:	"CCrossBow.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the CCrossBow
//
//    Last Updater Name		:   Bryan Schotanes
//    Last Update Date      :   
//    Last Update Notes     :   
//								
//								
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CCROSSBOW_H_
#define CCROSSBOW_H_

#include "IBaseWeapon.h"
class CCrossBow : public IBaseWeapon
{
private:

public:
	~CCrossBow(void) {}
	void Attack(void);
	void ChargedAttack(void);
	unsigned int GetWeaponType(void) const { return TYPE_WEAPON_CROSSBOW; }
	void SetWeaponRotation(float fWeaponRotation);
};

#endif