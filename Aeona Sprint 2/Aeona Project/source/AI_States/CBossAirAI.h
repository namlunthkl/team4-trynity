#ifndef _CBossAirAI_H_
#define _CBossAirAI_H_

#include "IBaseAIState.h"

class CBossAirAI : public IBaseAIState
{
	// Trilogy for proper singleton
	CBossAirAI(const CBossAirAI&){}
	CBossAirAI* operator=(const CBossAirAI&){}
	~CBossAirAI(void){}
	CBossAirAI(void){}

	static CBossAirAI* sm_pInstance;
	float FireTime;
	//int m_sndLarvaHiss;

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