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
#include "../Game Objects/TestPlayer.h"
// Particle Engine
#include "../Particle Engine/ParticleWeapon.h"

// Event System
#include "../Messaging/CEventSystem.h"
#include "../Messaging/IListener.h"
#include "../Messaging/CMessageSystem.h"

#include "../Game Objects/CEnemy.h"

#define SCREEN_POS_X(X) CGameplayState::GetInstance()->GetScreenPositionX(X)
#define SCREEN_POS_Y(Y) CGameplayState::GetInstance()->GetScreenPositionY(Y)

class CGameplayState : public IGameState , public IListener
{
	// JUST FOR TESTING
	TestPlayer* pPlayer;
	CEnemy* pNPC;
	CEnemy* pEnemy;
	ParticleWeapon PW;
	ParticleWeapon m_Rain;
	//	Proper Singleton - needs trilogy of evil
	//		Copy Constructor
	CGameplayState(const CGameplayState&){}
	//		Assignment operator
	CGameplayState& operator=(const CGameplayState&){}
	//		Destructor
	~CGameplayState(void){}

	// Simple camera system
	int m_nCameraPosX;
	int m_nCameraPosY;


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

	// Message Proc for messaging system
	static void MessageProc(CBaseMessage* pMsg);

	// Singleton accessor
	static CGameplayState* GetInstance(void);

	// Handle events
	void HandleEvent(CEvent* pEvent);

	// Those are going to be used by all objects so that
	// they are placed in the screen in a position
	// relative to the camera position
	inline int GetScreenPositionX(int nPosX)
	{ return nPosX - m_nCameraPosX; }

	inline int GetScreenPositionY(int nPosY)
	{ return nPosY - m_nCameraPosY; }

	inline int GetWorldPositionX(int nPosX)
	{ return nPosX + m_nCameraPosX; }

	inline int GetWorldPositionY(int nPosY)
	{ return nPosY + m_nCameraPosY; }
};

#endif // CGAMEPLAYSTATE_H_