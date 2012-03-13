#ifndef C_SPIDER_AI_STATE_H_
#define C_SPIDER_AI_STATE_H_

#include "IBaseAIState.h"

class CSpiderAIState : public IBaseAIState
{
	// Trilogy for proper singleton
	CSpiderAIState(const CSpiderAIState&){}
	CSpiderAIState* operator=(const CSpiderAIState&){}
	~CSpiderAIState(void){}
	CSpiderAIState(void){}

	static CSpiderAIState* sm_pInstance;

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