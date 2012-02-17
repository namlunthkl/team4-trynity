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
#include "../tinyxml/tinyxml.h"
#include "../Messaging/CStringTable.h"

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
	m_pStringTable = new CStringTable(UCHAR_MAX);

	LoadAllMaps("resource/WorldEngine.xml");

	m_rDrawArea.top = 0 - 256;
	m_rDrawArea.left = 0 - 256;
	m_rDrawArea.right = m_rDrawArea.left + GAME->GetScreenWidth() + 256;
	m_rDrawArea.bottom = m_rDrawArea.top + GAME->GetScreenHeight() + 256;
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Load all maps defined in an XML File
//	Parameters	:	szFilename: File that has all the maps' file names
////////////////////////////////////////////////////////////////////////
bool CWorldEngine::LoadAllMaps(const char* szFilename)
{
	// Create XML doc
	TiXmlDocument doc;
	// Try to load the file, and if it fails, return false
	if(!doc.LoadFile(szFilename))
		return false;

	// Get a pointer to the root
	TiXmlElement* pRoot = doc.RootElement();
	// If that wasn't created properly too, get out of here
	if(!pRoot)
		return false;

	// Temporary variables to store the data we'll read
	const char* szSourceFile = "";

	// Get a pointer to the first Tileset
	TiXmlElement* pTileset = pRoot->FirstChildElement("Tileset");
	// If it failes return false...
	if(!pTileset)
		return false;
	
	// Load all the tilesets
	while(pTileset)
	{
		// Create the tileset
		CTileset* tempTileset = new CTileset();
		// Get the file name
		szSourceFile = pTileset->Attribute("file");
		// Load the tileset
		tempTileset->Load(szSourceFile, m_pStringTable);
		// Push it to the tilesets vector
		m_vpTilesets.push_back(tempTileset);

		// Move on to the next sibling
		pTileset = pTileset->NextSiblingElement("Tileset");
	}

	// Get a pointer to the first Map
	TiXmlElement* pMap = pRoot->FirstChildElement("Map");
	// If it failes return false...
	if(!pMap)
		return false;
	
	// Load all the maps
	while(pMap)
	{
		// Create the tileset
		CMap* tempMap = new CMap();
		// Get the file name
		szSourceFile = pMap->Attribute("file");
		// Load the tileset
		tempMap->Load(szSourceFile, m_pStringTable);
		// Push it to the tilesets vector
		m_vpMaps.push_back(tempMap);

		// Move on to the next sibling
		pMap = pMap->NextSiblingElement("Map");
	}

	// Succeeded
	return true;
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
	for(unsigned int i=0; i < m_vpMaps.size(); ++i)
	{
		delete m_vpMaps[i];
		m_vpMaps[i] = NULL;
	}
	for(unsigned int i=0; i < m_vpTilesets.size(); ++i)
	{
		delete m_vpTilesets[i];
		m_vpTilesets[i] = NULL;
	}
	m_vpMaps.clear();
	m_vpTilesets.clear();

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

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Get a pointer to a specific tileset
//	Parameters	:	The wanted tileset's ID
////////////////////////////////////////////////////////////////////////
CTileset* CWorldEngine::GetTileset(unsigned char ucID)
{
	// Loop through all the tilesets until the right one is found
	for(unsigned int uiTilesetIndex = 0; uiTilesetIndex < m_vpTilesets.size(); ++uiTilesetIndex)
	{
		// If that's the right one, return it
		if(m_vpTilesets[uiTilesetIndex]->GetID() == ucID)
			return m_vpTilesets[uiTilesetIndex];
	}

	// If none was found, return null
	return NULL;
}