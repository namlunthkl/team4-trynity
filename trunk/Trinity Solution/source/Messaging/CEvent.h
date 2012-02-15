////////////////////////////////////////////////////////////////////////
//    File Name				:	"CEvent.h"
//
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
	void*		m_pParam;
	string		m_szEventID;

public:
	CEvent(string szEventID, void* pParam)
	{
		m_szEventID = szEventID;
		m_pParam  = pParam;
	}

	~CEvent() {}
};

#endif // CEVENT_H_