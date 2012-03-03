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
#include "../Weapons/CDagger.h"
#include "../Weapons/CSword.h"
#include "../Weapons/CHammer.h"
#include "../Weapons/CCrossBow.h"
// Constructor
CPlayer::CPlayer(void) : CBaseCharacter()
{
	m_byteWeapons = 0;
	m_byteMasks = 0;
	m_bHeartPiece = false;
	m_uiCurrentWeapon = WEAPON_SWORD;
	m_uiCurrentMask = MASK_NONE;
	m_sndPlayerMovement = -1;

	m_vGameWeapons.push_back(new CDagger);
	m_vGameWeapons.push_back(new CSword);
	m_vGameWeapons.push_back(new CHammer);
	m_vGameWeapons.push_back(new CCrossBow);
	m_vGameWeapons[m_uiCurrentWeapon]->Activate();
	Activate();
	m_fxFootsteps.Load("Resource/data/DustFromFeet.xml");
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
	
	m_vGameWeapons[m_uiCurrentWeapon]->Update(fElapsedTime);
	
	// Update the particles
	m_fxFootsteps.Update(fElapsedTime);

	//m_vGameWeapons[m_uiCurrentWeapon]->SetWeaponRotation(GetAnimationPlayer(GetCurrentAnimation())->ReturnWeaponAngle());
	
	//Point TempWepPoint;
	//TempWepPoint.x = GetPosX() - GetAnimationPlayer(GetCurrentAnimation())->ReturnAnchorPoint().x + GetAnimationPlayer(GetCurrentAnimation())->ReturnWeaponPoint().x;
	//TempWepPoint.y = GetPosY() - GetAnimationPlayer(GetCurrentAnimation())->ReturnAnchorPoint().y + GetAnimationPlayer(GetCurrentAnimation())->ReturnWeaponPoint().y;
	//m_vGameWeapons[m_uiCurrentWeapon]->SetWeaponAnchor(TempWepPoint);

	// Fire the particle effect if the position changed
	/*if(ptOldPosition != GetPosition())
	{	
		m_fxFootsteps.emitter.EmitterPosX = GetAnimationPlayer(GetCurrentAnimation())->ReturnAnchorPoint().x + SCREEN_POS_X((float)GetPosX()) ;
		m_fxFootsteps.emitter.EmitterPosY = GetAnimationPlayer(GetCurrentAnimation())->ReturnAnchorPoint().y + SCREEN_POS_Y((float)GetPosY());
		m_fxFootsteps.Fire();
	}*/
}

void CPlayer::Render(void)
{
	// Render the player
	//CBaseCharacter::Render
	m_vGameWeapons[m_uiCurrentWeapon]->Render(GetPosition());
	// Render the particles
	m_fxFootsteps.Render();
}

void CPlayer::Attack(CBaseCharacter* pTarget)
{
	CBaseCharacter::Attack(pTarget);
	m_vGameWeapons[m_uiCurrentWeapon]->Attack();
}

void CPlayer::ChargedAttack(void)
{
	m_vGameWeapons[m_uiCurrentWeapon]->ChargedAttack();
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
	if(CInputManager::GetInstance()->GetAttack())
	{
		m_vGameWeapons[m_uiCurrentWeapon]->SetAttacking(true);
	}
	else
	{
		m_vGameWeapons[m_uiCurrentWeapon]->SetAttacking(false);
	}

	if(m_vGameWeapons[m_uiCurrentWeapon]->GetAttacking())
	{
		switch (m_vGameWeapons[m_uiCurrentWeapon]->GetCurrentAnimation())
		{
		case ANM_WALK_UP:
			{
				m_vGameWeapons[m_uiCurrentWeapon]->SetCurrentAnimation(ANM_ATK_UP);
				break;
			}
		case ANM_WALK_DOWN:
			{
				m_vGameWeapons[m_uiCurrentWeapon]->SetCurrentAnimation(ANM_ATK_DOWN);
				break;
			}
		case ANM_WALK_LEFT:
			{
				m_vGameWeapons[m_uiCurrentWeapon]->SetCurrentAnimation(ANM_ATK_LEFT);
				break;
			}
		case ANM_WALK_RIGHT:
			{
				m_vGameWeapons[m_uiCurrentWeapon]->SetCurrentAnimation(ANM_ATK_RIGHT);
				break;
			}
		case ANM_IDLE_UP:
			{
				m_vGameWeapons[m_uiCurrentWeapon]->SetCurrentAnimation(ANM_ATK_UP);
				break;
			}
		case ANM_IDLE_DOWN:
			{
				m_vGameWeapons[m_uiCurrentWeapon]->SetCurrentAnimation(ANM_ATK_DOWN);
				break;
			}
		case ANM_IDLE_LEFT:
			{
				m_vGameWeapons[m_uiCurrentWeapon]->SetCurrentAnimation(ANM_ATK_LEFT);
				break;
			}
		case ANM_IDLE_RIGHT:
			{
				m_vGameWeapons[m_uiCurrentWeapon]->SetCurrentAnimation(ANM_ATK_RIGHT);
				break;
			}
		}
	}
	else
	{
		switch (m_vGameWeapons[m_uiCurrentWeapon]->GetCurrentAnimation())
		{
		case ANM_ATK_UP:
			{
				m_vGameWeapons[m_uiCurrentWeapon]->SetCurrentAnimation(ANM_WALK_UP);
				break;
			}
		case ANM_ATK_DOWN:
			{
				m_vGameWeapons[m_uiCurrentWeapon]->SetCurrentAnimation(ANM_WALK_DOWN);
				break;
			}
		case ANM_ATK_LEFT:
			{
				m_vGameWeapons[m_uiCurrentWeapon]->SetCurrentAnimation(ANM_WALK_LEFT);
				break;
			}
		case ANM_ATK_RIGHT:
			{
				m_vGameWeapons[m_uiCurrentWeapon]->SetCurrentAnimation(ANM_WALK_RIGHT);
				break;
			}
		}

		if(CInputManager::GetInstance()->GetUp())
		{
			m_vGameWeapons[m_uiCurrentWeapon]->SetCurrentAnimation(ANM_WALK_UP);
			SetVelY(-(float)GetSpeed());
		}
		else if(CInputManager::GetInstance()->GetDown())
		{
			m_vGameWeapons[m_uiCurrentWeapon]->SetCurrentAnimation(ANM_WALK_DOWN);
			SetVelY((float)GetSpeed());
		}
		else
			SetVelY(0);

		if(CInputManager::GetInstance()->GetLeft())
		{
			m_vGameWeapons[m_uiCurrentWeapon]->SetCurrentAnimation(ANM_WALK_LEFT);
			SetVelX(-(float)GetSpeed());
		}
		else if(CInputManager::GetInstance()->GetRight())
		{
			m_vGameWeapons[m_uiCurrentWeapon]->SetCurrentAnimation(ANM_WALK_RIGHT);
			SetVelX((float)GetSpeed());
		}
		else
			SetVelX(0);
		
	}
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
	else
	{
		m_vGameWeapons[m_uiCurrentWeapon]->Deactivate();
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