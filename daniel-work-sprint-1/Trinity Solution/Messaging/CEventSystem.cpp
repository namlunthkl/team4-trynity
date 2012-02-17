////////////////////////////////////////////////////////////////////////
//    File Name				:	"CEventSystem.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09 - 03:09 AM
//    Purpose				:	Class that handles the Event System
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "CEventSystem.h"

void CEventSystem::DispatchEvent(CEvent* pEvent)
{
}


CEventSystem* CEventSystem::GetInstance(void)
{
	static CEventSystem pInstance;
	return &pInstance;
}

void CEventSystem::RegisterForEvent(string szEventID, IListener* pClient)
{

}

void CEventSystem::UnregisterFromEvent(string szEventID, IListener* pClient)
{

}

void CEventSystem::UnregisterEveryone(IListener* pClient)
{

}

void CEventSystem::SendEvent(string szEventID, void* pData)
{

}

void CEventSystem::ProcessEvents(void)
{

}

void CEventSystem::ClearEvents(void)
{

}

void CEventSystem::ShutdownEventSystem(void)
{
}