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

class CEventSystem
{
	private:
		multimap<string, IListener*> m_mapClients;
		list<CEvent> m_listEvents;

		void DispatchEvent(CEvent* pEvent);

		// Proper singleton - needs trilogy
		CEventSystem() {}
		CEventSystem(const CEventSystem&);
		CEventSystem& operator=(const CEventSystem&);
		~CEventSystem() {}

	public:

		static CEventSystem* GetInstance(void);
		void RegisterForEvent(string szEventID, IListener* pClient);
		void UnregisterFromEvent(string szEventID, IListener* pClient);
		void UnregisterEveryone(IListener* pClient);
		void SendEvent(string szEventID, void* pData);
		void ProcessEvents(void);
		void ClearEvents(void);
		void ShutdownEventSystem(void);
};

#endif // CEVENTSYSTEM_H_