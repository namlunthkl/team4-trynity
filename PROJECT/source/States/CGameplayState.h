////////////////////////////////////////////////////////////////////////
//    File Name				:	"CGameplayState.h"
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09/12 - 1:00 AM
//    Purpose				:	Contains the GameplayState
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CGAMEPLAYSTATE_H_
#define CGAMEPLAYSTATE_H_

// Base state
#include "IGameState.h"

// Animation Engine
#include "../Animation/CAnimationManager.h"
#include "../Animation/CAnimationPlayer.h"
// World Engine
#include "../Tile Mapping/CWorldEngine.h"
#include "../Characters/TestPlayer.h"
// Particle Engine
#include "../Particle Engine/ParticleWeapon.h"

// Event System
#include "../Messaging/CEventSystem.h"
#include "../Messaging/IListener.h"

class CGameplayState : public IGameState , public IListener
{
	// JUST FOR TESTING
	TestPlayer* pPlayer;
	ParticleWeapon PW;

	//	Proper Singleton - needs trilogy of evil
	//		Copy Constructor
	CGameplayState(const CGameplayState&){}
	//		Assignment operator
	CGameplayState& operator=(const CGameplayState&){}
	//		Destructor
	~CGameplayState(void){}


public:

	// Constructor
	CGameplayState(void);

	// Initialize everything
	void Enter(void);

	// Get user input
	bool Input(void);

	// Update the world and the objects in the game
	void Update(float fElapsedTime);

	// Render the world and the objects in the game
	void Render(void);

	// Shutdown everything
	void Exit(void);

	// Singleton accessor
	static CGameplayState* GetInstance(void);

	// Handle events
	void HandleEvent(CEvent* pEvent);
};

#endif // CGAMEPLAYSTATE_H_