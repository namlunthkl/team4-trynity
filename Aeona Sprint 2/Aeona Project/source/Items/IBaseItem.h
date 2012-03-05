////////////////////////////////////////////////////////////////////////
//    File Name				:	"IBaseItem.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the IBaseItem
//
//    Last Updater Name		:   Bryan Schotanes
//    Last Update Date      :   
//    Last Update Notes     :   
//								
//								
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef IBASEITEM_H_
#define IBASEITEM_H_


#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "../Game Objects/CBaseObject.h"
class IBaseItem : public CBaseObject
{
private:

public:
	enum ItemType { TYPE_ITEM_BASE = 0, TYPE_ITEM_POTION, TYPE_ITEM_MAX };

	virtual void Update(float fElapsedTime) = 0;
	virtual void Render(PointD nPosition) = 0;
	virtual unsigned int GetItemType(void) const = 0;
};

#endif