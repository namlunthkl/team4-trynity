#include "StdAfx.h"
#include "CBossFireAI.h"
#include "../Game Objects/CPlayer.h"
#include "../Weapons/CFireBall.h"
#include "../Game Objects/CObjectManager.h"
CBossFireAI* CBossFireAI::sm_pInstance = NULL;

IBaseAIState* CBossFireAI::GetInstance(void)
{
	if(!sm_pInstance)
		sm_pInstance = new CBossFireAI();
	return sm_pInstance;
}

void CBossFireAI::DeleteInstance(void)
{
	if(sm_pInstance != NULL)
	{
		delete sm_pInstance;
		sm_pInstance = NULL;
	}
}

void CBossFireAI::Enter(CBaseCharacter* pCharacter)
{
	pCharacter->SetVelY( 0 );
	pCharacter->SetVelX( 0 );
	pCharacter->SetPrevVelX( 0 );
	pCharacter->SetPrevVelY( 0 );
	pCharacter->SetMoveTimer(0.0f);
	FireTime = 0.0f;
	pCharacter->SetMiniState(2);
	pCharacter->SetBehavior(0);
	pCharacter->philEnemyColor = D3DCOLOR_XRGB(255, 255, 255);

	pCharacter->m_bSpecial = false;
	pCharacter->m_uiSpecialCounter = 0;
	pCharacter->SetSpeed(150);

}

void CBossFireAI::Update(CBaseCharacter* pCharacter, float fElapsedTime)
{
	FireTime += fElapsedTime;

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
				pCharacter->SetMiniState( 4 );
			}
			break;
		}
	case 4:
		{
			if( (CPlayer::GetInstance()->GetPosY() >= pCharacter->GetPosY() - 512 && CPlayer::GetInstance()->GetPosY() <= pCharacter->GetPosY() + 512) && (CPlayer::GetInstance()->GetPosX() >= pCharacter->GetPosX() - 512 && CPlayer::GetInstance()->GetPosX() <= pCharacter->GetPosX() + 512) && FireTime >= 1.0f)
			{
				CFireball* FireBall = new CFireball();
				FireBall->SetSpeed(580);
				FireBall->Activate();
				CObjectManager::GetInstance()->AddObject(FireBall);
				PointD temp = pCharacter->GetPosition();
				float temp_y_dist = pCharacter->GetPosY() - CPlayer::GetInstance()->GetPosY();
				float temp_x_dist = pCharacter->GetPosX() - CPlayer::GetInstance()->GetPosX();

				if(fabs(temp_y_dist) > fabs(temp_x_dist))
				{
					if(CPlayer::GetInstance()->GetPosY() < pCharacter->GetPosY())
					{
						pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_UP);
						FireBall->SetVelX(0.0f);
						FireBall->SetVelY(-1.0f *FireBall->GetSpeed());
						FireBall->SetPosX(temp.x);
						FireBall->SetPosY(temp.y-20);
					}
					else if(CPlayer::GetInstance()->GetPosY() > pCharacter->GetPosY())
					{
						pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_DOWN);
						FireBall->SetVelX(0.0f);
						FireBall->SetVelY(1.0f * FireBall->GetSpeed());
						FireBall->SetPosX(temp.x);
						FireBall->SetPosY(temp.y);
					}
				}
				else
				{
					if(CPlayer::GetInstance()->GetPosX() < pCharacter->GetPosX())
					{
						pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_LEFT);
						FireBall->SetVelX(-1.0f *FireBall->GetSpeed());
						FireBall->SetVelY(0.0f);
						FireBall->SetPosX(temp.x);
						FireBall->SetPosY(temp.y-20);
					}
					else if(CPlayer::GetInstance()->GetPosX() > pCharacter->GetPosX())
					{
						pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_RIGHT);
						FireBall->SetVelX(1.0f *FireBall->GetSpeed());
						FireBall->SetVelY(0.0f);
						FireBall->SetPosX(temp.x);
						FireBall->SetPosY(temp.y-20);
					}
				}
				FireTime = 0;
			}
			pCharacter->SetMoveTimer( 0.0f );
			pCharacter->SetMiniState( 3 );
		}
	}

}

void CBossFireAI::Exit(CBaseCharacter* pCharacter)
{

}