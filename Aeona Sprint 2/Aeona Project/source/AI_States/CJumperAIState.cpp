#include "StdAfx.h"
#include "CJumperAIState.h"
#include "../Game Objects/CPlayer.h"

// Singleton's instance
CJumperAIState* CJumperAIState::sm_pInstance = NULL;

IBaseAIState* CJumperAIState::GetInstance(void)
{
	if(!sm_pInstance)
		sm_pInstance = new CJumperAIState();

	return sm_pInstance;
}

void CJumperAIState::DeleteInstance(void)
{
	if(sm_pInstance != NULL)
	{
		delete sm_pInstance;
		sm_pInstance = NULL;
	}
}

void CJumperAIState::Enter(CBaseCharacter* pCharacter)
{
	pCharacter->SetVelY(1.0f * (float)pCharacter->GetSpeed());
	pCharacter->SetVelX(1.0f * (float)pCharacter->GetSpeed());
	pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_RIGHT);
}

void CJumperAIState::Update(CBaseCharacter* pCharacter, float fElapsedTime)
{
	float fMoveTimer = pCharacter->GetMoveTimer();

	if(fMoveTimer < 0.0f)
		fMoveTimer = 0.0f;
	if(pCharacter->GetVelX() != 0 && pCharacter->GetVelY() != 0)
	{
		fMoveTimer += fElapsedTime;
		if(fMoveTimer >= 0.5f)
		{
			fMoveTimer = 0.0f;
			pCharacter->SetVelX( 0.0f );
			pCharacter->SetVelY( 0.0f );
		}
	}
	else
	{
		fMoveTimer += fElapsedTime;
		if(fMoveTimer >= 3.0f)
		{
			fMoveTimer = 0.0f;

			if( CPlayer::GetInstance()->GetPosY() > pCharacter->GetPosY() )
			{
				pCharacter->SetVelY( 5.0f * pCharacter->GetSpeed() );
			}
			else if( CPlayer::GetInstance()->GetPosY() < pCharacter->GetPosY() )
			{
				pCharacter->SetVelY( -5.0f * pCharacter->GetSpeed() );
			}
			else
			{
				pCharacter->SetVelY( 0.0f );
			}

			if( CPlayer::GetInstance()->GetPosX() > pCharacter->GetPosX() )
			{
				pCharacter->SetVelX( 5.0f * pCharacter->GetSpeed() );
			}
			else if( CPlayer::GetInstance()->GetPosX() < pCharacter->GetPosX() )
			{
				pCharacter->SetVelX( -5.0f * pCharacter->GetSpeed() );
			}
			else
			{
				pCharacter->SetVelX( 0.0f );
			}
		}
		else
		{
			// nothing; we are waiting still.
			int x = 0;
		}
	}

	pCharacter->SetMoveTimer(fMoveTimer);
}

void CJumperAIState::Exit(CBaseCharacter* pCharacter)
{

}
