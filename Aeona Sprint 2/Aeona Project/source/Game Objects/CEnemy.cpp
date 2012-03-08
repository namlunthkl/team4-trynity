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
}