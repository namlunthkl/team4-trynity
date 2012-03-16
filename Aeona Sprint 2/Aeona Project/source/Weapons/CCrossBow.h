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
#include "../Game Objects/CArrow.h"
class CCrossBow : public IBaseWeapon
{
private:
	CArrow* m_pArrow;
	float m_fTime;
	int m_imgArrow;
public:
	CCrossBow();
	~CCrossBow(void) {}
	void Attack(void);
	void ChargedAttack(void);
	void Update(float fElapsedTime);
	void Render(PointD nPosition);
	void Render(PointD nPos,DWORD WHICHCOLORYOUWANTHIMTOGLOWBRO);
	unsigned int GetWeaponType(void) const { return TYPE_WEAPON_CROSSBOW; }
	unsigned int GetType(void) const { return IBaseInterface::TYPE_WEAPON_ARROW; }
	void ShootArrow(void);
	RectD GetCollisionRect(void);
	//void SetWeaponRotation(float fWeaponRotation);
};

#endif