////////////////////////////////////////////////////////////////////////
//    File Name				:	"CEnemy.cpp"
//
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 4:24 AM
//    Purpose				:	Enemy character class definitions
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CEnemy.h"
#include "../States/CGameplayState.h"



bool CEnemy::Initialize(short sPosX, short sPosY, unsigned char ucCharType, unsigned int uiSpeed, unsigned char ucMaxHP, CAnimation* panmMove, CAnimation* panmDestruction)
{
	SetPosX( sPosX );
	SetPosY( sPosY );
	m_nCurrentAnimation = -1;
	SetImageID(TEX_MNG->LoadTexture("resource/tempAsset2.png"));
	return true;
}

void CEnemy::LoadAnimation()
{
	// Hack
	m_nCurrentAnimation = 1;
	CAnimationManager::GetInstance()->LoadAnimation("resource/npc walk.xml");
	m_pAnimation[ANM_UP] = new CAnimationPlayer(ANM_UP, true);
	m_pAnimation[ANM_DOWN] = new CAnimationPlayer(ANM_DOWN, true);
	m_pAnimation[ANM_LEFT] = new CAnimationPlayer(ANM_LEFT, true);
	m_pAnimation[ANM_RIGHT] = new CAnimationPlayer(ANM_RIGHT, true);
	m_pAnimation[ANM_UP]->Play();
	m_pAnimation[ANM_DOWN]->Play();
	m_pAnimation[ANM_LEFT]->Play();
	m_pAnimation[ANM_RIGHT]->Play();
}

RectD CEnemy::GetCollisionRect()
{
	RectD rectCollision(0, 0, 0, 0);
	
	if(m_nCurrentAnimation != -1)
	{
		rectCollision = m_pAnimation[m_nCurrentAnimation]->ReturnCollisionRect();
		Point anchor = m_pAnimation[m_nCurrentAnimation]->ReturnAnchorPoint();

		rectCollision.top += GetPosY() - anchor.y;
		rectCollision.left += GetPosX() - anchor.x;
		rectCollision.bottom += GetPosY() - anchor.y;
		rectCollision.right += GetPosX() - anchor.x;
	}

	return rectCollision;
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
	if(m_nCurrentAnimation != -1)
		m_pAnimation[m_nCurrentAnimation]->Update(fElapsedTime);

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
			CEnemy tempEnemy;
			tempEnemy.Initialize(GetPosX() + GetVelX(), GetPosY() + GetVelY(), 0, 0, 0, NULL, NULL);

			/*if(!CWorldEngine::GetInstance()->CheckCollisions(&tempEnemy))
			{
				SetPosX( GetPosX() + GetVelX() );
				SetPosY( GetPosY() + GetVelY() );
			}*/
		}
	}
	else
	{
		m_fEnemyMoveTimer += fElapsedTime;
		if(m_fEnemyMoveTimer >= 2.0f)
		{
			m_fEnemyMoveTimer = 0.0f;

			SetVelX((float)(rand()%3 - 1));
			SetVelY((float)(rand()%3 - 1));
		}
		else
		{
			//	nothing; we are waiting still.
		}
	}
}

void CEnemy::Render()
{
	if(m_nCurrentAnimation != -1)
		m_pAnimation[m_nCurrentAnimation]->Render(SCREEN_POS_X((int)GetPosX()),
		SCREEN_POS_Y((int)GetPosY()));
	else
	{
		RECT rPlayer;
		rPlayer.left = 96;
		rPlayer.top = 0;
		rPlayer.right = 192;
		rPlayer.bottom = 96;
		TEX_MNG->Draw( GetImageID(), SCREEN_POS_X((int)GetPosX()),
			SCREEN_POS_Y((int)GetPosY()), 1.0f, 1.0f, &rPlayer);
	}
}

void CEnemy::Shutdown()
{
}