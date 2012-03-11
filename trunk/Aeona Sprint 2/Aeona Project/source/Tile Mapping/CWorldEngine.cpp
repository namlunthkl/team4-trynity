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
#include "../Input Manager/CInputManager.h"
#include "../Game Objects/CBaseObject.h"

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

	m_nCullingMode = CMap::CULLING_SCREEN;
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

	GAME->RenderLoadingScreen( GAME->IncrementAndReturnAmountLoaded(), 0);

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

		//GAME->RenderLoadingScreen( GAME->IncrementAndReturnAmountLoaded(), 0);
	}

	// Succeeded
	return true;
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Updates all maps
////////////////////////////////////////////////////////////////////////
void CWorldEngine::UpdateWorld(float fElapsedTime)
{
	Input();
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Get input that changes the maps
////////////////////////////////////////////////////////////////////////
void CWorldEngine::Input(void)
{
	if(INPUT->KeyPressed(DIK_K))
	{
		m_nCullingMode++;

		if(m_nCullingMode == CMap::CULLING_MAX)
			m_nCullingMode = 0;
	}
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Render all maps
////////////////////////////////////////////////////////////////////////
void CWorldEngine::RenderWorldBelowObjects(void)
{
	for(unsigned int uiIndex = 0; uiIndex < m_vpMaps.size(); ++uiIndex)
	{
		CMap* curMap = m_vpMaps[uiIndex];

		// If the map is not on screen, don't even bother calling render on it
		double left = GetScreenPosX(curMap->GetPosX());
		double right = GetScreenPosX(curMap->GetPosX() + curMap->GetWidth() * curMap->GetTileset()->GetTileWidth());
		double top = GetScreenPosY(curMap->GetPosY());
		double bottom = GetScreenPosY(curMap->GetPosY() + curMap->GetHeight() * curMap->GetTileset()->GetTileHeight());

		if(right > 0 &&	left < GAME->GetScreenWidth() &&
			bottom > 0 && top < GAME->GetScreenHeight())
			curMap->RenderFirstLayers(m_nCullingMode);
	}
}

void CWorldEngine::RenderWorldAboveObjects(void)
{
	for(unsigned int uiIndex = 0; uiIndex < m_vpMaps.size(); ++uiIndex)
	{
		CMap* curMap = m_vpMaps[uiIndex];

		// If the map is not on screen, don't even bother calling render on it
		double left = GetScreenPosX(curMap->GetPosX());
		double right = GetScreenPosX(curMap->GetPosX() + curMap->GetWidth() * curMap->GetTileset()->GetTileWidth());
		double top = GetScreenPosY(curMap->GetPosY());
		double bottom = GetScreenPosY(curMap->GetPosY() + curMap->GetHeight() * curMap->GetTileset()->GetTileHeight());

		if(right > 0 &&	left < GAME->GetScreenWidth() &&
			bottom > 0 && top < GAME->GetScreenHeight())
				curMap->RenderLastLayers(m_nCullingMode);
	}
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Check collisions against all tiles on screen
//	Parameters	:	pBase - Object that we're checking collisions with
//	Return		:	True if collided, false otherwise
////////////////////////////////////////////////////////////////////////
bool CWorldEngine::CheckCollisions(IBaseInterface* pBase,
	RectD* CollisionRect, unsigned int uiObjType)
{
	double posx = 0;
	double posy = 0;

	if(pBase)
	{
		posx = ((CBaseObject*)pBase)->GetPosX();
		posy = ((CBaseObject*)pBase)->GetPosY();
	}
	else
	{
		posx = (CollisionRect->right + CollisionRect->left) / 2;
		posy = (CollisionRect->bottom + CollisionRect->top) / 2;
	}

	// Only check collision on the map where pBase is
	CMap* curMap = GetMapWherePointIs(posx, posy);

	// If the object is in no map, something is wrong, so GTFO!
	if(!curMap)
		return false;

	// If the map is not on screen, don't even bother calling check collisions on it
	double left = GetScreenPosX(curMap->GetPosX());
	double right = GetScreenPosX(curMap->GetPosX() + curMap->GetWidth() * curMap->GetTileset()->GetTileWidth());
	double top = GetScreenPosY(curMap->GetPosY());
	double bottom = GetScreenPosY(curMap->GetPosY() + curMap->GetHeight() * curMap->GetTileset()->GetTileHeight());

	if(right > 0 &&	left < GAME->GetScreenWidth() &&
		bottom > 0 && top < GAME->GetScreenHeight())
	{
		if(curMap->CheckCollisions(pBase, m_pStringTable, CollisionRect, uiObjType))
			// If collided in this map, return true
			return true;
	}
	return false;
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


const char* CWorldEngine::GetRegionName(double dPositionX, double dPositionY)
{
	CMap* map = GetMapWherePointIs(dPositionX, dPositionY);

	if(map)
		return m_pStringTable->GetString(map->GetTileset()->GetID());
	else
		return nullptr;
}

CMap* CWorldEngine::GetMapWherePointIs(double dPositionX, double dPositionY)
{
	for(unsigned int uiIndex = 0; uiIndex < m_vpMaps.size(); ++uiIndex)
	{
		CMap* curMap = m_vpMaps[uiIndex];

		if(dPositionX > curMap->GetPosX() &&
			dPositionX < curMap->GetPosX() + curMap->GetWidth() * curMap->GetTileset()->GetTileWidth() &&
			dPositionY > curMap->GetPosY() &&
			dPositionY < curMap->GetPosY() + curMap->GetHeight() * curMap->GetTileset()->GetTileHeight())
		{
			return curMap;
		}
	}

	return nullptr;
}