////////////////////////////////////////////////////////////////////////
//    File Name				:	"CPuzzle.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09 - 12:43 AM
//    Purpose				:	Puzzle class used for puzzle behavior
//								handling
//
//    Last Updater Name		:	Name of last person who updated it
//    Last Update Date		:	month/day - hour:min (AM/PM)
//    Last Update Notes		:	Notes from the last person who updated it
//
//    Other Notes			:   Notes from other updates are moved here
//								when the file is updated again
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CPUZZLE_H_
#define CPUZZLE_H_

// Just for now...
class IListener;
class CEvent;

class CPuzzle //: public IListener
{
	// Number of arguments needed for the puzzle
	unsigned int m_uiArgCount;

	// Arguments used by the puzzle
	vector<int> m_vnArguments;

	// Event the puzzle is listening to
	char* m_szEvent;

	// Handle Event function pointer
	void(*m_pfHandleEvent)(void);

	// Update function pointer
	void(*m_pfUpdate)(void);

public:
	void HandleEvent(CEvent* pEvent);
	void Update(float fElapsedTime);
	void Initialize(unsigned int uiArgCount, char* szEvent,
		void(*pfHandleEvent)(void), void(*pfUpdate)(void));
};


#endif // CPUZZLE_H_