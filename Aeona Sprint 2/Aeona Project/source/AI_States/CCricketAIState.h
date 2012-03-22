#ifndef C_CRICKET_AI_STATE_H_
#define C_CRICKET_AI_STATE_H_

#include "IBaseAIState.h"

class CCricketAIState : public IBaseAIState
{
	// Trilogy for proper singleton
	CCricketAIState(const CCricketAIState&){}
	CCricketAIState* operator=(const CCricketAIState&){}
	~CCricketAIState(void){}
	CCricketAIState(void){}

	static CCricketAIState* sm_pInstance;

	int m_sndLarvaHiss;

	//	0 - GetWhacked
	//	1 - WhackedPause
	//	2 - SittingStill
	//	3 - SquirmForward
	//	4 - SquirmPause
	//	5 - Lunge
	
public:
	static IBaseAIState* GetInstance(void);
	void Enter(CBaseCharacter* pCharacter);
	void Update(CBaseCharacter* pCharacter, float fElapsedTime);
	void Exit(CBaseCharacter* pCharacter);
	static void DeleteInstance(void);
};

#endif