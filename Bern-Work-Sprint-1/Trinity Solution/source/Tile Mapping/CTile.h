////////////////////////////////////////////////////////////////////////
//    File Name				:	"CTile.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/06 - 9:03 PM
//    Purpose				:	Tile class used for tile mapping
//
//    Last Updater Name		:	Name of last person who updated it
//    Last Update Date		:	month/day - hour:min (AM/PM)
//    Last Update Notes		:	Notes from the last person who updated it
//
//    Other Notes			:   Notes from other updates are moved here
//								when the file is updated again
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

public:
	// Constructor
	CTile(unsigned char ucPosX = 0, unsigned char ucPosY = 0, unsigned char ucID = 0)
	{
		SetPosX(ucPosX);
		SetPosY(ucPosY);
		SetID(ucID);
	}

	// Accessors
	inline unsigned char GetPosX(void)	{ return m_ucPosX; }
	inline unsigned char GetPosY(void)	{ return m_ucPosY; }
	inline unsigned char GetID(void)	{ return m_ucID; }

	// Mutators
	inline void SetPosY(unsigned char ucPosY)	{ m_ucPosY = ucPosY; }
	inline void SetPosX(unsigned char ucPosX)	{ m_ucPosX = ucPosX; }
	inline void SetID(unsigned char ucID)		{ m_ucID = ucID; }
};

#endif // CTILE_H_