////////////////////////////////////////////////////////////////////////
//    File Name				:	"CSwarmAIState.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09/12 - 2:18 AM
//    Purpose				:	The Swarm AI State identifies a state in
//								which the enemy will look for the player
//								and follow him.
////////////////////////////////////////////////////////////////////////

#ifndef C_SWARM_AI_STATE_H_
#define C_SWARM_AI_STATE_H_

#include "IBaseAIState.h"

class CSwarmAIState : public IBaseAIState
{
	// Trilogy for proper singleton
	CSwarmAIState(const CSwarmAIState&){}
	CSwarmAIState* operator=(const CSwarmAIState&){}
	~CSwarmAIState(void){}
	CSwarmAIState(void){}

	static CRandomAIState* sm_pInstance;

public:
	static IBaseAIState* GetInstance(void);
	void Enter(CBaseCharacter* pCharacter);
	void Update(CBaseCharacter* pCharacter, float fElapsedTime);
	void Exit(CBaseCharacter* pCharacter);
	static void DeleteInstance(void);
};

#endif // C_SWARM_AI_STATE_H_