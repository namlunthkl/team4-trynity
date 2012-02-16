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

	m_pStringTable = new CStringTable(UCHAR_MAX);
}

//////////////////////////////////////////////////////////////////////////
////	Purpose		:	Initialize the map
////	Parameters	:	szFilename - location of the xml file to load
////					nPosX and nPosY - position of the map in the world
////	Return		:	False if initialization failed, true if succeeded
//////////////////////////////////////////////////////////////////////////
//bool CMap::Initialize(char* szFilename, CTileset* Tileset, int nPosX, int nPosY)
//{
//	// HACK
//	SetPosX(nPosX);
//	SetPosY(nPosY);
//	SetTileset(Tileset);
//
//	// Try loading the file
//	// If loading succeeds, return true
//	if(Load(szFilename))
//		return true;
//	// Else, return false
//	else
//		return false;
//}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Load map information from a xml file
//	Parameters	:	Location of the xml file to load
//	Return		:	False if load failed, true if succeeded
////////////////////////////////////////////////////////////////////////
bool CMap::Load(const char const * szFilename)
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
	int nTilesetID = 0;
	int nWidth = 0;
	int nHeight = 0;
	int nPosX = 0;
	int nPosY = 0;
	int nTileType = 0;
	int nTilePosX = 0;
	int nTilePosY = 0;
	const char* szEvent = "";

	// Get the Tileset ID
	pRoot->Attribute("tileset", &nTilesetID);
	CTileset* pTileset = CWorldEngine::GetInstance()->GetTileset(nTilesetID);
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
			unsigned char ucEventID = m_pStringTable->LoadStringA(szEvent);

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
			// TODO: The most efficient to cull tiles in here is to use some kind of
			// algorithm to figure out between which indexes will the rendered tiles
			// be. Then, we can loop through all of them and continue immediately if
			// the index we're in is not on that range.

			// Get a pointer to the current tile - for better readability
			CTile* tileCurrent = m_vLayers[uiIndexLayer].GetTile(uiIndexTile);

			// Get the source rect of that tile
			RECT rectSource = GetTileSourceRect(tileCurrent);

			// Draw the tile using texture manager
			TEX_MNG->Draw(GetTileset()->GetImageID(),
				GetPosX() + GetTileset()->GetTileWidth() * uiIndexWidth,
				GetPosY() + GetTileset()->GetTileHeight() * uiIndexHeight,
				1.0f, 1.0f, &rectSource);

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