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

#include "../ByteUtil.h"

// CTile class
// Defines a tile based on a position in a tileset and an ID
class CTile
{
	// Position of this tile's graphic in a tileset
	unsigned char m_ucPosX;
	unsigned char m_ucPosY;

	// ID of this tile - represents tile type
	Byte m_byteInfo;

	// Event ID - an index in the map's string table
	// that represents the event that will be fired
	// when colliding or interacting with this tile
	unsigned char m_ucEventID;

public:
	// Constructor
	CTile(unsigned char ucPosX = 0, unsigned char ucPosY = 0, Byte byteInfo = 0, unsigned char ucEventID = 0)
	{
		SetPosX(ucPosX);
		SetPosY(ucPosY);
		SetInfo(byteInfo);
		SetEventID(ucEventID);
	}

	// Accessors
	inline unsigned char GetPosX(void)	{ return m_ucPosX; }
	inline unsigned char GetPosY(void)	{ return m_ucPosY; }
	inline unsigned char GetEventID(void) { return m_ucEventID; }
	inline Byte GetInfo(void) { return m_byteInfo; }

	// Mutators
	inline void SetPosY(unsigned char ucPosY)	{ m_ucPosY = ucPosY; }
	inline void SetPosX(unsigned char ucPosX)	{ m_ucPosX = ucPosX; }
	inline void SetEventID(unsigned char ucEventID) { m_ucEventID = ucEventID; }
	inline void SetInfo(Byte byteInfo) { m_byteInfo = byteInfo; }
};

#endif // CTILE_H_