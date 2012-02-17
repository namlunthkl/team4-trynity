////////////////////////////////////////////////////////////////////////
//    File Name				:	"CIdleAIState.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09/12 - 2:18 AM
//    Purpose				:	The Idle AI State identifies a state in
//								which the enemy won't move at all.
////////////////////////////////////////////////////////////////////////

#ifndef C_IDLE_AI_STATE_H_
#define C_IDLE_AI_STATE_H_

#include "IBaseAIState.h"

class CIdleAIState : public IBaseAIState
{
public:
	void Enter(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);
};

#endif // C_IDLE_AI_STATE_H_