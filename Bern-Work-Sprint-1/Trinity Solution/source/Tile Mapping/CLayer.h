////////////////////////////////////////////////////////////////////////
//    File Name				:	"CLayer.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/06 - 9:05 PM
//    Purpose				:	Layer class used for tile mapping
//
//    Last Updater Name		:	Name of last person who updated it
//    Last Update Date		:	month/day - hour:min (AM/PM)
//    Last Update Notes		:	Notes from the last person who updated it
//
//    Other Notes			:   Notes from other updates are moved here
//								when the file is updated again
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CLAYER_H_
#define CLAYER_H_

// CLayer has a dynamic array of tiles
//		Array
#include <vector>
using std::vector;
//		Tiles
#include "CTile.h"

// CLayer class
// Defines a layer composed of a vector of tiles
class CLayer
{
	// Vector of tiles
	vector<CTile> m_vTiles;

	// ID of this layer - represents layer position
	unsigned char m_ucID;

public:
	// Constructor
	CLayer(unsigned char ucID = 0)			{ SetID(ucID); }

	// ID Accessor and mutator
	inline unsigned char GetID(void)		{ return m_ucID; }
	inline void SetID(unsigned char ucID)	{ m_ucID = ucID; }

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Push a Tile into the array of tiles
	//	Return		:	Index of tile just added
	////////////////////////////////////////////////////////////////////////
	inline unsigned int PushTile(CTile Tile)
	{
		// Push the tile
		m_vTiles.push_back(Tile);
		// Return size - 1 (since arrays are zero-based)
		return m_vTiles.size() - 1;
	}

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Pop last Tile from the array
	////////////////////////////////////////////////////////////////////////
	inline void PopTile(void)
	{
		m_vTiles.pop_back();
	}

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Clear the array of tiles
	////////////////////////////////////////////////////////////////////////
	inline void Clear(void)
	{
		m_vTiles.clear();
	}

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Get the size of the array of tiles
	////////////////////////////////////////////////////////////////////////
	inline unsigned int GetSize(void)
	{
		return m_vTiles.size();
	}

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Get a specific tile
	////////////////////////////////////////////////////////////////////////
	inline CTile* GetTile(unsigned int nIndex)
	{
		return &m_vTiles[nIndex];
	}

};

#endif // CLAYER_H_