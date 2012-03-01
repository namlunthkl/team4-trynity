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

#include "../AI_States/IBaseAIState.h"

// Constructor
CBaseCharacter::CBaseCharacter(double dPositionX, double dPositionY, unsigned int uiSpeed,
	int nImageID, unsigned int uiWidth, unsigned int uiHeight, bool bActive,
	unsigned int uiMaxHealth, unsigned int uiAttackDamage)
	: CBaseObject(dPositionX, dPositionY, uiSpeed, nImageID, uiWidth ,uiHeight, bActive)
{
	m_uiMaxHealth = uiMaxHealth;
	m_uiCurHealth = uiMaxHealth;
	m_uiAttackDamage = uiAttackDamage;

	m_pAIState = nullptr;
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

	SetCurrentAnimation(0);

	return true;
}

void CBaseCharacter::Update(float fElapsedTime)
{
	CBaseObject::Update(fElapsedTime);

	if(m_pAIState)
		m_pAIState->Update(this, fElapsedTime);
}

void CBaseCharacter::Attack(CBaseCharacter* pTarget)
{
	// TODO: Play attack animation
	pTarget->SufferDamage(m_uiAttackDamage);
}

void CBaseCharacter::Die(void)
{
	// TODO: Play die animation
	// TODO: Send a message to spawn an item here
	// TODO: Send a message to delete this object
}

void CBaseCharacter::ChangeAIState(IBaseAIState* pAIState)
{
	if(m_pAIState != NULL)
	{
		m_pAIState->Exit(this);
	}
	m_pAIState = pAIState;
	if(m_pAIState != NULL)
	{
		m_pAIState->Enter(this);
	}
}

void CBaseCharacter::SufferDamage(unsigned int uiDamage)
{
	if(uiDamage < m_uiCurHealth)
	{
		m_uiCurHealth -= uiDamage;
	}
	else
	{
		m_uiCurHealth = 0;
		Die();
	}
}

void CBaseCharacter::Heal(unsigned int uiHealAmount)
{
	if(m_uiCurHealth + uiHealAmount < m_uiMaxHealth)
	{
		m_uiCurHealth += uiHealAmount;
	}
	else
	{
		m_uiCurHealth = m_uiMaxHealth;
	}
}

// Destructor
CBaseCharacter::~CBaseCharacter(void)
{
}