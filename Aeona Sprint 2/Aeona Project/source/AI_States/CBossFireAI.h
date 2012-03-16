#ifndef _CBossFireAI_H_
#define _CBossFireAI_H_

#include "IBaseAIState.h"

class CBossFireAI : public IBaseAIState
{
	// Trilogy for proper singleton
	CBossFireAI(const CBossFireAI&){}
	CBossFireAI* operator=(const CBossFireAI&){}
	~CBossFireAI(void){}
	CBossFireAI(void){}

	static CBossFireAI* sm_pInstance;
	float FireTime;

public:
	static IBaseAIState* GetInstance(void);
	void Enter(CBaseCharacter* pCharacter);
	void Update(CBaseCharacter* pCharacter, float fElapsedTime);
	void Exit(CBaseCharacter* pCharacter);
	static void DeleteInstance(void);
};

#endif