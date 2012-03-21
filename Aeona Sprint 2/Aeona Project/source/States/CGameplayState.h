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
// Particle Engine
#include "../Particle Engine/ParticleWeapon.h"


// Event System
#include "../Messaging/CEventSystem.h"
#include "../Messaging/IListener.h"
#include "../Messaging/CMessageSystem.h"

#include "../Game Objects/CEnemy.h"

// #define SCREEN_POS_X(X) CGameplayState::GetInstance()->GetScreenPositionX(X)
// #define SCREEN_POS_Y(Y) CGameplayState::GetInstance()->GetScreenPositionY(Y)
// #define WORLD_POS_X(X)	CGameplayState::GetInstance()->GetWorldPositionX(X)
// #define WORLD_POS_Y(Y)	CGameplayState::GetInstance()->GetWorldPositionY(Y)

class CGameplayState : public IGameState , public IListener
{
	// ParticleWeapon PW;

	//	Proper Singleton - needs trilogy of evil
	//		Copy Constructor
	CGameplayState(const CGameplayState&) {}
	//		Assignment operator
	CGameplayState& operator=(const CGameplayState&) {}
	//		Destructor
	~CGameplayState(void) {}

	//	Image for the HUD
	int m_imgHUD;
	int m_imgInventory;

	//	Variables used to draw the message box to the screen
	bool			m_bNPCTalking;
	int				m_imgMessageBox;
	CBitmapFont*	m_pFont;
	//		Name of the speaking NPC
	string			m_szCharName;
	//		Message the NPC is speaking
	string			m_szCurrentMessage;
	//		Selected option
	string			m_szCurrentOption;
	//		Function to actually render the message box
	void RenderMessageBox(void);

	// Game over screens
	bool	m_bVictory;
	bool	m_bGameOver;
	int		m_nGameOverID;
	int		m_nVictoryID;

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
	
	// Render the HUD in a separate function
	void RenderHUD(void);
	void RenderInventory(void);
	void RenderGameOverScreens(void);
	// Shutdown everything
	void Exit(void);

	// Message Proc for messaging system
	static void MessageProc(CBaseMessage* pMsg);

	// Singleton accessor
	static CGameplayState* GetInstance(void);

	// Handle events
	void HandleEvent(CEvent* pEvent);

	void SetMessageBox(bool bNPCTalking, string szCharName = "",
		string szCurrentMessage = "", string szCurrentOption = "");

	string BreakDownStrings(string szString, int nMin, int nMax);

	//	HEART ANIMATION TIMER?!
	float m_fHeartTimer;

};

#endif // CGAMEPLAYSTATE_H_