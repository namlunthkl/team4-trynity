////////////////////////////////////////////////////////////////////////
//    File Name				:	"CTile.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/06 - 9:03 PM
//    Purpose				:	Tile class used for tile mapping
//
//    Last Updater Name		:	Daniel Lima
//    Last Update Date		:	02/16 - 1:00 AM
//    Last Update Notes		:	- Char for the event added
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CTILE_H_
#define CTILE_H_

// CTile class
// Defines a tile based on a position in a tileset and an ID
class CTile
{
	// Position of this tile's graphic in a tileset
	unsigned char m_ucPosX;
	unsigned char m_ucPosY;

	// ID of this tile - represents tile type
	unsigned char m_ucID;

	// Event ID - an index in the map's string table
	// that represents the event that will be fired
	// when colliding or interacting with this tile
	unsigned char m_ucEventID;

public:
	// Constructor
	CTile(unsigned char ucPosX = 0, unsigned char ucPosY = 0, unsigned char ucID = 0, unsigned char ucEventID = 0)
	{
		SetPosX(ucPosX);
		SetPosY(ucPosY);
		SetID(ucID);
		SetEventID(ucEventID);
	}

	// Accessors
	inline unsigned char GetPosX(void)	{ return m_ucPosX; }
	inline unsigned char GetPosY(void)	{ return m_ucPosY; }
	inline unsigned char GetID(void)	{ return m_ucID; }
	inline unsigned char GetEventID(void) { return m_ucEventID; }

	// Mutators
	inline void SetPosY(unsigned char ucPosY)	{ m_ucPosY = ucPosY; }
	inline void SetPosX(unsigned char ucPosX)	{ m_ucPosX = ucPosX; }
	inline void SetID(unsigned char ucID)		{ m_ucID = ucID; }
	inline void SetEventID(unsigned char ucEventID) { m_ucEventID = ucEventID; }
};

#endif // CTILE_H_