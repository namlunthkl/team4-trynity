////////////////////////////////////////////////////////////////////////
//    File Name				:	"CMap.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/06 - 9:40 PM
//    Purpose				:	To contain all information needed to
//								render a map to the screen and functions
//								to load a map from an xml file exported
//								from the tile editor
//
//    Last Updater Name		:	Name of last person who updated it
//    Last Update Date		:	month/day - hour:min (AM/PM)
//    Last Update Notes		:	Notes from the last person who updated it
//
//    Other Notes			:   Notes from other updates are moved here
//								when the file is updated again
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CMAP_H_
#define CMAP_H_

// A map has an array of Layers
#include "CLayer.h"

// A map has a tileset
#include "CTileset.h"

// Map class
// An array of layers, a tileset, a size and a position in the world
class CMap
{
	//////////////////////////////////////////////////////////////////////////
	//	------------------------------------------------------------------	//
	//							DATA	MEMBERS								//
	//	------------------------------------------------------------------	//
	//////////////////////////////////////////////////////////////////////////
	
	// Array of layers
	vector<CLayer>	m_vLayers;

	// Position of the map in the world
	int				m_nPosX;
	int				m_nPosY;

	// Size of the map in number of tiles
	int				m_nWidth;
	int				m_nHeight;

	// Pointer to this map's tileset
	CTileset*		m_pTileset;

	//////////////////////////////////////////////////////////////////////////
	//	------------------------------------------------------------------	//
	//							PRIVATE	FUNCTIONS							//
	//	------------------------------------------------------------------	//
	//////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Load map information from a xml file
	//	Parameters	:	Location of the xml file to load
	//	Return		:	False if load failed, true if succeeded
	////////////////////////////////////////////////////////////////////////
	bool Load(char* szFilename);

public:
	//////////////////////////////////////////////////////////////////////////
	//	------------------------------------------------------------------	//
	//							PUBLIC	FUNCTIONS							//
	//	------------------------------------------------------------------	//
	//////////////////////////////////////////////////////////////////////////

	// Constructor
	CMap(void);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Initialize the map
	//	Parameters	:	szFilename - location of the xml file to load
	//					nPosX and nPosY - position of the map in the world
	//	Return		:	False if initialization failed, true if succeeded
	////////////////////////////////////////////////////////////////////////
	bool Initialize(char* szFilename, CTileset* pTileset, int nPosX, int nPosY);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Draw the map's tiles that are inside the window's
	//					space
	////////////////////////////////////////////////////////////////////////
	void Render(void);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Unload the file that is loaded by the Load function
	////////////////////////////////////////////////////////////////////////
	void Shutdown(void);

	//////////////////////////////////////////////////////////////////////////
	//	------------------------------------------------------------------	//
	//						ACCESSORS AND MUTATORS							//
	//	------------------------------------------------------------------	//
	//////////////////////////////////////////////////////////////////////////

	// Accessors
	inline int			GetPosX(void)		{ return m_nPosX; }
	inline int			GetPosY(void)		{ return m_nPosY; }
	inline int			GetWidth(void)		{ return m_nWidth; }
	inline int			GetHeight(void)		{ return m_nHeight; }
	inline CTileset*	GetTileset(void)	{ return m_pTileset; }

	// Mutators
	inline void SetPosX(int nPosX)				{ m_nPosX = nPosX; }
	inline void SetPosY(int nPosY)				{ m_nPosY = nPosY; }
	inline void SetWidth(int nWidth)			{ m_nWidth = nWidth; }
	inline void SetHeight(int nHeight)			{ m_nHeight = nHeight; }
	inline void SetTileset(CTileset* pTileset)	{ m_pTileset = pTileset; }
};



#endif // CMAP_H_