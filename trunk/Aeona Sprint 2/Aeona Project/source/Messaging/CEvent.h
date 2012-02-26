////////////////////////////////////////////////////////////////////////
//    File Name				:	"CEvent.h"
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09 - 12:43 AM
//    Purpose				:	Class that handles the behavior and
//								data of an event
////////////////////////////////////////////////////////////////////////

#ifndef CEVENT_H_
#define CEVENT_H_

#include <string>
using std::string;

class CEvent
{
private:
	string		m_szEventID;	//	The event's ID
	void*		m_pParam;		//	The value sent with the event

public:
	CEvent(string szEventID, void* pParam = NULL)
	{
		m_szEventID = szEventID;
		m_pParam  = pParam;
	}

	~CEvent() {}

	//	Accessors
	inline string GetEventID(void)	{ return m_szEventID; }
	inline void* GetParam(void)		{ return m_pParam; }
};

#endif // CEVENT_H_