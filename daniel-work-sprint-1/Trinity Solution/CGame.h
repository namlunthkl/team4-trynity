////////////////////////////////////////////////////////////////////////
//    File Name				:	"CGame.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/06 - 10:45 AM
//    Purpose				:	To contain all basic game-related data
//								and code, even though it just calls
//								a lot of functions from other classes
//
//    Last Updater Name		:	Name of last person who updated it
//    Last Update Date		:	month/day - hour:min (AM/PM)
//    Last Update Notes		:	Notes from the last person who updated it
//
//    Other Notes			:   Notes from other updates are moved here
//								when the file is updated again
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CGAME_H_
#define CGAME_H_

#include "States\IGameState.h"

// Timer class for game timing
#include "CTimer.h"

// Game class
// Proper singleton
class CGame
{
	//////////////////////////////////////////////////////////////////////////
	//	------------------------------------------------------------------	//
	//							DATA	MEMBERS								//
	//	------------------------------------------------------------------	//
	//////////////////////////////////////////////////////////////////////////
	
	//	Store window parameters when window is creates
	//	just in case you need them for any reason
	HWND			m_hWnd;
	short			m_sScreenWidth;
	short			m_sScreenHeight;
	bool			m_bIsWindowed;

	//	Game's current state
	IGameState*		m_pCurrentState;

	//	Timer - FPS, Game Time, Elapsed Time
	CTimer			m_Timer;

#if 0
	// HACK: Map creation testing
	CMap a;
#endif

	//////////////////////////////////////////////////////////////////////////
	//	------------------------------------------------------------------	//
	//							PRIVATE	FUNCTIONS							//
	//	------------------------------------------------------------------	//
	//////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Call the current state's Input method and exit the
	//					game if needed (Escape pressed in main menu, for
	//					example)
	//	Return		:	True if game should continue running
	//					False if game should quit
	////////////////////////////////////////////////////////////////////////
	bool Input(void);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Call the current state's Update method, thus
	//					updating the game independent of each state it's in
	////////////////////////////////////////////////////////////////////////
	void Update(void);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Call the current state's Render method, thus
	//					rendering the game independent of each state it's in
	////////////////////////////////////////////////////////////////////////
	void Render(void);

public:
	//////////////////////////////////////////////////////////////////////////
	//	------------------------------------------------------------------	//
	//							PUBLIC	FUNCTIONS							//
	//	------------------------------------------------------------------	//
	//////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Singleton's accessor
	//	Return		:	Pointer to the singleton's instance
	////////////////////////////////////////////////////////////////////////
	static CGame* GetInstance(void);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Initialize the game using window's parameters
	//	Parameters	:	hWnd - Window handle, hInstance - Instance handle,
	//					bIsWindowed - False means full screen
	//	Return		:	False if initialization failed, true if succeeded
	////////////////////////////////////////////////////////////////////////
	bool Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth,
		int nScreenHeight, bool bIsWindowed);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Run the game - call Input(), Update() and Render()
	//					Also time the game to call Update with fElapsedTime
	//	Return		:	True if game should continue running
	//					False if game should quit
	////////////////////////////////////////////////////////////////////////
	bool Main(void);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Shutdown everything that was initialized
	////////////////////////////////////////////////////////////////////////
	void Shutdown(void);

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Shutdown the game's current state, set the pointer
	//					to pNewState and initialize it
	//	Parameters	:	pNewState - pointer to new state's instance
	////////////////////////////////////////////////////////////////////////
	void ChangeState(IGameState* pNewState);

	//////////////////////////////////////////////////////////////////////////
	//	------------------------------------------------------------------	//
	//						ACCESSORS AND MUTATORS							//
	//	------------------------------------------------------------------	//
	//////////////////////////////////////////////////////////////////////////

public:
	inline short		GetScreenWidth	(void)					{ return m_sScreenWidth; }
	inline short		GetScreenHeight	(void)					{ return m_sScreenHeight; }

private:
	inline HWND			GetWindowHandle	(void)					{ return m_hWnd; }
	inline bool			GetIsWindowed	(void)					{ return m_bIsWindowed; }
	inline IGameState*	GetCurrentState	(void)					{ return m_pCurrentState; }
	inline CTimer		GetTimer		(void)					{ return m_Timer; }
	
	inline void			SetWindowHandle	(HWND hWnd)				{ m_hWnd = hWnd; }
	inline void			SetScreenWidth	(short sScreenWidth)	{ m_sScreenWidth = sScreenWidth; }
	inline void			SetScreenHeight	(short sScreenHeight)	{ m_sScreenHeight = sScreenHeight; }
	inline void			SetIsWindowed	(bool bIsWindowed)		{ m_bIsWindowed = bIsWindowed; }
};



#endif // CGAME_H_