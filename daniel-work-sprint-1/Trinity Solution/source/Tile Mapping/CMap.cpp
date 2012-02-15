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
//	Purpose		:	Initialize the map
//	Parameters	:	szFilename - location of the xml file to load
//					nPosX and nPosY - position of the map in the world
//	Return		:	False if initialization failed, true if succeeded
////////////////////////////////////////////////////////////////////////
bool CMap::Initialize(char* szFilename, CTileset* Tileset, int nPosX, int nPosY)
{
	// HACK
	SetPosX(nPosX);
	SetPosY(nPosY);
	SetTileset(Tileset);

	// Try loading the file
	// If loading succeeds, return true
	if(Load(szFilename))
		return true;
	// Else, return false
	else
		return false;
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Load map information from a xml file
//	Parameters	:	Location of the xml file to load
//	Return		:	False if load failed, true if succeeded
////////////////////////////////////////////////////////////////////////
bool CMap::Load(char* szFilename)
{
	// Regular load using the old version of the Tile Editor
	// (from Windows Programming II)
#if 0
	// HACK
	std::ifstream in;
	in.open(szFilename);
	if(in.is_open())
	{
		short sWidth;
		short sHeight;
		short sTilesetWidth;
		short sTilesetHeight;
		short sTileWidth;
		short sTileHeight;

		in >> sWidth;
		SetWidth(sWidth);
		in >> sHeight;
		SetHeight(sHeight);
		
		in >> sTilesetWidth;
		GetTileset()->SetWidth((unsigned char)sTilesetWidth);
		in >> sTilesetHeight;
		GetTileset()->SetHeight((unsigned char)sTilesetHeight);

		sTileWidth = 32;
		GetTileset()->SetTileWidth((unsigned char)sTileWidth);
		sTileHeight = 32;
		GetTileset()->SetTileHeight((unsigned char)sTileHeight);

		m_vLayers.push_back(CLayer());

		while(in.good())
		{
			short sX;
			short sY;

			in >> sX;
			in >> sY;

			if(in.eof())
				break;

			m_vLayers[0].PushTile(CTile((unsigned char)sX, (unsigned char)sY, 0));
		}

		return true;
	}
#endif

	// TODO: Load from XML file
	// (Type that the new tile editor will export)


	// If loading failed we should return false
	return false;
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Draw the map's tiles that are inside the window's
//					space
////////////////////////////////////////////////////////////////////////
void CMap::Render(void)
{
	// This code is rendering all the tiles in the map, interpreting
	// the tiles inside the vector as being pushed one column at a time,
	// from top to bottom
#if 0
	// HACK
	unsigned int uiIndexCol = 0;
	unsigned int uiIndexLine = 0;
	for(unsigned int uiIndexTile = 0; uiIndexTile < m_vLayers[0].Size(); ++uiIndexTile)
	{
		CTile* tile = m_vLayers[0].GetTile(uiIndexTile);

		RECT source;
		source.left = tile->GetPosX() * GetTileset()->GetTileWidth();
		source.top = tile->GetPosY() * GetTileset()->GetTileHeight();
		source.right = source.left + GetTileset()->GetTileWidth();
		source.bottom = source.top + GetTileset()->GetTileHeight();

		TEX_MNG->Draw(GetTileset()->GetImageID(), GetPosX() + GetTileset()->GetTileWidth() * uiIndexCol,
			GetPosY() + GetTileset()->GetTileHeight() * uiIndexLine, 1.0f, 1.0f,
			&source);

		uiIndexLine++;

		if(uiIndexLine >= GetHeight())
		{
			uiIndexLine = 0;
			uiIndexCol++;
		}
	}
#endif

	// TODO: Create a render function that will loop through the tiles
	// interpreting them as how they're added using the new Load function.
	// (probably one line at a time, from left to right)
	// Only render the tiles that are on the screen's area for optimization
	// purposes.
}