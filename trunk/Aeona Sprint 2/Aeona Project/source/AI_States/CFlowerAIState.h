#ifndef C_FLOWER_AI_STATE_H_
#define C_FLOWER_AI_STATE_H_

#include "IBaseAIState.h"

class CFlowerAIState : public IBaseAIState
{
	// Trilogy for proper singleton
	CFlowerAIState(const CFlowerAIState&){}
	CFlowerAIState* operator=(const CFlowerAIState&){}
	~CFlowerAIState(void){}
	CFlowerAIState(void){}

	static CFlowerAIState* sm_pInstance;

	int m_sndSlimeBlurb;

	//	0 - GetWhacked
	//	1 - WhackedPause
	//	2 - PassiveWander =)
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