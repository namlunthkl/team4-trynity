////////////////////////////////////////////////////////////////////////
//    File Name				:	"CTileset.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/15 - 11:39 PM
//    Purpose				:	Tileset class used for tile mapping
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "CTileset.h"
#include "../tinyxml/tinyxml.h"
#include "../Messaging/CStringTable.h"


// Constructor
CTileset::CTileset(void)
{
	SetImageID(-1);
	SetWidth(0);
	SetHeight(0);
	SetTileWidth(0);
	SetTileHeight(0);
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Load tileset information from a xml file
//	Parameters	:	Location of the xml file to load
//	Return		:	False if load failed, true if succeeded
////////////////////////////////////////////////////////////////////////
bool CTileset::Load(const char * const szFilename, CStringTable* pStringTable)
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
	int nWidth = 0;
	int nHeight = 0;
	int nTileWidth = 0;
	int nTileHeight = 0;
	const char* szImage = "";
	int nTransparentColor = 0;
	const char* szTilesetName = "";

	// Read all the data from the tileset file
	pRoot->Attribute("width", &nWidth);
	pRoot->Attribute("height", &nHeight);
	pRoot->Attribute("tilewidth", &nTileWidth);
	pRoot->Attribute("tileheight", &nTileHeight);
	pRoot->Attribute("transparent", &nTransparentColor);
	szTilesetName = pRoot->Attribute("id");
	szImage = pRoot->Attribute("image");

	// Set the tileset members
	SetImageID(TEX_MNG->LoadTexture(szImage, (DWORD)nTransparentColor));
	SetWidth(nWidth);
	SetHeight(nHeight);
	SetTileWidth(nTileWidth);
	SetTileHeight(nTileHeight);
	SetID(pStringTable->LoadString(szTilesetName));

	// Success!
	return true;
}

