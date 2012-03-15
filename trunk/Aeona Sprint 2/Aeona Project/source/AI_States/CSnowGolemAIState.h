#ifndef C_SNOWGOLEM_AI_STATE_H_
#define C_SNOWGOLEM_AI_STATE_H_

#include "IBaseAIState.h"

class CSnowGolemAIState : public IBaseAIState
{
	// Trilogy for proper singleton
	CSnowGolemAIState(const CSnowGolemAIState&){}
	CSnowGolemAIState* operator=(const CSnowGolemAIState&){}
	~CSnowGolemAIState(void){}
	CSnowGolemAIState(void){}

	static CSnowGolemAIState* sm_pInstance;

	int m_sndRockRoll;

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