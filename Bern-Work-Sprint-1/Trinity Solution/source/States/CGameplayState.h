////////////////////////////////////////////////////////////////////////
//    File Name				:	"CGameplayState.h"
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09/12 - 1:00 AM
//    Purpose				:	Contains the GameplayState
////////////////////////////////////////////////////////////////////////

#ifndef CGAMEPLAYSTATE_H_
#define CGAMEPLAYSTATE_H_

#include "IGameState.h"
#include "..\Tile Mapping\CMap.h"
#include "..\Animation\CAnimationPlayer.h"
#include "../Messaging/IListener.h"
#include "../Characters/TestPlayer.h"

class CGameplayState : public IGameState , public IListener
{
	vector<CMap> m_vMaps;
	CAnimationPlayer* WalkUp;
	CAnimationPlayer* WalkDown;
	CAnimationPlayer* WalkRight;
	CAnimationPlayer* WalkLeft;
	float bucket;

	// JUST FOR TESTING
	TestPlayer* pPlayer;
public:
	CGameplayState(void);
	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);
	static CGameplayState* GetInstance(void);
	void HandleEvent(CEvent* pEvent);
};

#endif // CGAMEPLAYSTATE_H_