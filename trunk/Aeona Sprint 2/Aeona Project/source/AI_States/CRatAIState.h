#ifndef C_RAT_AI_STATE_H_
#define C_RAT_AI_STATE_H_

#include "IBaseAIState.h"

class CRatAIState : public IBaseAIState
{
	// Trilogy for proper singleton
	CRatAIState(const CRatAIState&){}
	CRatAIState* operator=(const CRatAIState&){}
	~CRatAIState(void){}
	CRatAIState(void){}

	static CRatAIState* sm_pInstance;

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