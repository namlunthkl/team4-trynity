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
public:
	void Enter(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);
};

#endif // C_SWARM_AI_STATE_H_