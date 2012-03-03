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
	CCrossBow();
	~CCrossBow(void) {}
	void Attack(void);
	void ChargedAttack(void);
	void Update(float fElapsedTime);
	void Render(PointD nPosition);
	unsigned int GetWeaponType(void) const { return TYPE_WEAPON_CROSSBOW; }
	//void SetWeaponRotation(float fWeaponRotation);
};

#endif