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
#include "CTorchPuzzle.h"
#include "CFinalTorchPuzzleThatBernWantedButDanielMade.h"

void CPuzzleManager::InitPuzzleManager(void)
{
	// Push all puzzles
	CTorchPuzzle* TorchPuzzle = new CTorchPuzzle;
	TorchPuzzle->Create(4, "victory", "TorchLit", true);
	m_vpPuzzles.push_back(TorchPuzzle);

	CTorchPuzzle* TorchPuzzleB = new CTorchPuzzle;
	TorchPuzzleB->Create(1, "", "Fire", false);
	m_vpPuzzles.push_back(TorchPuzzleB);

	CTorchPuzzle* TorchPuzzleBoss1 = new CTorchPuzzle;
	TorchPuzzleBoss1->Create(4,"Light Torch.0", "TopLeftRoom",true);
	m_vpPuzzles.push_back(TorchPuzzleBoss1);
	CTorchPuzzle* TorchPuzzleBoss2 = new CTorchPuzzle;
	TorchPuzzleBoss2->Create(4,"Light Torch.1", "TopRightRoom",true);
	m_vpPuzzles.push_back(TorchPuzzleBoss2);
	CTorchPuzzle* TorchPuzzleBoss3 = new CTorchPuzzle;
	TorchPuzzleBoss3->Create(4,"Light Torch.2", "BottomLeftRoom",true);
	m_vpPuzzles.push_back(TorchPuzzleBoss3);
	CTorchPuzzle* TorchPuzzleBoss4 = new CTorchPuzzle;
	TorchPuzzleBoss4->Create(4,"Light Torch.3", "BottomRightRoom",true);
	m_vpPuzzles.push_back(TorchPuzzleBoss4);

	CFinalTorchPuzzleThatBernWantedButDanielMade* TorchPuzzleBossRoom = new CFinalTorchPuzzleThatBernWantedButDanielMade;
	TorchPuzzleBossRoom->Create(4,"OpenBossRoom", "Light Torch",false);
	m_vpPuzzles.push_back(TorchPuzzleBossRoom);
}

void CPuzzleManager::ShutdownPuzzleManager(void)
{
	// Destroy all puzzles
	for(unsigned int i=0; i < m_vpPuzzles.size(); ++i)
	{
		m_vpPuzzles[i]->Destroy();
		delete m_vpPuzzles[i];
	}
	m_vpPuzzles.clear();
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