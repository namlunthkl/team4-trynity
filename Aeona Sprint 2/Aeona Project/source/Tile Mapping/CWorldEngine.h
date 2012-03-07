//    File Name				:	"CWorldEngine.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/13 - 8:40 PM
//    Purpose				:	Singleton that handles the loading
//								and storage of all the maps and
//								puzzles in the game
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef C_WORLD_ENGINE_H_
#define C_WORLD_ENGINE_H_

#include "CMap.h"

#define WORLD CWorldEngine::GetInstance()

// For CheckCollisions
class IBaseInterface;
// For event names
class CStringTable;

// WorldEngine class - proper singleton
class CWorldEngine
{
	//////////////////////////////////////////////////////////////////////////
	//	------------------------------------------------------------------	//
	//							DATA	MEMBERS								//
	//	------------------------------------------------------------------	//
	//////////////////////////////////////////////////////////////////////////

	//	Vector of maps
	vector<CMap*>			m_vpMaps;

	// Vector of tilesets
	vector<CTileset*>		m_vpTilesets;

	// Rectangle with screen area to render and check collisions
	RECT					m_rDrawArea;

	//	Static member pointer Instance - Singleton
	static CWorldEngine*	sm_pInstance;

	// String table - Used for event names
	CStringTable*	m_pStringTable;

	//////////////////////////////////////////////////////////////////////////
	//	------------------------------------------------------------------	//
	//							PRIVATE	FUNCTIONS							//
	//	------------------------------------------------------------------	//
	//////////////////////////////////////////////////////////////////////////

	//	Constructor
	CWorldEngine(void) {}

	//	Proper singleton needs the trilogy of evil
	//		Copy Constructor
	CWorldEngine(const CWorldEngine&) {}
	//		Assignment Operator
	CWorldEngine& operator=(const CWorldEngine&) {}
	//		Destructor
	~CWorldEngine(void) {}

	// Culling mode
	int m_nCullingMode;

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Load all maps defined in an XML File
	//	Parameters	:	szFilename: File that has all the maps' file names
	////////////////////////////////////////////////////////////////////////
	bool LoadAllMaps(const char* szFilename);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Get input that changes the maps
	////////////////////////////////////////////////////////////////////////
	void Input(void);

public:

	//////////////////////////////////////////////////////////////////////////
	//	------------------------------------------------------------------	//
	//							PUBLIC	FUNCTIONS							//
	//	------------------------------------------------------------------	//
	//////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Singleton's accessor
	////////////////////////////////////////////////////////////////////////
	static CWorldEngine* GetInstance(void);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Initialize all variables, call LoadAllMaps()
	////////////////////////////////////////////////////////////////////////
	void InitWorldEngine(void);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Updates all maps
	////////////////////////////////////////////////////////////////////////
	void UpdateWorld(float fElapsedTime);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Render all maps
	////////////////////////////////////////////////////////////////////////
	void RenderWorldBelowObjects(void);
	void RenderWorldAboveObjects(void);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Check collisions against all tiles on screen
	//	Parameters	:	pBase - Object that we're checking collisions with
	//	Return		:	True if collided, false otherwise
	////////////////////////////////////////////////////////////////////////
	bool CheckCollisions(IBaseInterface* pBase, RectD* CollisionRect = nullptr, unsigned int uiObjType = 0U);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Unload files
	////////////////////////////////////////////////////////////////////////
	void ShutdownWorldEngine(void);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Delete the singleton's instance
	////////////////////////////////////////////////////////////////////////
	static void DeleteInstance(void);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Get a pointer to a specific tileset
	//	Parameters	:	The wanted tileset's ID
	////////////////////////////////////////////////////////////////////////
	CTileset* GetTileset(unsigned char ucID);

	const char* GetMapWherePointIs(double dPositionX, double dPositionY);

	///////////
	// HACK
	///////////
	inline int GetWorldWidth(void)
	{ return INT_MAX; }//m_vpMaps[0]->GetWidth() * m_vpMaps[0]->GetTileset()->GetTileWidth(); }
	inline int GetWorldHeight(void)
	{ return INT_MAX; }//m_vpMaps[0]->GetHeight() * m_vpMaps[0]->GetTileset()->GetTileHeight(); }
};

#endif // C_WORLD_ENGINE_H_