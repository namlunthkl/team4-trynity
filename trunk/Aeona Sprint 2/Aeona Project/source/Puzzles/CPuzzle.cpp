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

CPuzzle::CPuzzle(void)
{
	m_pParticle = nullptr;
	m_uiArgCount = 0;
}

void CPuzzle::HandleEvent(CEvent* pEvent)
{
	// Call this puzzle's specific handle event
	m_pfHandleEvent(pEvent, this);
}

void CPuzzle::Update(float fElapsedTime)
{
	// Call this puzzle's specific update
	m_pfUpdate(this);
}

void CPuzzle::Initialize(unsigned int uiArgCount, char* szEvent, vector<char*> m_szEventsToListen,
	void(*pfHandleEvent)(CEvent*, CPuzzle*), void(*pfUpdate)(CPuzzle*))
{
	m_uiArgCount = uiArgCount;
	m_szEvent = szEvent;
	m_pfHandleEvent = pfHandleEvent;
	m_pfUpdate = pfUpdate;

	for(unsigned int i=0; i < m_szEventsToListen.size(); ++i)
		CEventSystem::GetInstance()->RegisterForEvent(m_szEventsToListen[i], this);
}