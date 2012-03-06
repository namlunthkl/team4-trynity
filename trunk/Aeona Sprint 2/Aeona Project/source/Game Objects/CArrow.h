////////////////////////////////////////////////////////////////////////
//    File Name				:	"CArrow.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the Arrow
//
//    Last Updater Name		:   Bryan Schotanes
//    Last Update Date      :   
//    Last Update Notes     :   
//								
//								
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CARROW_H_
#define CARROW_H_

#include "../Game Objects/CBaseObject.h"
class CArrow : public CBaseObject
{
private:

public:
	CArrow();
	bool CheckCollision(IBaseInterface* pObject);
protected:
};
#endif