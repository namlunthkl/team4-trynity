////////////////////////////////////////////////////////////////////////
//    File Name				:	"CHammer.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the CHammer
//
//    Last Updater Name		:   Bryan Schotanes
//    Last Update Date      :   
//    Last Update Notes     :   
//								
//								
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CHAMMER_H_
#define CHAMMER_H_

#include "IBaseWeapon.h"
class CHammer : public IBaseWeapon
{
private:

public:
	~CHammer(void) {}
	void Attack(void);
	void ChargedAttack(void);
	unsigned int GetWeaponType(void) const { return TYPE_WEAPON_HAMMER; }
	void SetWeaponRotation(float fWeaponRotation);
};

#endif