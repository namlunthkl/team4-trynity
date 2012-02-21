////////////////////////////////////////////////////////////////////////
//    File Name				:	"CMap.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/06 - 9:40 PM
//    Purpose				:	To contain all information needed to
//								render a map to the screen and functions
//								to load a map from an xml file exported
//								from the tile editor
////////////////////////////////////////////////////////////////////////

// Precompiled header
#include "StdAfx.h"
#include "..\StdAfx.h"

#include "../tinyxml/tinyxml.h"
#include "../Messaging/CStringTable.h"
#include "CWorldEngine.h"


// Include header file
#include "CMap.h"

// Constructor
// Sets all parameters to 0/NULL values
CMap::CMap(void)
{
	SetPosX(0);
	SetPosY(0);
	SetWidth(0);
	SetHeight(0);
	SetTileset(NULL);
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Load map information from a xml file
//	Parameters	:	Location of the xml file to load
//	Return		:	False if load failed, true if succeeded
////////////////////////////////////////////////////////////////////////
bool CMap::Load(const char const * szFilename, CStringTable* pStringTable)
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
	const char* szTileset = "";
	int nWidth = 0;
	int nHeight = 0;
	int nPosX = 0;
	int nPosY = 0;
	int nTileType = 0;
	int nTilePosX = 0;
	int nTilePosY = 0;
	const char* szEvent = "";

	// Get the Tileset ID
	szTileset = pRoot->Attribute("tileset");
	unsigned char ucTilesetID = pStringTable->LoadStringA(szTileset);
	CTileset* pTileset = CWorldEngine::GetInstance()->GetTileset(ucTilesetID);
	SetTileset(pTileset);

	// Get the Map Element
	TiXmlElement* pMap = pRoot->FirstChildElement("Map");
	// If it failed return false...
	if(!pMap)
		return false;

	// Read all the data from the tileset file
	pMap->Attribute("width", &nWidth);
	pMap->Attribute("height", &nHeight);
	pMap->Attribute("posX", &nPosX);
	pMap->Attribute("posY", &nPosY);

	// Set the map members
	SetWidth(nWidth);
	SetHeight(nHeight);
	SetPosX(nPosX);
	SetPosY(nPosY);

	// First Layer in the map
	TiXmlElement* pLayer = pMap->FirstChildElement("Layer");
	// If it failed return false...
	if(!pLayer)
		return false;

	// Load all the layers
	while(pLayer)
	{
		// Create the layer
		CLayer tempLayer;

		// Get the Tile element
		TiXmlElement* pTile = pLayer->FirstChildElement("Tile");

		// Load all the tiles
		while(pTile)
		{
			// Read all the data for the tile here
			pTile->Attribute("PosX", &nTilePosX);
			pTile->Attribute("PosY", &nTilePosY);
			pTile->Attribute("Type", &nTileType);
			szEvent = pTile->Attribute("Event");

			// Load the event in the string table and get its ID
			unsigned char ucEventID = pStringTable->LoadStringA(szEvent);

			// Create the tile
			CTile tempTile((unsigned char)nTilePosX, (unsigned char)nTilePosY,
				(unsigned char)nTileType, ucEventID);

			// Push the tile to the layer
			tempLayer.PushTile(tempTile);

			// Move on to the next Tile (sibling)
			pTile = pTile->NextSiblingElement("Tile");
		}

		// Push the layer to the list
		m_vLayers.push_back(tempLayer);

		// Move on to the next Layer (sibling)
		pLayer = pLayer->NextSiblingElement("Layer");
	}

	// Success!
	return true;
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Draw the map's tiles that are inside the window's
//					space
////////////////////////////////////////////////////////////////////////
void CMap::Render(void)
{
	// Indexes we'll need for looping
	unsigned int uiIndexLayer	= 0;		// Loop through layers
	unsigned int uiIndexWidth	= 0;		// Loop through the map width / columns
	unsigned int uiIndexHeight	= 0;		// Loop through the map height / lines
	unsigned int uiIndexTile	= 0;		// Keep track of the tile we're looking in the array

	// First loop through all the layers
	for(uiIndexLayer = 0; uiIndexLayer < m_vLayers.size(); ++uiIndexLayer)
	{
		// For each layer, loop through all the tiles
		for(uiIndexTile = 0; uiIndexTile < m_vLayers[uiIndexLayer].GetSize(); ++uiIndexTile)
		{
			// Get a pointer to the current tile - for better readability
			CTile* tileCurrent = m_vLayers[uiIndexLayer].GetTile(uiIndexTile);

			// Get position to draw;
			int nTileWorldPosX = GetPosX() + GetTileset()->GetTileWidth() * uiIndexWidth;
			int nTileWorldPosY = GetPosY() + GetTileset()->GetTileHeight() * uiIndexHeight;
			int nTileScreenPosX = nTileWorldPosX - 0;	// TODO: Replace 0 by camera's X position
			int nTileScreenPosY = nTileWorldPosY - 0;	// TODO: Replace 0 by camera's Y position
			
			if(nTileScreenPosX >= 0 && (nTileScreenPosX + GetTileset()->GetTileWidth()) < GAME->GetScreenWidth()
				&& nTileScreenPosY >= 0 && (nTileScreenPosY + GetTileset()->GetTileHeight()) < GAME->GetScreenHeight())
			{
				// Get the source rect of that tile
				RECT rectSource = GetTileSourceRect(tileCurrent);

				// Draw the tile using texture manager
				TEX_MNG->Draw(GetTileset()->GetImageID(), nTileScreenPosX, nTileScreenPosY, 1.0f, 1.0f, &rectSource);
			}

			// Since we're reading line by line, from left to right, we need
			// to increase the width index every time we draw a tile
			++uiIndexWidth;

			// Once we reach the end of a line, though, we need to reset the
			// width index and increase the height index
			if(uiIndexWidth >= GetWidth())
			{
				// Reset width index
				uiIndexWidth = 0;

				// Increase height index
				++uiIndexHeight;
			}
		}

		// Once we're done loading a layer, we should reset the width and height
		// indexes, so that the next layer is rendered above this one
		uiIndexWidth = 0;
		uiIndexHeight = 0;
	}
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Check collisions against all tiles on screen
//	Parameters	:	pBase - Object that we're checking collisions with
//	Return		:	False if collided, true otherwise
////////////////////////////////////////////////////////////////////////
bool CMap::CheckCollisions(const IBaseInterface* pBase)
{
	// TODO: Check collisions against all tiles on screen
	return true;
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Get the source RECT of a tile in a tileset
//	Parameters	:	Tile to use
//	Return		:	The source RECT
////////////////////////////////////////////////////////////////////////
RECT CMap::GetTileSourceRect(CTile* tileCurrent)
{
	RECT rectSource;
	rectSource.left = tileCurrent->GetPosX() * GetTileset()->GetTileWidth();
	rectSource.top = tileCurrent->GetPosY() * GetTileset()->GetTileHeight();
	rectSource.right = rectSource.left + GetTileset()->GetTileWidth();
	rectSource.bottom = rectSource.top + GetTileset()->GetTileHeight();

	return rectSource;
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Check collisions against all tiles on screen
//	Parameters	:	pBase - Object that we're checking collisions with
//	Return		:	False if collided, true otherwise
////////////////////////////////////////////////////////////////////////
bool CMap::CheckCollisions(const IBaseInterface* pBase)
{
	// TODO: Check collisions against all tiles on screen
	return true;
}