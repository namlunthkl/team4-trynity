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
#include "../StdAfx.h"
// Include header file
#include "CBaseCharacter.h"

#include "../AI_States/IBaseAIState.h"
#include "../Messaging/CMessageSystem.h"

// Constructor
CBaseCharacter::CBaseCharacter(double dPositionX, double dPositionY, unsigned int uiSpeed,
	int nImageID, unsigned int uiWidth, unsigned int uiHeight, bool bActive,
	unsigned int uiMaxHealth, unsigned int uiAttackDamage)
	: CBaseObject(dPositionX, dPositionY, uiSpeed, nImageID, uiWidth ,uiHeight, bActive)
{
	m_uiMaxHealth = uiMaxHealth;
	m_uiCurHealth = uiMaxHealth;
	m_uiAttackDamage = uiAttackDamage;

	m_uiMiniState = 0;
	m_uiPhilDirection = 0;

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
		CAnimationPlayer* pAnmPlayer;
		//if(i == ANM_ATK_UP && i <= ANM_ATK_LEFT)
		//	pAnmPlayer = new CAnimationPlayer(i, false);
		//else
			pAnmPlayer = new CAnimationPlayer(i, true);

		PushAnimationPlayer(pAnmPlayer);
		pAnmPlayer->Play();
	}

	SetCurrentAnimation(0);

	return true;
}

void CBaseCharacter::Update(float fElapsedTime)
{
	if(m_pAIState && m_bDying == false)
		m_pAIState->Update(this, fElapsedTime);

	CBaseObject::Update(fElapsedTime);
}

void CBaseCharacter::Attack()
{
	// TODO: Play attack animation
	// TODO: DO DAMAGE
}

void CBaseCharacter::Die(void)
{
	// TODO: Play die animation

	// TODO: Send a message to spawn an item here
	// TODO: Send a message to delete this object
	if(m_uiEnemyBehavior == 0)
	{
		// CMessageSystem::GetInstance()->SendMsg(new CDestroyObjectMessage(this));
		Deactivate();
	}
	else
	{
		m_bDying = true;

		if(m_pAIState)
			m_pAIState->Exit(this);
	}
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
	if( m_uiEnemyBehavior != 0 && this->m_uiMiniState != 0 )
	{
		AUDIO->SFXPlaySound( CGame::GetInstance()->m_sndFleshHit );
		philEnemyColor = D3DCOLOR_XRGB(255, 0, 0);	// render in red
		SetMoveTimer( 0.0f );
		m_uiMiniState = 0;	//	it's an enemy, and set me to 'ow'
	}

	if(uiDamage < m_uiCurHealth)
	{
		m_uiCurHealth -= uiDamage;
	}
	else
	{
		m_uiCurHealth = 0;
		if(m_uiEnemyBehavior == BEHAVIOR_LARVA && this->m_bDying == false )
		{
			AUDIO->SFXPlaySound( CGame::GetInstance()->m_sndDeathSplat );
			philEnemyColor = D3DCOLOR_XRGB(0, 255, 0);
		}
		else if(m_uiEnemyBehavior == BEHAVIOR_GOLEM && this->m_bDying == false )
		{
			AUDIO->SFXPlaySound( CGame::GetInstance()->m_sndDeathSplat );
			philEnemyColor = D3DCOLOR_XRGB(180, 180, 180);
		}
		else if(m_uiEnemyBehavior == BEHAVIOR_SLIME && this->m_bDying == false )
		{
			AUDIO->SFXPlaySound( CGame::GetInstance()->m_sndDeathSplat );
			philEnemyColor = D3DCOLOR_XRGB(255, 160, 0);
		}
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

void CBaseCharacter::SetPhilDirection(void)
{
	if( GetVelX() < 0 )
	{
		// Possibly left
		if( fabs( GetVelX() ) > fabs( GetVelY() ) )
		{
			//	Definitely left!
			m_uiPhilDirection = 0;
			return;
		}
	}
	else if( GetVelY() < 0 )
	{
		//	Possibly up
		if( fabs( GetVelY() ) >= fabs( GetVelX() ) )
		{
			//	Definitely up, or perfectly diagonal.
			m_uiPhilDirection = 1;
			return;
		}
	}
	else if( GetVelX() > 0 )
	{
		//	Possibly right
		if( fabs( GetVelX() ) > fabs( GetVelY() ) )
		{
			//	Definitely right!
			m_uiPhilDirection = 2;
			return;
		}
	}
	else if( GetVelY() > 0 )
	{
		//	Possibly down
		if( fabs( GetVelY() ) >= fabs( GetVelX() ) )
		{
			//	Definitely down, or perfectly diagonal.
			m_uiPhilDirection = 3;
			return;
		}
	}
	m_uiPhilDirection = 0;	//	If we somehow fail, we're facing left by default.
}

void CBaseCharacter::Ressurect(void)
{
	CBaseObject::Ressurect();

	if(m_pAIState)
		m_pAIState->Enter(this);

	m_uiCurHealth = m_uiMaxHealth;
	m_uiMiniState = 0;
	m_uiPhilDirection = 0;
}