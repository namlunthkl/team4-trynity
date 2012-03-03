////////////////////////////////////////////////////////////////////////
//    File Name				:	"CPuzzleManager.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09 - 12:59 AM
//    Purpose				:	Holds all game puzzles
//
//    Last Updater Name		:	Name of last person who updated it
//    Last Update Date		:	month/day - hour:min (AM/PM)
//    Last Update Notes		:	Notes from the last person who updated it
//
//    Other Notes			:   Notes from other updates are moved here
//								when the file is updated again
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "CPuzzleManager.h"
#include "CPuzzleFunctions.h"

void CPuzzleManager::InitPuzzleManager(void)
{
	CPuzzle* TorchPuzzle = new CPuzzle();
	vector<char*> m_vpEvents;
	m_vpEvents.push_back("TorchLit.0");
	m_vpEvents.push_back("TorchLit.1");
	m_vpEvents.push_back("TorchLit.2");
	m_vpEvents.push_back("TorchLit.3");

	TorchPuzzle->Initialize(4, "OpenDoor", m_vpEvents, PuzzleA_Torches_HandleEvent, PuzzleA_Torched_Update, "resource/data/FireFlicker.xml");

	m_vpPuzzles.push_back(TorchPuzzle);
}

void CPuzzleManager::ShutdownPuzzleManager(void)
{

}

unsigned int CPuzzleManager::PushPuzzle(CPuzzle* pPuzzle)
{
	if(pPuzzle)
		m_vpPuzzles.push_back(pPuzzle);

	return m_vpPuzzles.size() - 1;
}

CPuzzleManager* CPuzzleManager::GetInstance(void)
{
	static CPuzzleManager instance;
	return &instance;
}

void CPuzzleManager::UpdatePuzzles(float fElapsedTime)
{
	for(unsigned int i=0; i < m_vpPuzzles.size(); ++i)
		m_vpPuzzles[i]->Update(fElapsedTime);
}

void CPuzzleManager::RenderPuzzles(void)
{
	for(unsigned int i=0; i < m_vpPuzzles.size(); ++i)
		m_vpPuzzles[i]->Render();
}