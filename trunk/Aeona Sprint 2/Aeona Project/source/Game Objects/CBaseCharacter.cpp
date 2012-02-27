////////////////////////////////////////////////////////////////////////
//    File Name				:	"CBaseCharacter.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/26 - 9:40 PM
//    Purpose				:	Class that inherits from CBaseObject and
//								contains all the functionality that is
//								common to all game characters
////////////////////////////////////////////////////////////////////////

// Precompiled header
#include "StdAfx.h"
// Include header file
#include "CBaseCharacter.h"

// Constructor
CBaseCharacter::CBaseCharacter(long lPositionX, long lPositionY, unsigned int uiSpeed,
	int nImageID, unsigned int uiWidth, unsigned int uiHeight, bool bActive,
	unsigned int uiMaxHealth, unsigned int uiAttackDamage)
	: CBaseObject(lPositionX, lPositionY, uiSpeed, nImageID, uiWidth ,uiHeight, bActive)
{
	m_uiMaxHealth = uiMaxHealth;
	m_uiCurHealth = uiMaxHealth;
	m_uiAttackDamage = uiAttackDamage;
}

// Common routines
bool CBaseCharacter::LoadAnimations(char const * const szFilename)
{
	if(!szFilename)
		return false;

	int* pnFirstAnmID = new int;
	int* pnLastAnmID = new int;
	
	CAnimationManager::GetInstance()->LoadAnimation(szFilename, pnFirstAnmID, pnLastAnmID);

	for(int i = *pnFirstAnmID; i <= *pnLastAnmID; ++i)
	{
		CAnimationPlayer* pAnmPlayer = new CAnimationPlayer(i, true);

		PushAnimationPlayer(pAnmPlayer);
		pAnmPlayer->Play();
	}

	return true;
}

void CBaseCharacter::Update(float fElapsedTime)
{
	CBaseObject::Update(fElapsedTime);
}

void CBaseCharacter::Attack(CBaseCharacter* pTarget)
{
}

void CBaseCharacter::Die(void)
{
}

void CBaseCharacter::ChangeAIState(IBaseAIState* pAIState)
{
}


void CBaseCharacter::SufferDamage(unsigned int uiDamage)
{
}

void CBaseCharacter::Heal(unsigned int uiHealAmount)
{
}

// Destructor
CBaseCharacter::~CBaseCharacter(void)
{
}