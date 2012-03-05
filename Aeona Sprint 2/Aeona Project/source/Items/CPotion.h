////////////////////////////////////////////////////////////////////////
//    File Name				:	"CPotion.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the CPotion
//
//    Last Updater Name		:   Bryan Schotanes
//    Last Update Date      :   
//    Last Update Notes     :   
//								
//								
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CPOTION_H_
#define CPOTION_H_

#include "IBaseItem.h"
class CPotion : public IBaseItem
{
private:

public:
	~CPotion(void) {}
	CPotion();
	int Heal(void);
	unsigned int GetWeaponType(void) const { return TYPE_ITEM_POTION; }
};

#endif