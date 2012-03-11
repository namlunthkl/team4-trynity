////////////////////////////////////////////////////////////////////////
//    File Name				:	"CPlayer.cpp"
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 3:57 AM
//    Purpose				:	Game player character class definitions
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "../StdAfx.h"
#include "CPlayer.h"
#include "../Messaging/CEventSystem.h"
#include "../Input Manager/CInputManager.h"
#include "../States/CGameplayState.h"
#include "../Weapons/CDagger.h"
#include "../Weapons/CSword.h"
#include "../Weapons/CHammer.h"
#include "../Weapons/CCrossBow.h"
#include "../Camera/CCameraControl.h"
#include "../Tile Mapping/CWorldEngine.h"
#include "../Light System/LightEngine.h"


#define WEAPON m_vGameWeapons[m_uiCurrentWeapon]
// Constructor]
CPlayer::CPlayer(void) : CBaseCharacter()
{
	m_byteWeapons = 0;
	m_byteMasks = 0;
	TurnBitOn(m_byteWeapons, WEAPON_DAGGER);

	m_fOuchTimer = 0.0f;
	m_Potion = new CPotion;
	//	Test the weapons!
	TurnBitOn(m_byteWeapons, WEAPON_SWORD);
	TurnBitOn(m_byteWeapons, WEAPON_HAMMER);
	TurnBitOn(m_byteWeapons, WEAPON_CROSSBOW);

	TurnBitOn(m_byteMasks,MASK_SPEED);
	TurnBitOn(m_byteMasks,MASK_ENDURANCE);
	TurnBitOn(m_byteMasks,MASK_STRENGHT);
	TurnBitOn(m_byteMasks,MASK_LIGHT);
	//	IM 12 AND WHAT IS THIS?
	TurnBitOn(m_byteMasks, MASK_NONE);

	TurnBitOn(m_byteMasks, 0);
	TurnBitOn(m_byteMasks, 1);
	TurnBitOn(m_byteMasks, 2);
	TurnBitOn(m_byteMasks, 3);

	m_bHeartPiece = false;
	m_uiCurrentWeapon = WEAPON_DAGGER;
	m_uiCurrentMask = MASK_NONE;
	m_sndPlayerMovement = -1;
	SetNumPotions(0);
	m_vGameWeapons.push_back(new CDagger);
	m_vGameWeapons[WEAPON_DAGGER]->Activate();
	m_vGameWeapons.push_back(new CSword);
	m_vGameWeapons[WEAPON_SWORD]->Activate();
	m_vGameWeapons.push_back(new CHammer);
	m_vGameWeapons[WEAPON_HAMMER]->Activate();
	m_vGameWeapons.push_back(new CCrossBow);
	m_vGameWeapons[WEAPON_CROSSBOW]->Activate();

	m_bBusy = false;

	//WEAPON->Activate();
	Activate();
	m_fxFootsteps.Load("Resource/data/DustFromFeet.xml");

	m_sndHit = AUDIO->SFXLoadSound("resource/sound/Hit.wav");

	m_sndPotion = new Sound();
	m_sndPotion->Load("resource/sound/potion.wav");
	m_sndSwitchAmulet = new Sound();
	m_sndSwitchAmulet->Load("resource/sound/select.wav");
	m_sndSwitchWeapon = new Sound();
	m_sndSwitchWeapon->Load("resource/sound/selectweapon.wav");
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
	if(m_fOuchTimer > 0.0f)
		m_fOuchTimer -= fElapsedTime;
	if( m_fOuchTimer < 0.0f )
	{
		m_fOuchTimer = 0.0f;
	}
	
	if(m_uiCurrentMask == MASK_SPEED)
	{
		m_nSpeedIncrease = 2;
		
	}
	else
	{
		m_nSpeedIncrease = 1;
	}
	
	if(m_uiCurrentMask == MASK_STRENGHT)
	{
		m_nDamageIncrease = 2;
	}
	else
	{
		m_nDamageIncrease = 1;
	}

	if(m_uiCurrentMask == MASK_ENDURANCE)
	{
		m_bDamageDecrease = true;
	}
	else
	{
		m_bDamageDecrease = false;
	}

	if(m_uiCurrentMask == MASK_LIGHT)
	{
		LightEngine::GetInstance()->SetPlayerPointLight(true);
	}
	else
	{
		LightEngine::GetInstance()->SetPlayerPointLight(false);
	}

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
	LightEngine::GetInstance()->SetPlayerPointPos( (float)GetPosX(), (float)GetPosY() );

	// Fire the particle effect if the position changed
	if(ptOldPosition != GetPosition())
	{
		m_fxFootsteps.emitter.EmitterPosX = (float)(GetAnchorPoint().x + GetPosX()-25);
		m_fxFootsteps.emitter.EmitterPosY = (float)(GetAnchorPoint().y + GetPosY()-16);
		m_fxFootsteps.Fire();
	}
}

void CPlayer::Render(void)
{
	// Render the player
	//
	//
	if( CPlayer::GetInstance()->m_fOuchTimer == 0.0f )
	{
		WEAPON->Render(GetPosition());
	}
	// Render the particles
	m_fxFootsteps.Render();
	
	//D3D->GetSprite()->Flush();
	//RectD rect = GetCollisionRect();
	//rect.OffsetRect(CCameraControl::GetInstance()->GetPositionX(),
	//	CCameraControl::GetInstance()->GetPositionY());
	//D3D->DrawRect(rect.GetWindowsRECT(), 255, 0, 0);

	RectD temp = WEAPON->GetCollisionRect();
	temp.OffsetRect(GetPosX(),GetPosY());
	temp.OffsetRect(CCameraControl::GetInstance()->GetPositionX(),
		CCameraControl::GetInstance()->GetPositionY());

	if(m_uiCurrentWeapon == WEAPON_SWORD)
	{
		D3D->DrawRect(temp.GetWindowsRECT(), 255, 69, 0);
	}
	else if(m_uiCurrentWeapon == WEAPON_DAGGER)
	{
		D3D->DrawRect(temp.GetWindowsRECT(), 255, 255, 0);
	}
	else if(m_uiCurrentWeapon == WEAPON_HAMMER)
	{
		D3D->DrawRect(temp.GetWindowsRECT(), 139, 69, 19);
	}
	else if(m_uiCurrentWeapon == WEAPON_CROSSBOW)
	{
		D3D->DrawRect(temp.GetWindowsRECT(), 30, 154, 255);
	}
}

void CPlayer::Attack(void)
{
	if(IsBusy())
		return;

	if( m_fOuchTimer == 0.0f )
	{
		//CBaseCharacter::Attack();
		WEAPON->Attack();
	}
}

void CPlayer::ChargedAttack(void)
{
	if( m_fOuchTimer == 0.0f )
	{
		WEAPON->ChargedAttack();
		// TODO: Create charged attack effect in here
		// TODO: Send any needed event
	}
}

void CPlayer::Die(void)
{
	CBaseCharacter::Die();
	CEventSystem::GetInstance()->SendEvent("game.over");
}

// Get input for the player
void CPlayer::Input(void)
{
	if(IsBusy())
		return;

	if(CInputManager::GetInstance()->GetAttack())
	{
		WEAPON->SetAttacking(true);
	}
	else
	{
		WEAPON->SetAttacking(false);
	}

	if(CInputManager::GetInstance()->GetY())
	{
		UsePotion();
	}

	//if i get hurt, stop my attack
	if( m_fOuchTimer > 0.0f )
		WEAPON->SetAttacking(false);

	if(WEAPON->GetAttacking())
	{
		SetVelX(0);
		SetVelY(0);
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
		Attack();
		//if(CInputManager::GetInstance()->Timeheld() > 0.5f)
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
			SetVelY(-(float)GetSpeed()*m_nSpeedIncrease);
		}
		else if(CInputManager::GetInstance()->GetDown())
		{
			WEAPON->SetCurrentAnimation(ANM_WALK_DOWN);
			SetVelY((float)GetSpeed()*m_nSpeedIncrease);
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
			SetVelX(-(float)GetSpeed() * m_nSpeedIncrease);
		}
		else if(CInputManager::GetInstance()->GetRight())
		{
			WEAPON->SetCurrentAnimation(ANM_WALK_RIGHT);
			SetVelX((float)GetSpeed() * m_nSpeedIncrease);
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

	m_sndSwitchWeapon->Play();
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

	m_sndSwitchAmulet->Play();
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
	RECT rectCollisionResult = { 0, 0, 0, 0 };
	CBaseObject* pBaseObject = (CBaseObject*)pObject;

	if(IntersectRect(&rectCollisionResult, &GetCollisionRect().GetWindowsRECT(), &pBaseObject->GetCollisionRect().GetWindowsRECT()))
	{
		int nRectWidth = rectCollisionResult.right - rectCollisionResult.left;
		int nRectHeight = rectCollisionResult.bottom - rectCollisionResult.top;
		double dAnmHeight = GetCollisionRect().bottom - GetCollisionRect().top;
		double dAnmWidth = GetCollisionRect().right - GetCollisionRect().left;
		if(nRectWidth > nRectHeight)
		{
			// Top/Down Collision
			if(GetCollisionRect().top < pBaseObject->GetCollisionRect().top)
			{
				if(GetVelY() > 0)
					SetPosY(rectCollisionResult.top + GetAnchorPoint().y - dAnmHeight);
			}
			else if(GetCollisionRect().bottom > pBaseObject->GetCollisionRect().bottom)
			{
				if(GetVelY() < 0)
					SetPosY(rectCollisionResult.bottom + GetAnchorPoint().y);
			}
		}
		if(nRectHeight > nRectWidth)
		{
			// Side Collision
			if(GetCollisionRect().left < pBaseObject->GetCollisionRect().left)
			{
				if(GetVelX() > 0)
					SetPosX(rectCollisionResult.left + GetAnchorPoint().x - dAnmWidth);
			}
			else if(GetCollisionRect().right > pBaseObject->GetCollisionRect().right)
			{
				if(GetVelX() < 0)
					SetPosX(rectCollisionResult.right + GetAnchorPoint().x);
			}
		}		
	}


	if(WEAPON->GetAttacking() == true && pObject->GetType() == TYPE_CHAR_ENEMY)
	{
		CEnemy* pEnemy = (CEnemy*)pObject;
		RectD WeaponCollisionRect = WEAPON->GetCollisionRect();
		WeaponCollisionRect.OffsetRect(GetPosX(),GetPosY());
		RECT temp2;

		if(IntersectRect(&temp2,&WeaponCollisionRect.GetWindowsRECT(),&pObject->GetCollisionRect().GetWindowsRECT()) != 0)
		{
			pEnemy->SufferDamage(GetAttackDamage()*m_nDamageIncrease);
		}
		int x = 0;
	}
	return true;
}

bool CPlayer::CheckWorldCollision(void)
{
	if(WEAPON->GetAttacking() == true)
	{
		RectD WeaponCollisionRect = WEAPON->GetCollisionRect();
		WeaponCollisionRect.OffsetRect(GetPosX(),GetPosY());
		unsigned int WeaponType = WEAPON->GetType();

		return WORLD->CheckCollisions(nullptr, &WeaponCollisionRect, WeaponType);
	}
	return false;
}

RectD CPlayer::GetWeaponRect(void)
{
	WEAPON->GetCollisionRect();
	m_weaponRect.OffsetRect(GetPosX(),GetPosY());
	return m_weaponRect;
}
// Destructor
CPlayer::~CPlayer(void)
{
}
const char* CPlayer::GetRegion(void) const
{
	return CWorldEngine::GetInstance()->GetRegionName(GetPosX(), GetPosY());
}
void CPlayer::SufferDamage(unsigned int uiDamage)
{
	if( m_fOuchTimer > 0.0f == false)
	{
		if(m_bDamageDecrease == true)
		{
			if(uiDamage > 1)
				CBaseCharacter::SufferDamage(uiDamage-1);
			else
			{
				if(rand()%2 == 0)
					CBaseCharacter::SufferDamage(0);
				else
					CBaseCharacter::SufferDamage(1);
			}
		}
		else
		{
			CBaseCharacter::SufferDamage(uiDamage);
		}
		if(m_sndHit != -1)
				AUDIO->SFXPlaySound(m_sndHit);
	}
}
void CPlayer::UsePotion(void)
{
	if(GetNumPotions() > 0 )
	{
		if(GetCurHealth() < GetMaxHealth())
		{
			//m_Potion->Heal();
			SetCurHealth( GetCurHealth() + 1 );
			SetNumPotions(GetNumPotions()-1);
			
			m_sndPotion->Play();
		}
	}
}