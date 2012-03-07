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

#include "../Messaging/CEventSystem.h"
#include "../Messaging/IListener.h"
#include "../Particle Engine/ParticleWeapon.h"
#include "../Tile Mapping/CWorldEngine.h"
#include <vector>
using std::vector;

class IBasePuzzle : public IListener
{
protected:
	// Number of arguments this puzzle is using
	unsigned int m_uiArgCount;
	// Vector of those arguments
	vector<int> m_vnArguments;

	// Event the puzzle will fire when complete
	char* m_szEventToFire;
	// Prefix name for all the events this puzzle is listening to
	char* m_szEventToListenTo;

	// Timer
	// When a torch is lit, there should be a little time
	// before the player is able to unlit it.
	DWORD m_dwTimeStamp;

	// Sequential
	// Should the puzzle only be complete when all the actions
	// are done in a right order?
	bool m_bSequential;

public:
	IBasePuzzle(void){};
	virtual void Create(unsigned int uiArgCount, char* szEventToFire, char* szEventToListenTo, bool bSequential);
	virtual void Update(float fElapsedTime) = 0;
	virtual void Render(void) = 0;
	virtual void Destroy(void) = 0;
	virtual void EventReceived(int ArgumentNumber, void* EventData);
	void HandleEvent(CEvent* pEvent);
	virtual void TryFiringEvent(void);
	int GetNumberOfArgumentsOn(void);
};

#endif // CPUZZLE_H_