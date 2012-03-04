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
#include "../Camera/CCameraControl.h"
#define WEAPON m_vGameWeapons[m_uiCurrentWeapon]
// Constructor]
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
	WEAPON->Activate();
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
	if( CCameraControl::GetInstance()->GetKillCam() == false )
	{
		CCameraControl::GetInstance()->ChargeCamSequence(CInputManager::GetInstance()->Timeheld());
	}
	// Store the old position of the player for future checks
	PointD ptOldPosition = GetPosition();

	// Call Base Character's update method to move the player
	
	CBaseCharacter::Update(fElapsedTime);
	
	WEAPON->Update(fElapsedTime);
	
	// Update the particles
	m_fxFootsteps.Update(fElapsedTime);


	//WEAPON->SetWeaponRotation(GetAnimationPlayer(GetCurrentAnimation())->ReturnWeaponAngle());
	
	//Point TempWepPoint;
	//TempWepPoint.x = GetPosX() - GetAnimationPlayer(GetCurrentAnimation())->ReturnAnchorPoint().x + GetAnimationPlayer(GetCurrentAnimation())->ReturnWeaponPoint().x;
	//TempWepPoint.y = GetPosY() - GetAnimationPlayer(GetCurrentAnimation())->ReturnAnchorPoint().y + GetAnimationPlayer(GetCurrentAnimation())->ReturnWeaponPoint().y;
	//WEAPON->SetWeaponAnchor(TempWepPoint);

	// Fire the particle effect if the position changed
	if(ptOldPosition != GetPosition())
	{
		m_fxFootsteps.emitter.EmitterPosX = WEAPON->GetAnimationPlayer(WEAPON->GetCurrentAnimation())->ReturnAnchorPoint().x + GetPosX();
		m_fxFootsteps.emitter.EmitterPosY = WEAPON->GetAnimationPlayer(WEAPON->GetCurrentAnimation())->ReturnAnchorPoint().y + GetPosY();
		m_fxFootsteps.Fire();
	}
}

void CPlayer::Render(void)
{
	// Render the player
	// 
	// 

	//CBaseCharacter::Render
	WEAPON->Render(GetPosition());
	// Render the particles
	m_fxFootsteps.Render();
}

void CPlayer::Attack(void)
{
	CBaseCharacter::Attack();
	WEAPON->Attack();
}

void CPlayer::ChargedAttack(void)
{
	
	WEAPON->ChargedAttack();
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
		WEAPON->SetAttacking(true);
		//if(rand()%100 == 1)
		//	CCameraControl::GetInstance()->SetKillCam(true);
	}
	else
	{
		WEAPON->SetAttacking(false);
	}

	if(WEAPON->GetAttacking())
	{
		switch (WEAPON->GetCurrentAnimation())
		{
		case ANM_WALK_UP:
			{
				WEAPON->SetCurrentAnimation(ANM_ATK_UP);
				WEAPON->SetPreviousAnimation(ANM_WALK_UP);
				break;
			}
		case ANM_WALK_DOWN:
			{
				WEAPON->SetCurrentAnimation(ANM_ATK_DOWN);
				WEAPON->SetPreviousAnimation(ANM_WALK_DOWN);
				break;
			}
		case ANM_WALK_LEFT:
			{
				WEAPON->SetCurrentAnimation(ANM_ATK_LEFT);
				WEAPON->SetPreviousAnimation(ANM_WALK_LEFT);
				break;
			}
		case ANM_WALK_RIGHT:
			{
				WEAPON->SetCurrentAnimation(ANM_ATK_RIGHT);
				WEAPON->SetPreviousAnimation(ANM_WALK_RIGHT);
				break;
			}
		case ANM_IDLE_UP:
			{
				WEAPON->SetCurrentAnimation(ANM_ATK_UP);
				WEAPON->SetPreviousAnimation(ANM_IDLE_UP);
				break;
			}
		case ANM_IDLE_DOWN:
			{
				WEAPON->SetCurrentAnimation(ANM_ATK_DOWN);
				WEAPON->SetPreviousAnimation(ANM_IDLE_DOWN);
				break;
			}
		case ANM_IDLE_LEFT:
			{
				WEAPON->SetCurrentAnimation(ANM_ATK_LEFT);
				WEAPON->SetPreviousAnimation(ANM_IDLE_LEFT);
				break;
			}
		case ANM_IDLE_RIGHT:
			{
				WEAPON->SetCurrentAnimation(ANM_ATK_RIGHT);
				WEAPON->SetPreviousAnimation(ANM_IDLE_RIGHT);
				break;
			}
		}
		
		//if(CInputManager::GetInstance()->Timeheld() > 2.0f)
		//{
		//	if(WEAPON->GetAnimationPlayer(WEAPON->GetCurrentAnimation())->GetPaused() != true)
		//		WEAPON->GetAnimationPlayer(WEAPON->GetCurrentAnimation())->Pause();
		//	
		//}
	}
	else
	{
		//if(attacked == true)
		//{
		//	if(CInputManager::GetInstance()->Timeheld() > 0.5f)
		//	{
		//		WEAPON->GetAnimationPlayer(GetCurrentAnimation())->Pause();
		//		ChargedAttack();
		//	}
		//	else
		//	{
		//		Attack();
		//	}
		//}
		
		if (WEAPON->GetCurrentAnimation() == ANM_ATK_UP || WEAPON->GetCurrentAnimation() == ANM_ATK_DOWN ||
			WEAPON->GetCurrentAnimation() == ANM_ATK_LEFT || WEAPON->GetCurrentAnimation() == ANM_ATK_RIGHT)
		{
			WEAPON->SetCurrentAnimation(WEAPON->GetPreviousAnimation());
		}
		
		SetPrevVelX(GetVelX());
		SetPrevVelY(GetVelY());
		if(CInputManager::GetInstance()->GetUp())
		{
			WEAPON->SetCurrentAnimation(ANM_WALK_UP);
			SetVelY(-(float)GetSpeed());
		}
		else if(CInputManager::GetInstance()->GetDown())
		{
			WEAPON->SetCurrentAnimation(ANM_WALK_DOWN);
			SetVelY((float)GetSpeed());
		}
		else
		{
			SetVelY(0);
			if(GetPrevVelY() < 0)
				WEAPON->SetCurrentAnimation(ANM_IDLE_UP);
			else if(GetPrevVelY() > 0)
				WEAPON->SetCurrentAnimation(ANM_IDLE_DOWN);
		}
			

		if(CInputManager::GetInstance()->GetLeft())
		{
			WEAPON->SetCurrentAnimation(ANM_WALK_LEFT);
			SetVelX(-(float)GetSpeed());
		}
		else if(CInputManager::GetInstance()->GetRight())
		{
			WEAPON->SetCurrentAnimation(ANM_WALK_RIGHT);
			SetVelX((float)GetSpeed());
		}
		else
		{
			SetVelX(0);
			if(GetPrevVelX() > 0)
				WEAPON->SetCurrentAnimation(ANM_IDLE_RIGHT);
			else if(GetPrevVelX() < 0)
				WEAPON->SetCurrentAnimation(ANM_IDLE_LEFT);
		}
		
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
		WEAPON->Deactivate();
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
bool CPlayer::CheckCollision(IBaseInterface* pObject)
{

	if(pObject->GetType() == TYPE_CHAR_NPC)
	{
		RECT temp,temp2;
		temp = WEAPON->GetAnimationPlayer(WEAPON->GetCurrentAnimation())->ReturnWeaponCollisionRect();
		temp.left += WEAPON->GetAnimationPlayer(WEAPON->GetCurrentAnimation())->ReturnFrameRect().left;
		temp.right += WEAPON->GetAnimationPlayer(WEAPON->GetCurrentAnimation())->ReturnFrameRect().right;
		temp.top += WEAPON->GetAnimationPlayer(WEAPON->GetCurrentAnimation())->ReturnFrameRect().top;
		temp.bottom += WEAPON->GetAnimationPlayer(WEAPON->GetCurrentAnimation())->ReturnFrameRect().bottom;

		if(IntersectRect(&temp2,&temp,&pObject->GetCollisionRect().GetWindowsRECT()) != 0)
		{
			CMessageSystem::GetInstance()->SendMsg(new CDestroyNPCMessage((CNPC*)pObject));
		}
	}
	return CBaseObject::CheckCollision(pObject);

}
// Destructor
CPlayer::~CPlayer(void)
{

}

const char* CPlayer::GetRegion(void) const
{
	return CWorldEngine::GetInstance()->GetMapWherePointIs(GetPosX(), GetPosY());
}