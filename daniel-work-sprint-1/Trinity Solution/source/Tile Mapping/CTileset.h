////////////////////////////////////////////////////////////////////////
//    File Name				:	"CTileset.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/06 - 9:05 PM
//    Purpose				:	Tileset class used for tile mapping
//
//    Last Updater Name		:	Daniel Lima
//    Last Update Date		:	02/16 - 12:30 AM
//    Last Update Notes		:	- CPP File created
//								- Load function written and tested
//								- ID member added
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

	// ID used for maps to connect with tilesets
	unsigned char m_ucID;

public:
	// Constructor
	CTileset(void);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Load tileset information from a xml file
	//	Parameters	:	Location of the xml file to load
	//	Return		:	False if load failed, true if succeeded
	////////////////////////////////////////////////////////////////////////
	bool Load(const char const * szFilename);

	// Accessors
	inline int				GetImageID		(void)	const					{ return m_imgTilesetID; }
	inline unsigned char	GetWidth		(void)	const					{ return m_ucWidth; }
	inline unsigned char	GetHeight		(void)	const					{ return m_ucHeight; }
	inline unsigned char	GetTileWidth	(void)	const					{ return m_ucTileWidth; }
	inline unsigned char	GetTileHeight	(void)	const					{ return m_ucTileHeight; }
	inline unsigned char	GetID			(void)	const					{ return m_ucID; }

	// We're not using mutators anywhere else right now',
	// so let's just keep them private
private:
	// Mutators
	inline void				SetImageID		(int imgTilesetID)				{ m_imgTilesetID = imgTilesetID; }
	inline void				SetWidth		(unsigned char ucWidth)			{ m_ucWidth = ucWidth; }
	inline void				SetHeight		(unsigned char ucHeight)		{ m_ucHeight = ucHeight; }
	inline void				SetTileWidth	(unsigned char ucTileWidth)		{ m_ucTileWidth = ucTileWidth; }
	inline void				SetTileHeight	(unsigned char ucTileHeight)	{ m_ucTileHeight = ucTileHeight; }
	inline void				SetID			(unsigned char ucID)			{ m_ucID = ucID; }
};

#endif // CTILESET_H_