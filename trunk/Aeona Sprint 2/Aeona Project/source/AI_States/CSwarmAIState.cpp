////////////////////////////////////////////////////////////////////////
//    File Name				:	"CSwarmAIState.cpp"
//
//    Author Name			:	Phil Sullivan
//    Creation Date			:	03/1 - 11:50 PM
//    Purpose				:	The Random AI State identifies a state
//								in which the enemy will charge at the
//								player when he's nearby.
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "CSwarmAIState.h"
#include "../Game Objects/CPlayer.h"

// Singleton's instance
CSwarmAIState* CSwarmAIState::sm_pInstance = NULL;

IBaseAIState* CSwarmAIState::GetInstance(void)
{
	if(!sm_pInstance)
		sm_pInstance = new CSwarmAIState();

	return sm_pInstance;
}

void CSwarmAIState::DeleteInstance(void)
{
	if(sm_pInstance != NULL)
	{
		delete sm_pInstance;
		sm_pInstance = NULL;
	}
}

void CSwarmAIState::Enter(CBaseCharacter* pCharacter)
{
	pCharacter->SetVelY(0 * pCharacter->GetSpeed());
	pCharacter->SetVelX(0 * pCharacter->GetSpeed());
	pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_RIGHT);
}

void CSwarmAIState::Update(CBaseCharacter* pCharacter, float fElapsedTime)
{
	float fMoveTimer = pCharacter->GetMoveTimer();

	if(fMoveTimer < 0.0f)
		fMoveTimer = 0.0f;
	if(pCharacter->GetVelX() != 0 && pCharacter->GetVelY() != 0)	//	If we are moving
	{
		fMoveTimer += fElapsedTime;
		if(fMoveTimer >= 3.0f)
		{
			fMoveTimer = 0.0f;			//	Stop us now
			pCharacter->SetVelX(0);
			pCharacter->SetVelY(0);
		}
	}
	else		//	but if we are NOT moving...
	{
		fMoveTimer += fElapsedTime;	//	use the same timer, but now we're waiting for a bigger time
		if(fMoveTimer >= 0.6f)
		{
			fMoveTimer = 0.0f;

			if( CPlayer::GetInstance()->GetPosY() > pCharacter->GetPosY() )
			{
				pCharacter->SetVelY( 3.0f * pCharacter->GetSpeed() );
			}
			else if( CPlayer::GetInstance()->GetPosY() < pCharacter->GetPosY() )
			{
				pCharacter->SetVelY( -3.0f * pCharacter->GetSpeed() );
			}
			else
			{
				pCharacter->SetVelY( 0.0f );
			}

			if( CPlayer::GetInstance()->GetPosX() > pCharacter->GetPosX() )
			{
				pCharacter->SetVelX( 3.0f * pCharacter->GetSpeed() );
			}
			else if( CPlayer::GetInstance()->GetPosX() < pCharacter->GetPosX() )
			{
				pCharacter->SetVelX( -3.0f * pCharacter->GetSpeed() );
			}
			else
			{
				pCharacter->SetVelX( 0.0f );
			}

			//if(RandVelY > 0)
			//	pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_DOWN);
			//else
			//	pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_UP);

			//if(RandVelX > 0)
			//	pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_RIGHT);
			//else if(RandVelX < 0)
			//	pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_LEFT);
		}
		else	//	if the timer is not yet 2.0f
		{
			// nothing; we are waiting still.
		}
	}

	pCharacter->SetMoveTimer(fMoveTimer);
}

void CSwarmAIState::Exit(CBaseCharacter* pCharacter)
{

}
