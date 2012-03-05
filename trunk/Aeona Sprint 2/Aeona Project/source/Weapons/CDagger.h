////////////////////////////////////////////////////////////////////////
//    File Name				:	"CDagger.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the CDagger
//
//    Last Updater Name		:   Bryan Schotanes
//    Last Update Date      :   
//    Last Update Notes     :   
//								
//								
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CDAGGER_H_
#define CDAGGER_H_

#include "IBaseWeapon.h"
class CDagger : public IBaseWeapon
{
private:

public:
	CDagger();
	~CDagger(void) {}
	void Attack(void);
	void ChargedAttack(void);
	void Update(float fElapsedTime);
	void Render(PointD nPosition);
	unsigned int GetWeaponType(void) const { return TYPE_WEAPON_DAGGER; }
	//void SetWeaponRotation(float fWeaponRotation);
	RectD GetCollisionRect(void);
};

#endif