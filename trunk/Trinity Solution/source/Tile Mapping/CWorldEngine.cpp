//    File Name				:	"CWorldEngine.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/13 - 8:40 PM
//    Purpose				:	Singleton that handles the loading
//								and storage of all the maps and
//								puzzles in the game
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "CWorldEngine.h"

// Singleton's instance
CWorldEngine* CWorldEngine::sm_pInstance = NULL;

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Singleton's accessor
////////////////////////////////////////////////////////////////////////
CWorldEngine* CWorldEngine::GetInstance(void)
{
	if(!sm_pInstance)
		sm_pInstance = new CWorldEngine();

	return sm_pInstance;
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Initialize all variables, call LoadAllMaps()
////////////////////////////////////////////////////////////////////////
void CWorldEngine::InitWorldEngine(void)
{
	// TODO: Change that to use default filename with maps information
	LoadAllMaps("FILENAME.XML");

	m_rDrawArea.top = 0 - 256;
	m_rDrawArea.left = 0 - 256;
	m_rDrawArea.right = m_rDrawArea.left + GAME->GetScreenWidth() + 256;
	m_rDrawArea.bottom = m_rDrawArea.top + GAME->GetScreenHeight() + 256;
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Load all maps defined in an XML File
//	Parameters	:	szFilename: File that has all the maps' file names
////////////////////////////////////////////////////////////////////////
void CWorldEngine::LoadAllMaps(const char* szFilename)
{
	// TODO: Write code to go through the file passed,
	// get the number of tilesets, open and read all the tilesets passed,
	// get the number of maps, open and read all the maps passed
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Updates all maps
////////////////////////////////////////////////////////////////////////
void CWorldEngine::UpdateWorld(float fElapsedTime)
{
	
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Render all maps
////////////////////////////////////////////////////////////////////////
void CWorldEngine::RenderWorld(void)
{
	for(unsigned int uiIndex = 0; uiIndex < m_vpMaps.size(); ++uiIndex)
	{
		CMap* curMap = m_vpMaps[uiIndex];

		if(curMap->GetPosX() >= m_rDrawArea.left &&
			curMap->GetPosY() >= m_rDrawArea.top &&
			curMap->GetPosX() + curMap->GetWidth() <= m_rDrawArea.right &&
			curMap->GetPosY() + curMap->GetHeight() <= m_rDrawArea.bottom)
		{
			curMap->Render();
		}
	}
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Check collisions against all tiles on screen
//	Parameters	:	pBase - Object that we're checking collisions with
//	Return		:	False if collided, true otherwise
////////////////////////////////////////////////////////////////////////
bool CWorldEngine::CheckCollisions(const IBaseInterface* pBase)
{
	// TODO: Call check collision on all maps that are on screen
	for(unsigned int uiIndex = 0; uiIndex < m_vpMaps.size(); ++uiIndex)
	{
		CMap* curMap = m_vpMaps[uiIndex];

		if(curMap->GetPosX() >= m_rDrawArea.left &&
			curMap->GetPosY() >= m_rDrawArea.top &&
			curMap->GetPosX() + curMap->GetWidth() <= m_rDrawArea.right &&
			curMap->GetPosY() + curMap->GetHeight() <= m_rDrawArea.bottom)
		{
			// TODO: Define check collisions function on CMap
			// curMap->CheckCollisions(pBase);
		}
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Unload files
////////////////////////////////////////////////////////////////////////
void CWorldEngine::ShutdownWorldEngine(void)
{
	// TODO: Call shutdown on all maps and tilesets
	// TODO: Each map and tileset should have a shutdown method to
	// clean up its memory and unload assets
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Delete the singleton's instance
////////////////////////////////////////////////////////////////////////
void CWorldEngine::DeleteInstance(void)
{
	if(sm_pInstance)
	{
		delete sm_pInstance;
		sm_pInstance = NULL;
	}
}