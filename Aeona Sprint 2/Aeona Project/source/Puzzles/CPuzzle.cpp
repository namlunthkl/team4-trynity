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



void IBasePuzzle::Create(unsigned int uiArgCount, char* szEventToFire, char* szEventToListenTo, bool bSequential)
{
	// Set the argument count
	m_uiArgCount = uiArgCount;
	m_szEventToFire = szEventToFire;
	m_szEventToListenTo = szEventToListenTo;
	m_bSequential = bSequential;

	// Initialize the arguments vector
	for(unsigned int i=0; i < m_uiArgCount; ++i)
		m_vnArguments.push_back(0);

	string szEventToRegister = szEventToListenTo;
	szEventToRegister += ".";
	// Register client for events
	for(char i = '0'; i < '0' + (int)uiArgCount; ++i)
		CEventSystem::GetInstance()->RegisterForEvent(szEventToRegister + i, this);

	m_dwTimeStamp = timeGetTime();
}

void IBasePuzzle::HandleEvent(CEvent* pEvent)
{
	if(timeGetTime() - m_dwTimeStamp < 250)
		return;

	unsigned int i;
	string EventName = "";
	int EventNumber = 0;

	// Get event name and number
	for(i = 0; i < pEvent->GetEventID().size(); ++i)
	{
		if(pEvent->GetEventID()[i] == '.')
			break;
		EventName += pEvent->GetEventID()[i];
	}
	EventNumber = atoi(pEvent->GetEventID().c_str() + (i+1));

	// Check if event name is the one we're listening to
	if(EventName == m_szEventToListenTo)
	{
		if(EventNumber < (int)m_uiArgCount)
			EventReceived(EventNumber, pEvent->GetParam());
	}

	TryFiringEvent();
	m_dwTimeStamp = timeGetTime();
}

void IBasePuzzle::EventReceived(int ArgumentNumber, void* EventData)
{
	if(m_vnArguments[ArgumentNumber] == 0)
		m_vnArguments[ArgumentNumber] = 1;
	else
		m_vnArguments[ArgumentNumber] = 0;

	// If the puzzle should be completed in the right order
	if(m_bSequential && m_vnArguments[ArgumentNumber] == 1)
	{
		// If the puzzle is sequential and this torch was just lit

		// Turn off all the ones that should come after this
		for(unsigned int i = ArgumentNumber + 1; i < m_uiArgCount; ++i)
			m_vnArguments[i] = 0;

		// And if the one before this was off
		if(ArgumentNumber > 0)
		{
			if(m_vnArguments[ArgumentNumber - 1] == 0)
			{
				// Turn off all the ones that came before it
				for(int i = ArgumentNumber - 1; i >= 0; --i)
					m_vnArguments[i] = 0;
			}
		}
	}
}

void IBasePuzzle::TryFiringEvent(void)
{
	for(unsigned int i=0; i < m_vnArguments.size(); ++i)
	{
		if(m_vnArguments[i] == 0)
			break;

		if(m_vnArguments[i] == 1 && i == m_vnArguments.size() - 1)
			CEventSystem::GetInstance()->SendEvent(m_szEventToFire);
	}
}

void IBasePuzzle::Destroy(void)
{
	m_uiArgCount = 0;
	m_vnArguments.clear();
}

int IBasePuzzle::GetNumberOfArgumentsOn(void)
{
	int n = 0;
	for(unsigned int i=0; i < m_uiArgCount; ++i)
		if(m_vnArguments[i] == 1) n++;
	return n;
}