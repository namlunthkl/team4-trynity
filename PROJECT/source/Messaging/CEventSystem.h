////////////////////////////////////////////////////////////////////////
//    File Name				:	"CEventSystem.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09 - 03:09 AM
//    Purpose				:	Class that handles the Event System
////////////////////////////////////////////////////////////////////////

#ifndef CEVENTSYSTEM_H_
#define CEVENTSYSTEM_H_

#include "CEvent.h"
#include "IListener.h"

#include <list>
#include <map>
using std::multimap;
using std::pair;
using std::list;

class CEventSystem
{
	private:
		//	The database that contains clients that listen for events
		multimap<string, IListener*> m_mapClients;
		//	Events waiting to be processed
		list<CEvent> m_listEvents;

		void DispatchEvent(CEvent* pEvent);
		bool AlreadyRegistered(string eventID, IListener* pClient);

		// Constructor & Trilogy
		CEventSystem() {}
		CEventSystem(const CEventSystem&);
		CEventSystem& operator=(const CEventSystem&);
		~CEventSystem() {}

	public:
		static CEventSystem* GetInstance(void)
		{
			static CEventSystem instance;
			return &instance;
		}
		void RegisterForEvent(string szEventID, IListener* pClient);
		void UnregisterFromEvent(string szEventID, IListener* pClient);
		void UnregisterEveryone(IListener* pClient);
		void SendEvent(string szEventID, void* pData = NULL);
		void ProcessEvents(void);
		void ClearEvents(void);
		void ShutdownEventSystem(void);
};

#endif // CEVENTSYSTEM_H_