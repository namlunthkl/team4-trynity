////////////////////////////////////////////////////////////////////////
//    File Name				:	"CTileset.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/06 - 9:05 PM
//    Purpose				:	Tileset class used for tile mapping
//
//    Last Updater Name		:	Name of last person who updated it
//    Last Update Date		:	month/day - hour:min (AM/PM)
//    Last Update Notes		:	Notes from the last person who updated it
//
//    Other Notes			:   Notes from other updates are moved here
//								when the file is updated again
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CTILESET_H_
#define CTILESET_H_

// CTileset class
// Defines an image id and a size for a tileset
class CTileset
{
	// Image ID for the Tileset
	int m_imgTilesetID;

	// Size of the whole tileset, in number of tiles
	unsigned char m_ucWidth;
	unsigned char m_ucHeight;

	// Size of each tile in this tileset, in pixels
	unsigned char m_ucTileWidth;
	unsigned char m_ucTileHeight;

public:
	// Constructor
	CTileset(int imgTilesetID = -1, unsigned char ucWidth = 0, unsigned char ucHeight = 0,
		unsigned char ucTileWidth = 0, unsigned char ucTileHeight = 0)
	{
		SetImageID(imgTilesetID);
		SetWidth(ucWidth);
		SetHeight(ucHeight);
		SetTileWidth(ucTileWidth);
		SetTileHeight(ucTileHeight);
	}

	// Accessors
	inline int				GetImageID(void)		{ return m_imgTilesetID; }
	inline unsigned char	GetWidth(void)			{ return m_ucWidth; }
	inline unsigned char	GetHeight(void)			{ return m_ucHeight; }
	inline unsigned char	GetTileWidth(void)		{ return m_ucTileWidth; }
	inline unsigned char	GetTileHeight(void)		{ return m_ucTileHeight; }

	// Mutators
	inline void SetImageID(int imgTilesetID)				{ m_imgTilesetID = imgTilesetID; }
	inline void SetWidth(unsigned char ucWidth)				{ m_ucWidth = ucWidth; }
	inline void SetHeight(unsigned char ucHeight)			{ m_ucHeight = ucHeight; }
	inline void SetTileWidth(unsigned char ucTileWidth)		{ m_ucTileWidth = ucTileWidth; }
	inline void SetTileHeight(unsigned char ucTileHeight)	{ m_ucTileHeight = ucTileHeight; }
};

#endif // CTILESET_H_