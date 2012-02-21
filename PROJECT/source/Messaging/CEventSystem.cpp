////////////////////////////////////////////////////////////////////////
//    File Name				:	"CEventSystem.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09 - 03:09 AM
//    Purpose				:	Class that handles the Event System
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "CEventSystem.h"

void CEventSystem::RegisterForEvent(string szEventID, IListener* pClient)
{
	//	Error check to make sure the client exists and hasn't been registered already
	if(!pClient || AlreadyRegistered(szEventID, pClient))
	{
		return;
	}

	//	Register (build) the database of clients
	m_mapClients.insert(make_pair(szEventID, pClient));
}

void CEventSystem::UnregisterFromEvent(string szEventID, IListener* pClient)
{
	//	Iterate all clients that are listening for this event
	pair<multimap<string, IListener*>::iterator, multimap<string, IListener*>::iterator> range;

	//	Find all of the clients that are able to receive this event
	range = m_mapClients.equal_range(szEventID);

	//	Go through the list of clients that are able to receive this event
	for(multimap<string, IListener*>::iterator mmIter = range.first; mmIter != range.second; ++mmIter)
	{
		//	Check if the pointer is equal to the client
		if((*mmIter).second == pClient)
		{
			//	Remove the client from the list
			mmIter = m_mapClients.erase(mmIter);
			break;
		}
	}
}

void CEventSystem::UnregisterEveryone(IListener* pClient)
{
	multimap<string, IListener*>::iterator mmIter = m_mapClients.begin();

	while(mmIter != m_mapClients.end())
	{
		if((*mmIter).second == pClient)
		{
			mmIter = m_mapClients.erase(mmIter);
		}
		else
		{
			++mmIter;
		}
	}
}

void CEventSystem::DispatchEvent(CEvent* pEvent)
{
	//	Iterate all clients that are listening for this event
	pair<multimap<string, IListener*>::iterator, multimap<string, IListener*>::iterator> range;

	//	Find all clients that are able to receive this event
	range = m_mapClients.equal_range(pEvent->GetEventID());

	//	Go through the linked list of clients that are able to receive this event
	for(multimap<string, IListener*>::iterator mmIter = range.first; mmIter != range.second; ++mmIter)
	{
		//	Pass event to the client
		(*mmIter).second->HandleEvent(pEvent);
	}
}

bool CEventSystem::AlreadyRegistered(string szEventID, IListener* pClient)
{
	bool bIsAlreadyRegistered = false;

	//	Iterate all clients that are listening for this event
	pair<multimap<string, IListener*>::iterator, multimap<string, IListener*>::iterator> range;

	//	Find all clients that are able to receive this event
	range = m_mapClients.equal_range(szEventID);

	//	Go through the list of clients that are able to receive this event
	for(multimap<string, IListener*>::iterator mmIter = range.first; mmIter != range.second; ++mmIter)
	{
		//	Check if the pointer is equal to the client
		if((*mmIter).second == pClient)
		{
			bIsAlreadyRegistered = true;
			break;
		}
	}
	return bIsAlreadyRegistered;
}

void CEventSystem::SendEvent(string szEventID, void* pData)
{
	//	Push the event into the list
	CEvent newEvent(szEventID, pData);

	m_listEvents.push_back(newEvent);
}

void CEventSystem::ProcessEvents(void)
{
	//	Go through my list of events that are waiting to be processed
	while(m_listEvents.size())
	{
		DispatchEvent(&m_listEvents.front());
		m_listEvents.pop_front();
	}
}

void CEventSystem::ClearEvents(void)
{
	m_listEvents.clear();
}

void CEventSystem::ShutdownEventSystem(void)
{
	m_mapClients.clear();
}