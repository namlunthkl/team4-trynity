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

// For CheckCollisions function
class IBaseInterface;
// For Event names
class CStringTable;

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

	// For tile collision checks and firing events
	enum ETyleByte { BIT_TILE_COLLISION = 0, BIT_EVENT_ANY_COLLISION,
		BIT_EVENT_PLAYER_COLLISION, BIT_EVENT_ACTION_BUTTON,
		BIT_EVENT_BASIC_ATTACK, BIT_EVENT_FIRE_BLADE,
		BIT_EVENT_EARTH_HAMMER, BIT_EVENT_AIR_CROSSBOW };


	//////////////////////////////////////////////////////////////////////////
	//	------------------------------------------------------------------	//
	//							PRIVATE	FUNCTIONS							//
	//	------------------------------------------------------------------	//
	//////////////////////////////////////////////////////////////////////////

	

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Get the source RECT of a tile in a tileset
	//	Parameters	:	Tile to use
	//	Return		:	The source RECT
	////////////////////////////////////////////////////////////////////////
	RECT GetTileSourceRect(CTile* tileCurrent);

public:
	//////////////////////////////////////////////////////////////////////////
	//	------------------------------------------------------------------	//
	//							PUBLIC	FUNCTIONS							//
	//	------------------------------------------------------------------	//
	//////////////////////////////////////////////////////////////////////////

	// Constructor
	CMap(void);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Load map information from a xml file
	//	Parameters	:	Location of the xml file to load
	//	Return		:	False if load failed, true if succeeded
	////////////////////////////////////////////////////////////////////////
	bool Load(char const * const szFilename, CStringTable * pStringTable);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Draw the map's tiles that are inside the window's
	//					space
	////////////////////////////////////////////////////////////////////////
	void Render(void);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Check collisions against all tiles on screen
	//	Parameters	:	pBase - Object that we're checking collisions with
	//	Return		:	True if collided, false otherwise
	////////////////////////////////////////////////////////////////////////
	bool CheckCollisions(IBaseInterface* pBase, CStringTable * pStringTable);

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