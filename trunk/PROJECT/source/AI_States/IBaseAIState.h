////////////////////////////////////////////////////////////////////////
//    File Name				:	"IBaseAIState.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09/12 - 2:18 AM
//    Purpose				:	Base abstract interface from which all
//								the AI states inherit
////////////////////////////////////////////////////////////////////////

#ifndef I_BASE_AI_STATE_H_
#define I_BASE_AI_STATE_H_

class IBaseAIState
{
public:
	virtual void Enter(void) = 0;
	virtual void Update(float fElapsedTime) = 0;
	virtual void Render(void) = 0;
	virtual void Exit(void) = 0;
};

#endif // I_BASE_AI_STATE_H_