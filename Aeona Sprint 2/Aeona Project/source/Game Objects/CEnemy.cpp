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
#include "../Wrappers/SGD_Math.h"
#include "../Camera/CCameraControl.h"

CEnemy::CEnemy(double dPositionX, double dPositionY, unsigned int uiSpeed,
		int nImageID, unsigned int uiWidth, unsigned int uiHeight, bool bActive,
		unsigned int uiMaxHealth, unsigned int uiAttackDamage, float fRespawnTime)
		: CBaseCharacter(dPositionX, dPositionY, uiSpeed, nImageID, uiWidth, uiHeight, bActive, uiMaxHealth, uiAttackDamage)
{
	m_ptRespawnPosition.x = dPositionX;
	m_ptRespawnPosition.y = dPositionY;
	m_dwDeadTimeStamp = 0;
	m_fRespawnTime = fRespawnTime;
}

CEnemy::~CEnemy(void)
{

}

void CEnemy::Update(float fElapsedTime)
{
	// DANIEL CODE BEGIN
	if(IsDead())
	{
		if((timeGetTime() - m_dwDeadTimeStamp) > (m_fRespawnTime * 1000))
		{
			Ressurect();

			SetPosX(m_ptRespawnPosition.x);
			SetPosY(m_ptRespawnPosition.y);
		}
	}
	// DANIEL CODE END
	else
	{
		CBaseCharacter::Update(fElapsedTime);
	}
}

bool CEnemy::CheckCollision(IBaseInterface* pObject)
{
	if(pObject->GetType() == TYPE_WEAPON_ARROW) return false;

	if( CBaseCharacter::CheckCollision(pObject) == true)
	{
		if( pObject->GetType() == TYPE_CHAR_PLAYER && this->m_uiMiniState > 1 )
		{
			CPlayer::GetInstance()->SufferDamage(GetAttackDamage());
			if(CPlayer::GetInstance()->GetOuchTimer() == 0.0f)
				CPlayer::GetInstance()->SetOuchTimer(0.8f);
		}
	}
	return true;
}

void CEnemy::Die(void)
{
	int random = RandomInt( 0, 5 );
	if( random == 2 )
	{
		CCameraControl::GetInstance()->SetKillCam(true);
	}
	CBaseCharacter::Die();
	m_dwDeadTimeStamp = timeGetTime();
}