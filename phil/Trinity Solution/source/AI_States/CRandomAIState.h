////////////////////////////////////////////////////////////////////////
//    File Name				:	"CRandomAIState.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09/12 - 2:18 AM
//    Purpose				:	The Random AI State identifies a state
//								in which the enemy will move randomly
//								throughout the game world.
////////////////////////////////////////////////////////////////////////

#ifndef C_RANDOM_AI_STATE_H_
#define C_RANDOM_AI_STATE_H_

#include "IBaseAIState.h"

class CRandomAIState : public IBaseAIState
{
public:
	void Enter(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);
};

#endif // C_RANDOM_AI_STATE_H_