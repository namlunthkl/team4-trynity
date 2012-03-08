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
	pCharacter->SetVelY( 0 );
	pCharacter->SetVelX( 0 );
	pCharacter->SetPrevVelX(0);
	pCharacter->SetPrevVelY(0);
	pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_RIGHT);

	pCharacter->SetMoveTimer(0.0f);
	pCharacter->SetMiniState(2);
	pCharacter->SetSpeed(30);
	
	//	0 - hurt
	//	1 - hurt knocked back
	//	2 - stopped
	//	3 - wandering
	//	4 - pause-before
	//	5 - leaping
	//	6 - pause-after
}

void CJumperAIState::Update(CBaseCharacter* pCharacter, float fElapsedTime)
{
	switch( pCharacter->GetMiniState() )
	{
		case 0:	// 0 - hurt
		{
			if( pCharacter->GetMoveTimer() < 0.75f )
			{
				pCharacter->SetMoveTimer( pCharacter->GetMoveTimer() + fElapsedTime );
			}
			else
			{
				pCharacter->SetMoveTimer( 0.0f );
				pCharacter->SetMiniState( 3 );	// set to stopped after i'm done being hurt
			}
			break;
		}
		case 1:	// 1 - hurt knocked back
		{
			break;
		}
		case 2:	// 2 - stopped
		{
			//	NEARBY PLAYER CHECK!!
			if( (CPlayer::GetInstance()->GetPosY() >= pCharacter->GetPosY() - 192 && CPlayer::GetInstance()->GetPosY() <= pCharacter->GetPosY() + 192) && (CPlayer::GetInstance()->GetPosX() >= pCharacter->GetPosX() - 192 && CPlayer::GetInstance()->GetPosX() <= pCharacter->GetPosX() + 192) )
			{
				pCharacter->SetMoveTimer( 0.0f );
				pCharacter->SetMiniState( 5 );	// set to crouching, ready to pounce, when we find player
				break;	// i don't want to continue 'stopped' if the player is instantly nearby.
			}
			//	NEARBY PLAYER CHECK!!
			if( pCharacter->GetMoveTimer() < 1.5f )
			{
				pCharacter->SetMoveTimer( pCharacter->GetMoveTimer() + fElapsedTime );
			}
			else
			{
				pCharacter->SetVelX(0);
				pCharacter->SetVelY(0);
				pCharacter->SetMoveTimer( 0.0f );
				pCharacter->SetMiniState( 3 );	// set to wandering after done resting
			}
			break;
		}
		case 3:	// 3 - wandering
		{
			if( pCharacter->GetMoveTimer() == 0.0f )
			{
				pCharacter->SetMoveTimer( pCharacter->GetMoveTimer() + fElapsedTime );
				unsigned int tempDir = rand()%8;
				if( tempDir == 0 )
				{
					pCharacter->SetVelX( 0.0f );
					pCharacter->SetVelY( -1.0 * pCharacter->GetSpeed() );
					pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_UP);
				}
				else if( tempDir == 1 )
				{
					pCharacter->SetVelX( pCharacter->GetSpeed() );
					pCharacter->SetVelY( -1.0f * pCharacter->GetSpeed() );
					pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_UP);
					float meh = pCharacter->GetVelX();
					float meh2= pCharacter->GetVelY();
					int x = 5;
				}
				else if( tempDir == 2 )
				{
					pCharacter->SetVelX( pCharacter->GetSpeed() );
					pCharacter->SetVelY( 0.0f );
					pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_RIGHT);
				}
				else if( tempDir == 3 )
				{
					pCharacter->SetVelX( pCharacter->GetSpeed() );
					pCharacter->SetVelY( pCharacter->GetSpeed() );
					pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_DOWN);
				}
				else if( tempDir == 4 )
				{
					pCharacter->SetVelX( 0.0f );
					pCharacter->SetVelY( pCharacter->GetSpeed() );
					pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_DOWN);
				}
				else if( tempDir == 5 )
				{
					pCharacter->SetVelX( -1.0f * pCharacter->GetSpeed() );
					pCharacter->SetVelY( pCharacter->GetSpeed() );
					pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_DOWN);
				}
				else if( tempDir == 6 )
				{
					pCharacter->SetVelX( -1.0f * pCharacter->GetSpeed() );
					pCharacter->SetVelY( 0 );
					pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_LEFT);
				}
				else if( tempDir == 7 )
				{
					pCharacter->SetVelX( -1.0 * pCharacter->GetSpeed() );
					pCharacter->SetVelY( -1.0 * pCharacter->GetSpeed() );
					pCharacter->SetCurrentAnimation(CBaseCharacter::ANM_WALK_UP);
				}
			}
			else if( pCharacter->GetMoveTimer() < 1.0f )
			{
				pCharacter->SetMoveTimer( pCharacter->GetMoveTimer() + fElapsedTime );
			}
			else
			{
				pCharacter->SetVelX(0);
				pCharacter->SetVelY(0);
				pCharacter->SetMoveTimer( 0.0f );
				pCharacter->SetMiniState( 2 );	// set to stopped after wandering
			}
			break;
		}
		case 4:	// 4 - pause-before
		{
			if( pCharacter->GetMoveTimer() == 0.0f )
			{
				pCharacter->SetMoveTimer( pCharacter->GetMoveTimer() + fElapsedTime );
				//find the player direction!
				int temp_y_dist = pCharacter->GetPosY() - CPlayer::GetInstance()->GetPosY();
				int temp_x_dist = pCharacter->GetPosX() - CPlayer::GetInstance()->GetPosX();
				if(abs(temp_y_dist) < abs(temp_x_dist))
				{
					//then we are going north-south
					if(CPlayer::GetInstance()->GetPosY() < pCharacter->GetPosY())
					{
						pCharacter->SetVelX( 0.0f );
						pCharacter->SetVelY( -0.5f * pCharacter->GetSpeed() );
					}
					else
					{
						pCharacter->SetVelX( 0.0f );
						pCharacter->SetVelY( 0.5f * pCharacter->GetSpeed() );
					}
				}
				else
				{
					//then we are going east-west
					if(CPlayer::GetInstance()->GetPosX() < pCharacter->GetPosX())
					{
						pCharacter->SetVelX( -0.5f * pCharacter->GetSpeed() );
						pCharacter->SetVelY( 0.0f );
					}
					else
					{
						pCharacter->SetVelX( 0.5f * pCharacter->GetSpeed() );
						pCharacter->SetVelY( 0.0f );
					}
				}
			}
			else if( pCharacter->GetMoveTimer() < 0.5f )
			{
				pCharacter->SetMoveTimer( pCharacter->GetMoveTimer() + fElapsedTime );
			}
			else
			{
				pCharacter->SetMoveTimer( 0.0f );
				pCharacter->SetMiniState( 5 );	// set to pouncing after done crouching
			}
			break;
		}
		case 5:	// 5 - jump
		{
			if( pCharacter->GetMoveTimer() == 0.0f )
			{
				pCharacter->SetMoveTimer( pCharacter->GetMoveTimer() + fElapsedTime );
				//find the player direction!
				int temp_y_dist = pCharacter->GetPosY() - CPlayer::GetInstance()->GetPosY();
				int temp_x_dist = pCharacter->GetPosX() - CPlayer::GetInstance()->GetPosX();
				if(abs(temp_y_dist) > abs(temp_x_dist))
				{
					//then we are going north-south
					if(CPlayer::GetInstance()->GetPosY() < pCharacter->GetPosY())
					{
						pCharacter->SetVelX( 0.0f );
						pCharacter->SetVelY( -8.0f * pCharacter->GetSpeed() );
					}
					else
					{
						pCharacter->SetVelX( 0.0f );
						pCharacter->SetVelY( 8.0f * pCharacter->GetSpeed() );
					}
				}
				else
				{
					//then we are going east-west
					if(CPlayer::GetInstance()->GetPosX() < pCharacter->GetPosX())
					{
						pCharacter->SetVelX( -8.0f * pCharacter->GetSpeed() );
						pCharacter->SetVelY( 0.0f );
					}
					else
					{
						pCharacter->SetVelX( 8.0f * pCharacter->GetSpeed() );
						pCharacter->SetVelY( 0.0f );
					}
				}
			}
			else if( pCharacter->GetMoveTimer() < 0.6f )
			{
				pCharacter->SetMoveTimer( pCharacter->GetMoveTimer() + fElapsedTime );
			}
			else
			{
				pCharacter->SetVelX(0.0f);
				pCharacter->SetVelY(0.0f);
				pCharacter->SetMoveTimer( 0.0f );
				pCharacter->SetMiniState( 3 );
			}
			break;
		}
	}




	//if(fMoveTimer < 0.0f)
	//	fMoveTimer = 0.0f;
	//if(pCharacter->GetVelX() != 0 && pCharacter->GetVelY() != 0)
	//{
	//	fMoveTimer += fElapsedTime;
	//	if(fMoveTimer >= 0.5f)
	//	{
	//		fMoveTimer = 0.0f;
	//		pCharacter->SetVelX( 0.0f );
	//		pCharacter->SetVelY( 0.0f );
	//	}
	//}
	//else
	//{
	//	fMoveTimer += fElapsedTime;
	//	if(fMoveTimer >= 3.0f)
	//	{
	//		fMoveTimer = 0.0f;

	//		if( CPlayer::GetInstance()->GetPosY() > pCharacter->GetPosY() )
	//		{
	//			pCharacter->SetVelY( 5.0f * pCharacter->GetSpeed() );
	//		}
	//		else if( CPlayer::GetInstance()->GetPosY() < pCharacter->GetPosY() )
	//		{
	//			pCharacter->SetVelY( -5.0f * pCharacter->GetSpeed() );
	//		}
	//		else
	//		{
	//			pCharacter->SetVelY( 0.0f );
	//		}

	//		if( CPlayer::GetInstance()->GetPosX() > pCharacter->GetPosX() )
	//		{
	//			pCharacter->SetVelX( 5.0f * pCharacter->GetSpeed() );
	//		}
	//		else if( CPlayer::GetInstance()->GetPosX() < pCharacter->GetPosX() )
	//		{
	//			pCharacter->SetVelX( -5.0f * pCharacter->GetSpeed() );
	//		}
	//		else
	//		{
	//			pCharacter->SetVelX( 0.0f );
	//		}
	//	}
	//	else
	//	{
	//		// nothing; we are waiting still.
	//		int x = 0;
	//	}
	//}

	//pCharacter->SetMoveTimer(fMoveTimer);
}

void CJumperAIState::Exit(CBaseCharacter* pCharacter)
{

}
