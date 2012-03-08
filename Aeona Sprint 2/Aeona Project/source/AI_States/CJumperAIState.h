#ifndef C_JUMPER_AI_STATE_H_
#define C_JUMPER_AI_STATE_H_

#include "IBaseAIState.h"

class CJumperAIState : public IBaseAIState
{
	// Trilogy for proper singleton
	CJumperAIState(const CJumperAIState&){}
	CJumperAIState* operator=(const CJumperAIState&){}
	~CJumperAIState(void){}
	CJumperAIState(void){}

	static CJumperAIState* sm_pInstance;

	//	0 - hurt
	//	1 - hurt knocked back
	//	2 - wander
	//	3 - pause-before
	//	4 - leaping
	//	5 - pause-after
	
public:
	static IBaseAIState* GetInstance(void);
	void Enter(CBaseCharacter* pCharacter);
	void Update(CBaseCharacter* pCharacter, float fElapsedTime);
	void Exit(CBaseCharacter* pCharacter);
	static void DeleteInstance(void);
};

#endif