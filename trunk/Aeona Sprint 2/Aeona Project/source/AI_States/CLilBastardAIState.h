#ifndef C_LIL_BASTARD_AI_STATE_H_
#define C_LIL_BASTARD_AI_STATE_H_

#include "IBaseAIState.h"

class CLilBastardAIState : public IBaseAIState
{
	// Trilogy for proper singleton
	CLilBastardAIState(const CLilBastardAIState&){}
	CLilBastardAIState* operator=(const CLilBastardAIState&){}
	~CLilBastardAIState(void){}
	CLilBastardAIState(void){}

	static CLilBastardAIState* sm_pInstance;

	int m_sndLilBastardSnore;

	//	0 - GetWhacked
	//	1 - WhackedPause
	//	2 - Sweepyhead
	//	3 - nada
	//	4 - CalmDownDude
	//	5 - RandomLunge
	
public:
	static IBaseAIState* GetInstance(void);
	void Enter(CBaseCharacter* pCharacter);
	void Update(CBaseCharacter* pCharacter, float fElapsedTime);
	void Exit(CBaseCharacter* pCharacter);
	static void DeleteInstance(void);
};

#endif