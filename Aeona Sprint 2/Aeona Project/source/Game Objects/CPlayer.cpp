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
#include "../Game Objects/CFinalBoss.h"
// Constructor
CPlayer::CPlayer(void) : CBaseCharacter()
{
	m_byteWeapons = 0;
	m_byteMasks = 0;
	TurnBitOn(m_byteWeapons, WEAPON_DAGGER);
	TurnBitOn(m_byteMasks, MASK_NONE);
	m_fOuchTimer = 0.0f;
	//m_Potion = new CPotion;

	m_bHasFlower = false;
	m_uiGems = 0;

	rotation = 0.0f;	//	this is for the rotating effect and rotation direction (north-south, east-west) on charged attacks.

#if 1
	TurnBitOn(m_byteMasks,MASK_SPEED);
	TurnBitOn(m_byteMasks,MASK_ENDURANCE);
	TurnBitOn(m_byteMasks,MASK_STRENGHT);
	TurnBitOn(m_byteMasks,MASK_LIGHT);
	
	TurnBitOn(m_byteWeapons, WEAPON_SWORD);
	TurnBitOn(m_byteWeapons, WEAPON_HAMMER);
	TurnBitOn(m_byteWeapons, WEAPON_CROSSBOW);
	//	Test the weapons!
#endif

	m_bHeartPiece = false;
	m_uiCurrentWeapon = WEAPON_DAGGER;
	m_uiCurrentMask = MASK_NONE;
	m_sndPlayerMovement = -1;
	m_uiNumPotions = 0;
	m_bPhilCharging = false;
	m_bHammerCircle = false;
	m_bPhilSpecialAttack = false;
	m_fPhilChargeIdkman = 0.0f;
	m_imgCharges = TEX_MNG->LoadTexture("resource/Charges.png", D3DCOLOR_XRGB(255, 0, 255));
	m_fBlastTimer = 0.0f;

	m_vGameWeapons.push_back(new CDagger);
	m_vGameWeapons[WEAPON_DAGGER]->Activate();
	m_vGameWeapons[WEAPON_DAGGER]->SetCurrentAnimation(ANM_IDLE_UP);
	m_vGameWeapons.push_back(new CSword);
	m_vGameWeapons[WEAPON_SWORD]->Activate();
	m_vGameWeapons[WEAPON_SWORD]->SetCurrentAnimation(ANM_IDLE_UP);
	m_vGameWeapons.push_back(new CHammer);
	m_vGameWeapons[WEAPON_HAMMER]->Activate();
	m_vGameWeapons[WEAPON_HAMMER]->SetCurrentAnimation(ANM_IDLE_UP);
	m_vGameWeapons.push_back(new CCrossBow);
	m_vGameWeapons[WEAPON_CROSSBOW]->Activate();
	m_vGameWeapons[WEAPON_CROSSBOW]->SetCurrentAnimation(ANM_IDLE_UP);

	m_bBusy = false;

	Activate();
	// PARTICLE WEAPON
	m_fxElementalWeapon.Load("Resource/data/ParticleWeapon.xml");

	m_sndHit = AUDIO->SFXLoadSound("resource/sound/Hit.wav");

	m_sndPotion = new Sound();
	m_sndPotion->Load("resource/sound/potion.wav");
	m_sndSwitchAmulet = new Sound();
	m_sndSwitchAmulet->Load("resource/sound/select.wav");
	m_sndSwitchWeapon = new Sound();
	m_sndSwitchWeapon->Load("resource/sound/selectweapon.wav");
}


void CPlayer::Reset(void)
{
	m_byteWeapons = 0;
	m_byteMasks = 0;
	TurnBitOn(m_byteWeapons, WEAPON_DAGGER);
	TurnBitOn(m_byteMasks, MASK_NONE);
	m_fOuchTimer = 0.0f;
	m_Potion = new CPotion;
	m_bHasFlower = false;
	m_uiGems = 0;

	m_bHeartPiece = false;
	m_uiCurrentWeapon = WEAPON_DAGGER;
	m_uiCurrentMask = MASK_NONE;
	m_sndPlayerMovement = -1;
	m_uiNumPotions = 0;
	m_bPhilCharging = false;
	m_bPhilSpecialAttack = false;
	m_fPhilChargeIdkman = 0.0f;

	m_vGameWeapons.push_back(new CDagger);
	m_vGameWeapons[WEAPON_DAGGER]->Activate();
	m_vGameWeapons[WEAPON_DAGGER]->SetCurrentAnimation(ANM_IDLE_UP);
	m_vGameWeapons.push_back(new CSword);
	m_vGameWeapons[WEAPON_SWORD]->Activate();
	m_vGameWeapons[WEAPON_SWORD]->SetCurrentAnimation(ANM_IDLE_UP);
	m_vGameWeapons.push_back(new CHammer);
	m_vGameWeapons[WEAPON_HAMMER]->Activate();
	m_vGameWeapons[WEAPON_HAMMER]->SetCurrentAnimation(ANM_IDLE_UP);
	m_vGameWeapons.push_back(new CCrossBow);
	m_vGameWeapons[WEAPON_CROSSBOW]->Activate();
	m_vGameWeapons[WEAPON_CROSSBOW]->SetCurrentAnimation(ANM_IDLE_UP);

	m_bBusy = false;
	m_bTrulyDead = false;
	m_bDying = false;
	Activate();
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
		m_fOuchTimer = 0.0f;

	if(m_fBlastTimer > 0.0f)
		m_fBlastTimer -= fElapsedTime;
	if(m_fBlastTimer < 0.0f)
		m_fBlastTimer = 0.0f;

	if(m_uiCurrentWeapon == WEAPON_SWORD || m_uiCurrentWeapon == WEAPON_HAMMER)
	{
		rotation -= fElapsedTime;
		if(rotation < (3.14159f * -2.0f) )
			rotation = 0.0f;
	}

	if(m_uiCurrentMask == MASK_SPEED)
		m_fSpeedIncrease = 1.5;
	else
		m_fSpeedIncrease = 1;

	if(m_uiCurrentMask == MASK_STRENGHT)
		m_nDamageIncrease = 2;
	else
		m_nDamageIncrease = 1;

	if(m_uiCurrentMask == MASK_ENDURANCE)
		m_bDamageDecrease = true;
	else
		m_bDamageDecrease = false;

	if(m_uiCurrentMask == MASK_LIGHT)
		LightEngine::GetInstance()->SetPlayerPointLight(true);
	else
		LightEngine::GetInstance()->SetPlayerPointLight(false);

	if( CCameraControl::GetInstance()->GetKillCam() == false )
		CCameraControl::GetInstance()->ChargeCamSequence(this->m_fPhilChargeIdkman);
		//CCameraControl::GetInstance()->ChargeCamSequence(CInputManager::GetInstance()->Timeheld());
	// Store the old position of the player for future checks
	PointD ptOldPosition = GetPosition();

	// Call Base Character's update method to move the player

	CBaseCharacter::Update(fElapsedTime);

	WEAPON->Update(fElapsedTime);

	// Update the particles
	m_fxElementalWeapon.Update(fElapsedTime);
	LightEngine::GetInstance()->SetPlayerPointPos( (float)GetPosX(), (float)GetPosY() );
}

void CPlayer::Render(void)
{
	RECT shadow;
	shadow.left = 512-32;
	shadow.top = 0;
	shadow.right = 512;
	shadow.bottom = 32;

	TEX_MNG->Draw(GAME->m_imgEnemiesDeath, (int)GetPosX() -(16)/*- (48*scale)*/, (int)GetPosY() -(16)/*- (48*scale)*/, 1.0f, 1.0f, &shadow, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(100, 255, 255, 255));

	// Render the player
	//
	//
	if( CPlayer::GetInstance()->m_fOuchTimer == 0.0f )
	{
		bool showplayer = false;
		if(m_uiCurrentWeapon == WEAPON_HAMMER && m_fBlastTimer > 0.0f)
			showplayer = false;
		else if(m_uiCurrentWeapon == WEAPON_SWORD && m_fBlastTimer > 0.0f)
			showplayer = false;
		else
			showplayer = true;

		


		//begin shit for rendering charge crap below
		if(m_fBlastTimer > 0.0f || m_bHammerCircle == true)
		{
			RECT r;
			r.left = 0;
			r.right = 1;
			r.top = 0;
			r.bottom = 1;
			
			int ox = 0;
			int oy = 0;

			if(m_uiCurrentWeapon == WEAPON_DAGGER || m_uiCurrentWeapon == WEAPON_CROSSBOW)
			{
				switch(WEAPON->GetCurrentAnimation())
				{
				case ANM_WALK_UP:
				case ANM_IDLE_UP:
				case ANM_ATK_UP:
					rotation = 3.14159f/2.0f;
					break;
				case ANM_WALK_DOWN:
				case ANM_IDLE_DOWN:
				case ANM_ATK_DOWN:
					rotation = 3.14159f/2.0f;
					break;
				case ANM_WALK_LEFT:
				case ANM_IDLE_LEFT:
				case ANM_ATK_LEFT:
					rotation = 0.0f;
					break;
				case ANM_WALK_RIGHT:
				case ANM_IDLE_RIGHT:
				case ANM_ATK_RIGHT:
					rotation = 0.0f;
					break;
				default:
					rotation = 0.0f;
				}
			}
			else if(m_uiCurrentWeapon == WEAPON_HAMMER && m_bHammerCircle == false)
			{
				rotation = 0.0f;
			}

			if(GetCurrentWeapon() == 0)			//dagger
			{
				r.left = 0;
				r.right = 240;
				r.top = 0;
				r.bottom = 60;
				ox = 120;
				oy = 30;
			}
			else if(GetCurrentWeapon() == 1)	//sword
			{
				r.left = 0;
				r.right = 200;
				r.top = 60;
				r.bottom = 60+200;
				ox = 100;
				oy = 100;
			}
			else if(GetCurrentWeapon() == 2)	//hammer
			{
				r.left = 0;
				r.right = 220;
				r.top = 60+200+220;
				r.bottom = 60+200+220+220;
				ox = 110;
				oy = 110;
			}
			else if(GetCurrentWeapon() == 3)	//bow
			{
				r.left = 240;
				r.right = 240+48;
				r.top = 0;
				r.bottom = 1000;
				if(rotation == 0.0f)
					rotation = 3.14159f/2.0f;
				else
					rotation = 0.0f;
				ox = 24;
				oy = 500;
			}

			if(m_bHammerCircle == true)
			{
				r.left = 0;
				r.right = 220;
				r.top = 60+200;
				r.bottom = 60+200+220;
				ox = 110;
				oy = 110;
			}

			if(m_uiCurrentWeapon == WEAPON_DAGGER || m_uiCurrentWeapon == WEAPON_CROSSBOW)
				TEX_MNG->Draw(m_imgCharges, GetPosX()-ox, GetPosY()-oy, 1.0f, 1.0f, &r, 0.0f+ox, 0.0f+oy, rotation);
			else if(m_uiCurrentWeapon == WEAPON_SWORD)
				TEX_MNG->Draw(m_imgCharges, GetPosX()-ox, GetPosY()-oy, 1.0f, 1.0f, &r, 0.0f+ox, 0.0f+oy, rotation*13);
			else if(m_uiCurrentWeapon == WEAPON_HAMMER && m_bHammerCircle == true)
				TEX_MNG->Draw(m_imgCharges, GetPosX()-ox, GetPosY()-oy, 1.0f, 1.0f, &r, 0.0f+ox, 0.0f+oy, rotation*3, D3DCOLOR_ARGB(205,255,255,255));
			else
				TEX_MNG->Draw(m_imgCharges, GetPosX()-ox, GetPosY()-oy, 1.0f, 1.0f, &r, 0.0f+ox, 0.0f+oy, rotation );
		}
		//end render of charge stuff.

		//DRAW THE PLAYER HERE
		if(showplayer == true)
		WEAPON->Render(GetPosition());
		//DRAW THE PLAYER HERE
	}
	else
	{
		WEAPON->Render(GetPosition(),D3DCOLOR_ARGB(155,255,0,0));
	}

	// Render the particles
	m_fxElementalWeapon.Render();

	//D3D->GetSprite()->Flush();
	//RectD rect = GetCollisionRect();
	//rect.OffsetRect(CCameraControl::GetInstance()->GetPositionX(),
	//	CCameraControl::GetInstance()->GetPositionY());
	//D3D->DrawRect(rect.GetWindowsRECT(), 0, 255, 0);

	RectD temp = WEAPON->GetCollisionRect();
	temp.OffsetRect(GetPosX(),GetPosY());
	temp.OffsetRect(CCameraControl::GetInstance()->GetPositionX(), CCameraControl::GetInstance()->GetPositionY());

#ifdef _DEBUG
	if(false) //if(IsOnDebug())
	{
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

	D3D->GetSprite()->Flush();

	//if(GetPosX() != GetInteractivePoint().x)
	//	int x = 0;

	D3D->DrawLine((int)GetScreenPosX(GetPosX()), (int)GetScreenPosY(GetPosY()),
		(int)GetScreenPosX(GetInteractivePoint().x), (int)GetScreenPosY(GetInteractivePoint().y), 255, 0, 0);

	temp = GetInteractiveRect();
	temp.OffsetRect(CCameraControl::GetInstance()->GetPositionX(), CCameraControl::GetInstance()->GetPositionY());
	D3D->DrawRect(temp.GetWindowsRECT(), 255, 0, 0);
#endif
}

void CPlayer::Attack(void)
{
	if(IsBusy())
		return;

	if( m_fOuchTimer == 0.0f )
	{
		m_fPhilChargeIdkman = 0.0f;	//	Set it to 0.0f when we begin an attack, cus we either are not charging, or we just Attack()'d a charged attack, so set it back to 0.0f anyway.
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
	WEAPON->SetCurrentAnimation(ANM_DIE_DIE);
}

// Get input for the player
void CPlayer::Input(void)
{
	if(IsBusy())
		return;

	
	// This If Check is breaking the attacks for bow and hammer fyi - NO ITS NOT, UR LYING U BUTTNOSE!
	if(m_bPhilCharging == false)
	{
		CCameraControl::GetInstance()->SetReleaseButton(true);
		if(WEAPON->GetAttacking() == false)
		{
			if(CInputManager::GetInstance()->GetAttack())
				WEAPON->SetAttacking(true);
			else
				WEAPON->SetAttacking(false);
		}
	}
	//only for charge attack timer.
	if(CInputManager::GetInstance()->GetAttack() == true)
	{
		m_bPhilCharging = true;
	}
	else
	{
		m_bPhilCharging = false;
		if(m_fPhilChargeIdkman > 0.0f)
		{
			if(m_fPhilChargeIdkman < 1.0f)
			{
				m_fPhilChargeIdkman = 0.0f;
				WEAPON->SetAttacking(true);
			}
			else
			{
				m_fPhilChargeIdkman = 0.0f;
				m_bPhilSpecialAttack = true;
				WEAPON->SetAttacking(true);
			}
		}
	}

	if(CInputManager::GetInstance()->GetY())
	{
		UsePotion();
	}
	if( CInputManager::GetInstance()->GetPressedA() )
	{
		if( m_uiCurrentWeapon == WEAPON_SWORD )
		{
			m_fxElementalWeapon.emitter.EmitterPosX = (float)(GetAnchorPoint().x + GetPosX() - 40.0f );
			m_fxElementalWeapon.emitter.EmitterPosY = (float)(GetAnchorPoint().y + GetPosY() - 80.0f );
			m_fxElementalWeapon.emitter.ColorStartR = 255;
			m_fxElementalWeapon.emitter.ColorStartG = 0;
			m_fxElementalWeapon.emitter.ColorStartB = 0;
			m_fxElementalWeapon.emitter.ColorEndR = 200;
			m_fxElementalWeapon.emitter.ColorEndG = 0;
			m_fxElementalWeapon.emitter.ColorEndB = 0;
			m_fxElementalWeapon.Fire();
		}
		if( m_uiCurrentWeapon == WEAPON_HAMMER )
		{
			m_fxElementalWeapon.emitter.EmitterPosX = (float)(GetAnchorPoint().x + GetPosX() - 40.0f );
			m_fxElementalWeapon.emitter.EmitterPosY = (float)(GetAnchorPoint().y + GetPosY() - 80.0f );
			m_fxElementalWeapon.emitter.ColorStartR = 0;
			m_fxElementalWeapon.emitter.ColorStartG = 255;
			m_fxElementalWeapon.emitter.ColorStartB = 0;
			m_fxElementalWeapon.emitter.ColorEndR = 0;
			m_fxElementalWeapon.emitter.ColorEndG = 200;
			m_fxElementalWeapon.emitter.ColorEndB = 0;
			m_fxElementalWeapon.Fire();
		}
		if( m_uiCurrentWeapon == WEAPON_CROSSBOW )
		{
			m_fxElementalWeapon.emitter.EmitterPosX = (float)(GetAnchorPoint().x + GetPosX() - 40.0f );
			m_fxElementalWeapon.emitter.EmitterPosY = (float)(GetAnchorPoint().y + GetPosY() - 80.0f );
			m_fxElementalWeapon.emitter.ColorStartR = 0;
			m_fxElementalWeapon.emitter.ColorStartG = 0;
			m_fxElementalWeapon.emitter.ColorStartB = 255;
			m_fxElementalWeapon.emitter.ColorEndR = 0;
			m_fxElementalWeapon.emitter.ColorEndG = 0;
			m_fxElementalWeapon.emitter.ColorEndB = 200;
			m_fxElementalWeapon.Fire();
		}
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
				WEAPON->SetPreviousAnimation(ANM_IDLE_UP);
				break;
			}
		case ANM_WALK_DOWN:
			{
				WEAPON->SetCurrentAnimation(ANM_ATK_DOWN);
				WEAPON->SetPreviousAnimation(ANM_IDLE_DOWN);
				break;
			}
		case ANM_WALK_LEFT:
			{
				WEAPON->SetCurrentAnimation(ANM_ATK_LEFT);
				WEAPON->SetPreviousAnimation(ANM_IDLE_LEFT);
				break;
			}
		case ANM_WALK_RIGHT:
			{
				WEAPON->SetCurrentAnimation(ANM_ATK_RIGHT);
				WEAPON->SetPreviousAnimation(ANM_IDLE_RIGHT);
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
	else if(WEAPON->GetCurrentAnimation() == ANM_DIE_DIE)
	{
		SetVelX(0);
		SetVelY(0);
		if(WEAPON->GetAnimationPlayer(WEAPON->GetCurrentAnimation())->GetFrameNumber() == 3)
			CEventSystem::GetInstance()->SendEvent("game.over");
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

		if (WEAPON->GetCurrentAnimation() == ANM_ATK_UP || WEAPON->GetCurrentAnimation() == ANM_ATK_DOWN || WEAPON->GetCurrentAnimation() == ANM_ATK_LEFT || WEAPON->GetCurrentAnimation() == ANM_ATK_RIGHT)
		{
			WEAPON->GetAnimationPlayer(WEAPON->GetCurrentAnimation())->Reset();
			WEAPON->SetCurrentAnimation(WEAPON->GetPreviousAnimation());
			WEAPON->SetAttacking(false);
		}

		SetPrevVelX(GetVelX());
		SetPrevVelY(GetVelY());
		if(CInputManager::GetInstance()->GetUp())
		{
			WEAPON->SetCurrentAnimation(ANM_WALK_UP);
			SetVelY(-(float)GetSpeed()*m_fSpeedIncrease);
		}
		else if(CInputManager::GetInstance()->GetDown())
		{
			WEAPON->SetCurrentAnimation(ANM_WALK_DOWN);
			SetVelY((float)GetSpeed()*m_fSpeedIncrease);
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
			SetVelX(-(float)GetSpeed() * m_fSpeedIncrease);
		}
		else if(CInputManager::GetInstance()->GetRight())
		{
			WEAPON->SetCurrentAnimation(ANM_WALK_RIGHT);
			SetVelX((float)GetSpeed() * m_fSpeedIncrease);
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
	WEAPON->m_fSlashTimer = 0.0f;
	// Increase the current weapon variable
	++m_uiCurrentWeapon;

	// If we reached max, go back to the first one
	if(m_uiCurrentWeapon >= WEAPON_MAX)
		m_uiCurrentWeapon = WEAPON_DAGGER;

	// If it doesn't have the weapon
	if(!TestBit(m_byteWeapons, m_uiCurrentWeapon))
	{
		// Keep looking
		CycleWeapon();
	}

	StopAttacking();

	if(m_bDying == true)
		WEAPON->SetCurrentAnimation(ANM_DIE_DIE);
	m_sndSwitchWeapon->Play();
}

// Cycle through the masks
void CPlayer::CycleMask(void)
{
	while(true)
	{
		m_uiCurrentMask++;

		if(m_uiCurrentMask >= MASK_MAX)
			m_uiCurrentMask = MASK_NONE;

		if(TestBit(m_byteMasks, m_uiCurrentMask))
			break;
	}

	m_sndSwitchAmulet->Play();
}

// Set the bit for a weapon on
void CPlayer::AcquireWeapon(unsigned int uiWeaponType)
{
	TurnBitOn(m_byteWeapons, uiWeaponType);
}

// Set bit of a mask on
void CPlayer::AcquireAmulet(unsigned int uiMaskType)
{
	TurnBitOn(m_byteMasks, uiMaskType);
}

// Set bool for heart piece on or increase health
void CPlayer::AcquireHeartPiece(void)
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

		if(pEnemy->m_uiEnemyBehavior != 0)
		{
			if(pEnemy->m_uiMiniState > 1 )
			{
				if(IntersectRect(&temp2,&WeaponCollisionRect.GetWindowsRECT(),&pObject->GetCollisionRect().GetWindowsRECT()) != 0)
				{
					pEnemy->SufferDamage(GetAttackDamage()*m_nDamageIncrease);
				}
			}
		}
		else
		{
			if(IntersectRect(&temp2,&WeaponCollisionRect.GetWindowsRECT(),&pObject->GetCollisionRect().GetWindowsRECT()) != 0)
			{
				pEnemy->SufferDamage(GetAttackDamage()*m_nDamageIncrease);
			}
		}
	}

	if(WEAPON->GetAttacking() == true && pObject->GetType() == TYPE_CHAR_FINALBOSS)
	{
		CFinalBoss* pFinalBoss = (CFinalBoss*)pObject;
		RectD WeaponCollisionRect = WEAPON->GetCollisionRect();
		WeaponCollisionRect.OffsetRect(GetPosX(),GetPosY());
		RECT temp2;

		if(pFinalBoss->m_uiEnemyBehavior != 0)
		{
			if(pFinalBoss->m_uiMiniState > 1 )
			{
				if(IntersectRect(&temp2,&WeaponCollisionRect.GetWindowsRECT(),&pObject->GetCollisionRect().GetWindowsRECT()) != 0)
				{
					pFinalBoss->SufferDamage(GetAttackDamage()*m_nDamageIncrease);
				}
			}
		}
		else
		{
			if(IntersectRect(&temp2,&WeaponCollisionRect.GetWindowsRECT(),&pObject->GetCollisionRect().GetWindowsRECT()) != 0)
			{
				pFinalBoss->SufferDamage(GetAttackDamage()*m_nDamageIncrease);
			}
		}
	}
	return true;
}

bool CPlayer::CheckWorldCollision(void)
{
	if(WEAPON->GetType() != TYPE_WEAPON_CROSSBOW)
	{
		if(WEAPON->GetAttacking() == true)
		{
			RectD WeaponCollisionRect = WEAPON->GetCollisionRect();
			WeaponCollisionRect.OffsetRect(GetPosX(),GetPosY());
			unsigned int WeaponType = WEAPON->GetType();

			return WORLD->CheckCollisions(nullptr, &WeaponCollisionRect, WeaponType);
		}
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
	StopAttacking();

	if( m_fOuchTimer == 0.0f)
	{
		WEAPON->GetAnimationPlayer(WEAPON->GetCurrentAnimation())->Reset();
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
			m_uiNumPotions--;
			m_sndPotion->Play();
		}
	}
}


// Return Point used for talking with NPCs and opening chests
PointD CPlayer::GetInteractivePoint(void)
{
	switch(WEAPON->GetCurrentAnimation())
	{
	case ANM_WALK_UP:
	case ANM_IDLE_UP:
	case ANM_ATK_UP:
		return PointD(GetPosX(), GetPosY() - 40);
		break;
	case ANM_WALK_DOWN:
	case ANM_IDLE_DOWN:
	case ANM_ATK_DOWN:
		return PointD(GetPosX(), GetPosY() + 40);
		break;
	case ANM_WALK_LEFT:
	case ANM_IDLE_LEFT:
	case ANM_ATK_LEFT:
		return PointD(GetPosX() - 40, GetPosY());
		break;
	case ANM_WALK_RIGHT:
	case ANM_IDLE_RIGHT:
	case ANM_ATK_RIGHT:
		return PointD(GetPosX() + 40, GetPosY());
		break;
	default:
		return PointD(GetPosX(), GetPosY());
	}
}

RectD CPlayer::GetInteractiveRect(void)
{
	PointD point = GetInteractivePoint();

	RectD interactiveRect;
	interactiveRect.top = point.y - 12;
	interactiveRect.bottom = point.y + 12;
	interactiveRect.left = point.x - 12;
	interactiveRect.right = point.x + 12;

	return interactiveRect;
}