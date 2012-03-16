#include "StdAfx.h"
#include "CBossDaggerAI.h"
#include "../Game Objects/CPlayer.h"
CBossDaggerAI* CBossDaggerAI::sm_pInstance = NULL;

IBaseAIState* CBossDaggerAI::GetInstance(void)
{
	if(!sm_pInstance)
		sm_pInstance = new CBossDaggerAI();
	return sm_pInstance;
}

void CBossDaggerAI::DeleteInstance(void)
{
	if(sm_pInstance != NULL)
	{
		delete sm_pInstance;
		sm_pInstance = NULL;
	}
}

void CBossDaggerAI::Enter(CBaseCharacter* pCharacter)
{
	pCharacter->SetVelY( 0 );
	pCharacter->SetVelX( 0 );
	pCharacter->SetPrevVelX( 0 );
	pCharacter->SetPrevVelY( 0 );

	pCharacter->SetMoveTimer( 0.0f );
	pCharacter->SetMiniState(2);
	pCharacter->SetBehavior(0);
	pCharacter->philEnemyColor = D3DCOLOR_XRGB(255, 255, 255);

	pCharacter->m_bSpecial = false;
	pCharacter->m_uiSpecialCounter = 0;
	pCharacter->SetSpeed(350);

	//	0 - GetWhacked
	//	1 - WhackedPause
	//	2 - SittingStill
	//	3 - SquirmForward
	//	4 - SquirmPause
	//	5 - Lunge

}

void CBossDaggerAI::Update(CBaseCharacter* pCharacter, float fElapsedTime)
{
	//pCharacter->m_bWalkCycle = 0;	//	Set to the one that looks most like an attack.
	//find the player direction!
	float temp_y_dist = pCharacter->GetPosY() - 595;
	float temp_x_dist = pCharacter->GetPosX() - 1519;
	
	if(fabs(temp_y_dist) > fabs(temp_x_dist))
	{
		//then we are going north-south
		if(595 < pCharacter->GetPosY())
		{
			pCharacter->SetVelX( 0.0f );
			pCharacter->SetVelY( -1.0f * pCharacter->GetSpeed() );
			pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_UP);
		}
		else
		{
			pCharacter->SetVelX( 0.0f );
			pCharacter->SetVelY( pCharacter->GetSpeed() );
			pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_DOWN);
		}
		pCharacter->SetPrevVelX( 0.0f );
		pCharacter->SetPrevVelY( pCharacter->GetVelY() );
	}
	else
	{
		//then we are going east-west
		if(1519 < pCharacter->GetPosX())
		{
			pCharacter->SetVelX( -1.0f * pCharacter->GetSpeed() );
			pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_LEFT);
			pCharacter->SetVelY( 0.0f );
		}
		else
		{
			pCharacter->SetVelX( pCharacter->GetSpeed() );
			pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_RIGHT);
			pCharacter->SetVelY( 0.0f );
		}
		pCharacter->SetPrevVelX( pCharacter->GetVelX() );
		pCharacter->SetPrevVelY( 0.0f );
	}
	
}

void CBossDaggerAI::Exit(CBaseCharacter* pCharacter)
{

}