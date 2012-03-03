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

	for(unsigned int i=0; i < m_vParticle.size(); ++i)
			m_vParticle[i]->Update(fElapsedTime);
}

void CPuzzle::Initialize(unsigned int uiArgCount, char* szEvent, vector<char*> m_szEventsToListen,
	void(*pfHandleEvent)(CEvent*, CPuzzle*), void(*pfUpdate)(CPuzzle*), char const * const szParticleFile)
{
	m_uiArgCount = uiArgCount;
	m_szEvent = szEvent;
	m_pfHandleEvent = pfHandleEvent;
	m_pfUpdate = pfUpdate;

	for(unsigned int i=0; i < m_szEventsToListen.size(); ++i)
		CEventSystem::GetInstance()->RegisterForEvent(m_szEventsToListen[i], this);

	for(unsigned int i=0; i < uiArgCount; ++i)
		m_vnArguments.push_back(0);

	for(unsigned int i=0; i < uiArgCount; ++i)
	{
		ParticleWeapon* p = new ParticleWeapon();
		p->Load(szParticleFile);
		m_vParticle.push_back(p);
	}
}

void CPuzzle::Render(void)
{
	for(unsigned int i=0; i < m_vParticle.size(); ++i)
			m_vParticle[i]->Render();
}