////////////////////////////////////////////////////////////////////////
//    File Name				:	"IListener.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09 - 03:47 AM
//    Purpose				:	Class that every event listener should
//								inherit from
////////////////////////////////////////////////////////////////////////

#ifndef ILISTENER_H_
#define ILISTENER_H_

#include "CEvent.h"

class IListener
{
public:
	IListener(void) {}
	virtual ~IListener(void) {}
	virtual void HandleEvent(CEvent* pEvent) = 0;
};

#endif // ILISTENER_H_