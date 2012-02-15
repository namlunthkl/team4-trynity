////////////////////////////////////////////////////////////////////////
//    File Name				:	"CPuzzle.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09 - 12:50 AM
//    Purpose				:	Puzzle class used for puzzle behavior
//								handling
////////////////////////////////////////////////////////////////////////

// Precompiled header
#include "StdAfx.h"

#include "CPuzzle.h"

void CPuzzle::HandleEvent(CEvent* pEvent)
{
	// If it is the event we're listening to...
	/*if(pEvent->GetEventID() == m_szEvent)
	{
		// Call this puzzle's specific handle event
		m_pfHandleEvent();
	}
	*/
}

void CPuzzle::Update(float fElapsedTime)
{
	// Call this puzzle's specific update
	m_pfUpdate();
}

void CPuzzle::Initialize(unsigned int uiArgCount, char* szEvent,
	void(*pfHandleEvent)(void), void(*pfUpdate)(void))
{
	m_uiArgCount = uiArgCount;
	m_szEvent = szEvent;
	m_pfHandleEvent = pfHandleEvent;
	m_pfUpdate = pfUpdate;

	// EventSystem->RegisterClient(m_szEvent, this);
}