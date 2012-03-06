////////////////////////////////////////////////////////////////////////
//    File Name				:	"CEnemy.cpp"
//
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 4:24 AM
//    Purpose				:	Enemy character class definitions
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "../States/CGameplayState.h"

CEnemy::CEnemy(double dPositionX, double dPositionY, unsigned int uiSpeed,
		int nImageID, unsigned int uiWidth, unsigned int uiHeight, bool bActive,
		unsigned int uiMaxHealth, unsigned int uiAttackDamage)
		: CBaseCharacter(dPositionX, dPositionY, uiSpeed, nImageID, uiWidth, uiHeight, bActive, uiMaxHealth, uiAttackDamage)
{
	//LoadAnimations("resource/NPCAnimationsAnchorBased.xml");
}

CEnemy::~CEnemy(void)
{

}

bool CEnemy::CheckCollision(IBaseInterface* pObject)
{
	if(pObject->GetType() == TYPE_WEAPON_ARROW) return false;

	if( CBaseCharacter::CheckCollision(pObject) == true)
	{
		if( pObject->GetType() == TYPE_CHAR_PLAYER )
		{
			CPlayer::GetInstance()->SufferDamage(GetAttackDamage());
			CPlayer::GetInstance()->m_fOuchTimer = 0.8f;
		}
	}
	return true;
}

void CEnemy::Die(void)
{
	CBaseCharacter::Die();
	CEventSystem::GetInstance()->SendEvent("victory");
}


//
//void CEnemy::Update(float fElapsedTime)
//{
//	if(m_nCurrentAnimation != -1)
//		m_pAnimation[m_nCurrentAnimation]->Update(fElapsedTime);
//
//	if(m_fEnemyMoveTimer < 0.0f)
//		m_fEnemyMoveTimer = 0.0f;
//	if(GetVelX() != 0 && GetVelY() != 0)
//	{
//		m_fEnemyMoveTimer += fElapsedTime;
//		if(m_fEnemyMoveTimer >= 1.0f)
//		{
//			m_fEnemyMoveTimer = 0.0f;
//			SetVelX(0);
//			SetVelY(0);
//		}
//		else
//		{
//			CEnemy tempEnemy;
//			tempEnemy.Initialize(GetPosX() + GetVelX(), GetPosY() + GetVelY(), 0, 0, 0, NULL, NULL);
//
//			/*if(!CWorldEngine::GetInstance()->CheckCollisions(&tempEnemy))
//			{
//				SetPosX( GetPosX() + GetVelX() );
//				SetPosY( GetPosY() + GetVelY() );
//			}*/
//		}
//	}
//	else
//	{
//		m_fEnemyMoveTimer += fElapsedTime;
//		if(m_fEnemyMoveTimer >= 2.0f)
//		{
//			m_fEnemyMoveTimer = 0.0f;
//
//			SetVelX((float)(rand()%3 - 1));
//			SetVelY((float)(rand()%3 - 1));
//		}
//		else
//		{
//			//	nothing; we are waiting still.
//		}
//	}
//}
//
