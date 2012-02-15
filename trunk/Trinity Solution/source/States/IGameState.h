////////////////////////////////////////////////////////////////////////
//    File Name				:	"IGameState.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/06 - 8:50 PM
//    Purpose				:	Interface for game states
//
//    Last Updater Name		:	Name of last person who updated it
//    Last Update Date		:	month/day - hour:min (AM/PM)
//    Last Update Notes		:	Notes from the last person who updated it
//
//    Other Notes			:   Notes from other updates are moved here
//								when the file is updated again
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef IGAMESTATE_H_
#define IGAMESTATE_H_

// IGameState class
// Pure virtual interface that states to inherit from
class IGameState
{
	// Every state will need at least one background music
	int m_musBGM;

	// Every state will need at least one image for the font
	int m_imgFont;

	// Every state will need at least one image for the cursor
	int m_imgCursor;

public:
	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Initialize state's variables
	////////////////////////////////////////////////////////////////////////
	virtual void Enter(void) = 0;

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Get user input
	//	Return		:	True if game should continue running
	//					False if game should quit
	////////////////////////////////////////////////////////////////////////
	virtual bool Input(void) = 0;

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Update state's variables
	////////////////////////////////////////////////////////////////////////
	virtual void Update(float fElapsedTime) = 0;

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Draw to the screen
	////////////////////////////////////////////////////////////////////////
	virtual void Render(void) = 0;

	////////////////////////////////////////////////////////////////////////
	//	Purpose		:	Clean up dynamically allocated memory
	////////////////////////////////////////////////////////////////////////
	virtual void Exit(void) = 0;
	
protected:
	virtual ~IGameState() = 0 {}
};

#endif // IGAMESTATE_H_