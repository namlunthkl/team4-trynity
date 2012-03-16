////////////////////////////////////////////////////////////////////////
//    File Name				:	"CBoulder.h"
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
#ifndef CBOULDER_H_
#define CBOULDER_H_

#include "../Game Objects/CBaseObject.h"
class CBoulder : public CBaseObject
{
private:
	float timeout;
public:
	CBoulder();
	void Render(void);
	bool CheckCollision(IBaseInterface* pObject);
	void Update(float fElapsedTime);
	unsigned int GetType(void) const { return IBaseInterface::TYPE_WEAPON_BOULDER; }
protected:
};
#endif