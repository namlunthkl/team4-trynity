////////////////////////////////////////////////////////////////////////
//    File Name				:	"CRandomAIState.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/27 - 6:56 PM
//    Purpose				:	The Random AI State identifies a state
//								in which the enemy will move randomly
//								throughout the game world.
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "CRandomAIState.h"

// Singleton's instance
CRandomAIState* CRandomAIState::sm_pInstance = NULL;

IBaseAIState* CRandomAIState::GetInstance(void)
{
	if(!sm_pInstance)
		sm_pInstance = new CRandomAIState();

	return sm_pInstance;
}

void CRandomAIState::DeleteInstance(void)
{
	if(sm_pInstance != NULL)
	{
		delete sm_pInstance;
		sm_pInstance = NULL;
	}
}

void CRandomAIState::Enter(CBaseCharacter* pCharacter)
{
	pCharacter->SetVelY(1.0f * (float)pCharacter->GetSpeed());
	pCharacter->SetVelX(1.0f * (float)pCharacter->GetSpeed());
	pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_RIGHT);
}

void CRandomAIState::Update(CBaseCharacter* pCharacter, float fElapsedTime)
{
	float fMoveTimer = pCharacter->GetMoveTimer();

	if(fMoveTimer < 0.0f)
		fMoveTimer = 0.0f;
	if(pCharacter->GetVelX() != 0 && pCharacter->GetVelY() != 0)
	{
		fMoveTimer += fElapsedTime;
		if(fMoveTimer >= 1.0f)
		{
			fMoveTimer = 0.0f;
			pCharacter->SetVelX(0);
			pCharacter->SetVelY(0);
		}
	}
	else
	{
		fMoveTimer += fElapsedTime;
		if(fMoveTimer >= 2.0f)
		{
			fMoveTimer = 0.0f;

			float RandVelY = (float)(rand() % 3 - 1);
			pCharacter->SetVelY(RandVelY * pCharacter->GetSpeed());
			if(RandVelY > 0)
				pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_DOWN);
			else
				pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_UP);

			float RandVelX = (float)(rand() % 3 - 1);
			pCharacter->SetVelX(RandVelX * pCharacter->GetSpeed());

			if(RandVelX > 0)
				pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_RIGHT);
			else if(RandVelX < 0)
				pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_LEFT);
		}
		else
		{
			// nothing; we are waiting still.
			int x = 0;
		}
	}

	pCharacter->SetMoveTimer(fMoveTimer);
}

void CRandomAIState::Exit(CBaseCharacter* pCharacter)
{

}
