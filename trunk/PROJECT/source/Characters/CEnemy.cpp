////////////////////////////////////////////////////////////////////////
//    File Name				:	"CEnemy.cpp"
//
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 4:24 AM
//    Purpose				:	Enemy character class definitions
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CEnemy.h"

//	Enemy-specific
void CEnemy::ChangeState(IBaseAIState* pAIState)
{
	if(m_pAIState != NULL)
	{
		m_pAIState->Exit();
	}
	m_pAIState = pAIState;
	if(m_pAIState != NULL)
	{
		m_pAIState->Enter();
	}
}

bool CEnemy::Initialize(short sPosX, short sPosY, unsigned char ucCharType, unsigned int uiSpeed, unsigned char ucMaxHP, CAnimation* panmMove, CAnimation* panmDestruction)
{
	SetPosX( sPosX );
	SetPosY( sPosY );


	int temp = GetImageID();
	
	return true;
}

RECT CEnemy::GetCollisionRect()
{
	RECT temp = {32,32,32,32};
	return temp;
}

bool CEnemy::CheckCollision(IBaseInterface* pBase)
{
	return true;
}

void CEnemy::HandleEvent(CEvent* pEvent)
{
}

void CEnemy::Update(float fElapsedTime)
{
	if(m_fEnemyMoveTimer < 0.0f)
		m_fEnemyMoveTimer = 0.0f;
	if(GetVelX() != 0 && GetVelY() != 0)
	{
		m_fEnemyMoveTimer += fElapsedTime;
		if(m_fEnemyMoveTimer >= 1.0f)
		{
			m_fEnemyMoveTimer = 0.0f;
			SetVelX(0);
			SetVelY(0);
		}
		else
		{
			SetPosX( GetPosX() + GetVelX() );
			SetPosY( GetPosY() + GetVelY() );
		}
	}
	else
	{
		m_fEnemyMoveTimer += fElapsedTime;
		if(m_fEnemyMoveTimer >= 2.0f)
		{
			m_fEnemyMoveTimer = 0.0f;

			SetVelX(rand()%3 - 1);
			SetVelY(rand()%3 - 1);
		}
		else
		{
			//	nothing; we are waiting still.
		}
	}
}

void CEnemy::Render()
{
	RECT rPlayer;
	rPlayer.left = 96;
	rPlayer.top = 0;
	rPlayer.right = 192;
	rPlayer.bottom = 96;
	TEX_MNG->Draw( GetImageID(), GetPosX(), GetPosY(), 1.0f, 1.0f, &rPlayer);
}

void CEnemy::Shutdown()
{
}

//	References
void CEnemy::AddRef()
{
	SetRefCount( GetRefCount() + 1 );
}
void CEnemy::Release()
{
	SetRefCount( GetRefCount() - 1 );
	if( GetRefCount() == 0 )
	{
		delete this;
	}
}

//	Type
unsigned int CEnemy::GetType()
{
	return 0;
}