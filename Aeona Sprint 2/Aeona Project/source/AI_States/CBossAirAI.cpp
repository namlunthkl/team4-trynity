#include "StdAfx.h"
#include "CBossAirAI.h"
#include "../Game Objects/CPlayer.h"
CBossAirAI* CBossAirAI::sm_pInstance = NULL;

IBaseAIState* CBossAirAI::GetInstance(void)
{
	if(!sm_pInstance)
		sm_pInstance = new CBossAirAI();
	return sm_pInstance;
}

void CBossAirAI::DeleteInstance(void)
{
	if(sm_pInstance != NULL)
	{
		delete sm_pInstance;
		sm_pInstance = NULL;
	}
}

void CBossAirAI::Enter(CBaseCharacter* pCharacter)
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

void CBossAirAI::Update(CBaseCharacter* pCharacter, float fElapsedTime)
{
	switch( pCharacter->GetMiniState() )
	{
	case 0:	// 0 - Get Whacked!
		{
			if( pCharacter->GetMoveTimer() == 0.0f )	//	We JUST got whacked!
			{
				pCharacter->SetMoveTimer( pCharacter->GetMoveTimer() + fElapsedTime );	//	Increment timer.
				if(pCharacter->GetPrevVelX() < 0.0f)	//	We got whacked, so set our velocity flying backward
					pCharacter->SetVelX( 350.0f );
				else if(pCharacter->GetPrevVelX() > 0.0f)
					pCharacter->SetVelX( -350.0f );
				if(pCharacter->GetPrevVelY() < 0.0f)
					pCharacter->SetVelY( 350.0f );
				else if(pCharacter->GetPrevVelY() > 0.0f)
					pCharacter->SetVelY( -350.0f );
			}
			else if( pCharacter->GetMoveTimer() < 0.15f )	//	Throw us backward for a bit
			{
				pCharacter->SetMoveTimer( pCharacter->GetMoveTimer() + fElapsedTime );	//	Increment timer.
			}
			else
			{
				pCharacter->SetMoveTimer( 0.0f );
				pCharacter->SetMiniState( 1 );	// Go to the little pause state after being whacked.
			}
			break;
		}
	case 1:	// 1 - Pause after being whacked.
		{
			if( pCharacter->GetMoveTimer() == 0.0f )
			{
				pCharacter->SetMoveTimer( pCharacter->GetMoveTimer() + fElapsedTime );	//	Increment timer.
				pCharacter->SetVelX( 0.0f );
				pCharacter->SetVelY( 0.0f );
			}
			else if( pCharacter->GetMoveTimer() < 0.4f )	//	Owww I'm still hurting, for 0.4 sec
			{
				pCharacter->SetMoveTimer( pCharacter->GetMoveTimer() + fElapsedTime );	//	Increment timer.
			}
			else
			{
				pCharacter->SetMoveTimer( 0.0f );
				pCharacter->philEnemyColor = D3DCOLOR_XRGB(255, 255, 255);
				pCharacter->SetMiniState( 3 );	// Immediately squirm forward.
			}
			break;
		}
	case 2:	// 2 - Sitting still because the player is not near.
		{
			//	NEARBY PLAYER CHECK!!
			if( (CPlayer::GetInstance()->GetPosY() >= pCharacter->GetPosY() - 512 && CPlayer::GetInstance()->GetPosY() <= pCharacter->GetPosY() + 512) && (CPlayer::GetInstance()->GetPosX() >= pCharacter->GetPosX() - 512 && CPlayer::GetInstance()->GetPosX() <= pCharacter->GetPosX() + 512) )
			{
				pCharacter->SetMoveTimer( 0.0f );
				pCharacter->SetMiniState( 3 );	// set to crouching, ready to pounce, when we find player
				break;	// i don't want to continue 'stopped' if the player is instantly nearby.
			}
			//	NEARBY PLAYER CHECK!!
			else if( pCharacter->GetMoveTimer() == 0.0f )
			{
				pCharacter->SetMoveTimer( pCharacter->GetMoveTimer() + fElapsedTime );
				pCharacter->SetVelX( 0.0f );
				pCharacter->SetVelY( 0.0f );
			}
			else if( pCharacter->GetMoveTimer() < 2.0f )
			{
				pCharacter->SetMoveTimer( pCharacter->GetMoveTimer() + fElapsedTime );
			}
			else
			{
				pCharacter->SetMoveTimer( 0.0f );
				pCharacter->SetMiniState( 2 );
			}
			break;
		}
	case 3:
		{
			if( pCharacter->GetMoveTimer() == 0.0f )
			{
				pCharacter->m_bWalkCycle = !pCharacter->m_bWalkCycle;
				pCharacter->SetMoveTimer( pCharacter->GetMoveTimer() + fElapsedTime );	//	Increment timer.
				//	HACK directly check whether the player is nearby or not, below.
				if( (CPlayer::GetInstance()->GetPosY() >= pCharacter->GetPosY() - 512 && CPlayer::GetInstance()->GetPosY() <= pCharacter->GetPosY() + 512) && (CPlayer::GetInstance()->GetPosX() >= pCharacter->GetPosX() - 512 && CPlayer::GetInstance()->GetPosX() <= pCharacter->GetPosX() + 512) )
				{
					//pCharacter->m_bWalkCycle = 0;	//	Set to the one that looks most like an attack.
					//find the player direction!
					double temp_y_dist = pCharacter->GetPosY() - CPlayer::GetInstance()->GetPosY();
					double temp_x_dist = pCharacter->GetPosX() - CPlayer::GetInstance()->GetPosX();

					if(fabs(temp_y_dist) > fabs(temp_x_dist))
					{
						//then we are going north-south
						if(CPlayer::GetInstance()->GetPosY() < pCharacter->GetPosY())
						{
							pCharacter->SetVelX( 0.0f );
							pCharacter->SetVelY( -1.0f * pCharacter->GetSpeed() );
							pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_UP);
						}
						else
						{
							pCharacter->SetVelX( 0.0f );
							pCharacter->SetVelY( (float) pCharacter->GetSpeed() );
							pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_DOWN);
						}
						pCharacter->SetPrevVelX( 0.0f );
						pCharacter->SetPrevVelY( pCharacter->GetVelY() );
					}
					else
					{
						//then we are going east-west
						if(CPlayer::GetInstance()->GetPosX() < pCharacter->GetPosX())
						{
							pCharacter->SetVelX( -1.0f * pCharacter->GetSpeed() );
							pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_LEFT);
							pCharacter->SetVelY( 0.0f );
						}
						else
						{
							pCharacter->SetVelX( (float) pCharacter->GetSpeed() );
							pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_RIGHT);
							pCharacter->SetVelY( 0.0f );
						}
						pCharacter->SetPrevVelX( pCharacter->GetVelX() );
						pCharacter->SetPrevVelY( 0.0f );
					}
				}
			}
			else if( pCharacter->GetMoveTimer() < 0.1f )
			{
				pCharacter->SetMoveTimer( pCharacter->GetMoveTimer() + fElapsedTime );	//	Increment timer.
			}
			else
			{
				pCharacter->SetMoveTimer( 0.0f );
			}
			break;
		}
	}
}

void CBossAirAI::Exit(CBaseCharacter* pCharacter)
{

}