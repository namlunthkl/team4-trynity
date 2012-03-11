#ifndef C_LARVA_AI_STATE_H_
#define C_LARVA_AI_STATE_H_

#include "IBaseAIState.h"

class CLarvaAIState : public IBaseAIState
{
	// Trilogy for proper singleton
	CLarvaAIState(const CLarvaAIState&){}
	CLarvaAIState* operator=(const CLarvaAIState&){}
	~CLarvaAIState(void){}
	CLarvaAIState(void){}

	static CLarvaAIState* sm_pInstance;

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