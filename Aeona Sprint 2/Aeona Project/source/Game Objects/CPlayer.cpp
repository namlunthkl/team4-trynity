////////////////////////////////////////////////////////////////////////
//    File Name				:	"CPlayer.cpp"
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 3:57 AM
//    Purpose				:	Game player character class definitions
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CPlayer.h"
#include "../Messaging/CEventSystem.h"
#include "../Input Manager/CInputManager.h"
#include "../States/CGameplayState.h"

// Constructor
CPlayer::CPlayer(void) : CBaseCharacter()
{
	m_byteWeapons = 0;
	m_byteMasks = 0;
	m_bHeartPiece = false;
	m_uiCurrentWeapon = WEAPON_DAGGER;
	m_uiCurrentMask = MASK_NONE;
	m_sndPlayerMovement = -1;
	
	Activate();
	CBaseCharacter::LoadAnimations("resource/Char Walk.xml");
	m_fxFootsteps.Load("Resource/data/leafyburst.xml");
}

CPlayer* CPlayer::GetInstance(void)
{
	// Lazy instantiation
	static CPlayer instance;
	return &instance;
}


// Common routines - Overloaded methods

void CPlayer::Update(float fElapsedTime)
{
	// Store the old position of the player for future checks
	PointD ptOldPosition = GetPosition();

	// Call Base Character's update method to move the player
	CBaseCharacter::Update(fElapsedTime);
	// Update the particles
	m_fxFootsteps.Update(fElapsedTime);

	// Fire the particle effect if the position changed
	if(ptOldPosition != GetPosition())
	{
		m_fxFootsteps.Fire(SCREEN_POS_X(GetPosX()), SCREEN_POS_Y(GetPosY()));
	}
}

void CPlayer::Render(void)
{
	// Render the player
	CBaseCharacter::Render();

	// Render the particles
	m_fxFootsteps.Render();
}

void CPlayer::Attack(CBaseCharacter* pTarget)
{
	CBaseCharacter::Attack(pTarget);
}

void CPlayer::ChargedAttack(void)
{
	// TODO: Create charged attack effect in here
	// TODO: Send any needed event
}

void CPlayer::Die(void)
{
	CBaseCharacter::Die();
	CEventSystem::GetInstance()->SendEvent("GameOver");
}

// Get input for the player
void CPlayer::Input(void)
{
	if(CInputManager::GetInstance()->GetUp())
	{
		SetCurrentAnimation(ANM_WALK_UP);
		SetVelY(-(float)GetSpeed());
	}
	else if(CInputManager::GetInstance()->GetDown())
	{
		SetCurrentAnimation(ANM_WALK_DOWN);
		SetVelY((float)GetSpeed());
	}
	else
		SetVelY(0);

	if(CInputManager::GetInstance()->GetLeft())
	{
		SetCurrentAnimation(ANM_WALK_LEFT);
		SetVelX(-(float)GetSpeed());
	}
	else if(CInputManager::GetInstance()->GetRight())
	{
		SetCurrentAnimation(ANM_WALK_RIGHT);
		SetVelX((float)GetSpeed());
	}
	else
		SetVelX(0);
}

// Cycle through the weapons
void CPlayer::CycleWeapon(void)
{
	// Increase the current weapon variable
	m_uiCurrentWeapon++;

	// If we reached max, go back to the first one
	if(m_uiCurrentWeapon >= WEAPON_MAX)
		m_uiCurrentWeapon = WEAPON_DAGGER;

	// If it doesn't have the weapon
	if(!TestBit(m_byteWeapons, m_uiCurrentWeapon))
	{
		// Keep looking
		CycleWeapon();
	}
}

// Cycle through the masks
void CPlayer::CycleMask(void)
{
	// Increase the current weapon variable
	m_uiCurrentMask++;

	// If we reached max, go back to the first one
	if(m_uiCurrentMask >= MASK_MAX)
		m_uiCurrentMask = MASK_NONE;

	// If it doesn't have the weapon
	if(!TestBit(m_byteMasks, m_uiCurrentMask))
	{
		// Keep looking
		CycleMask();
	}
}

// Set the bit for a weapon on
void CPlayer::AquireWeapon(unsigned int uiWeaponType)
{
	TurnBitOn(m_byteWeapons, uiWeaponType);
}

// Set bit of a mask on
void CPlayer::AquireMask(unsigned int uiMaskType)
{
	TurnBitOn(m_byteMasks, uiMaskType);
}

// Set bool for heart piece on or increase health
void CPlayer::AquireHeartPiece(void)
{
	if(m_bHeartPiece == false)
		m_bHeartPiece = true;
	else
	{
		GainHeart();
		m_bHeartPiece = false;
	}
}

// Destructor
CPlayer::~CPlayer(void)
{

}