////////////////////////////////////////////////////////////////////////
//    File Name				:	"IBaseAIState.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09/12 - 2:18 AM
//    Purpose				:	Base abstract interface from which all
//								the AI states inherit
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef I_BASE_AI_STATE_H_
#define I_BASE_AI_STATE_H_

// The object the AI will be controlling
#include "../Game Objects/CBaseCharacter.h"

class IBaseAIState
{
public:
	virtual void Enter(CBaseCharacter* pCharacter) = 0;
	virtual void Update(CBaseCharacter* pCharacter, float fElapsedTime) = 0;
	virtual void Exit(CBaseCharacter* pCharacter) = 0;
};

#endif // I_BASE_AI_STATE_H_