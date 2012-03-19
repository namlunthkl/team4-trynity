#include "StdAfx.h"

#include "CItemChest.h"
#include "../Input Manager/CInputManager.h"
#include "CPlayer.h"
#include "../States/CGameplayState.h"

// Constructor
CItemChest::CItemChest(unsigned int uiType, double dPositionX, double dPositionY)
	: CBaseObject(dPositionX, dPositionY, 0, -1, 30, 30, true)
{
	m_uiType = uiType;
	m_uiStatus = CHEST_STATUS_CLOSED;
	m_nAnimationIndex = 0;

	SetImageID(TEX_MNG->LoadTexture("resource/Other/ItemChests.png"));
	m_nOpenSound = AUDIO->SFXLoadSound("resource/sound/Chest.wav");
	m_nGetItemSound = AUDIO->SFXLoadSound("resource/sound/GetItem.wav");

	switch(m_uiType)
	{
	case CHEST_POTION:
		m_nChestGraphic = 0;
		break;
	case CHEST_GEM:
		m_nChestGraphic = 1;
		break;
	case CHEST_HEARTPIECE:
		m_nChestGraphic = 2;
		break;
	default:
		m_nChestGraphic = 3;
	}
}

// Destructor
CItemChest::~CItemChest()
{

}

// Common routines
void CItemChest::Update(float fElapsedTime)
{
	if(m_uiStatus == CHEST_STATUS_OPENING)
	{
		m_nAnimationIndex += 2;
		if(m_nAnimationIndex == 30)
			m_uiStatus = CHEST_STATUS_JUST_OPENED;
	}

	if(m_uiStatus == CHEST_STATUS_JUST_OPENED)
	{
		string szMessage;

		switch(m_uiType)
		{
		case CHEST_POTION:
			CPlayer::GetInstance()->AcquirePotion();
			szMessage = "You got a health potion. Press Tab to use it if you loose hearts.";
			break;
		case CHEST_GEM:
			CPlayer::GetInstance()->AcquireGem();
			szMessage = "You got a bright gem. It looks useless, but maybe you'll need it one day.";
			break;
		case CHEST_HEARTPIECE:
			CPlayer::GetInstance()->AcquireHeartPiece();
			szMessage = "You got a piece of heart. Collect two to increase your heart capacity by one.";
			break;
		case CHEST_AMULET_SPEED:
			CPlayer::GetInstance()->AcquireAmulet(CPlayer::MASK_SPEED);
			szMessage = "You found the sacred amulet of Speed. When using this, you'll run much faster.";
			break;
		case CHEST_AMULET_STRENGTH:
			CPlayer::GetInstance()->AcquireAmulet(CPlayer::MASK_STRENGHT);
			szMessage = "You found the sacred amulet of Strength. When using this, you'll deal more damage to enemies.";
			break;
		case CHEST_AMULET_ENDURANCE:
			CPlayer::GetInstance()->AcquireAmulet(CPlayer::MASK_ENDURANCE);
			szMessage = "You found the sacred amulet of Endurance. When using this, you'll have a chance of taking less damage from enemies.";
			break;
		case CHEST_AMULET_LIGHT:
			CPlayer::GetInstance()->AcquireAmulet(CPlayer::MASK_LIGHT);
			szMessage = "You found the sacred amulet of Light. When using this, you'll be able to see everything around you, even in the darkest nights.";
			break;
		}

		AUDIO->SFXPlaySound(m_nGetItemSound);

		CGameplayState::GetInstance()->SetMessageBox(true, "Chest",
			CGameplayState::GetInstance()->BreakDownStrings(szMessage, 48, 51));

		m_uiStatus = CHEST_STATUS_MESSAGE;
	}
}

void CItemChest::Input(void)
{
	if(CInputManager::GetInstance()->GetPressedA())
	{
		if(m_uiStatus == CHEST_STATUS_CLOSED)
		{
			RECT rectIntersection;
			if(IntersectRect(&rectIntersection, &GetCollisionRect().GetWindowsRECT(),
				&CPlayer::GetInstance()->GetInteractiveRect().GetWindowsRECT()))
			{
				if(CPlayer::GetInstance()->Lock())
				{
					m_uiStatus = CHEST_STATUS_OPENING;
					AUDIO->SFXPlaySound(m_nOpenSound);
				}
			}
		}
		else if(m_uiStatus == CHEST_STATUS_MESSAGE)
		{
			CPlayer::GetInstance()->Unlock();
			m_uiStatus = CHEST_STATUS_OPEN;
			CGameplayState::GetInstance()->SetMessageBox(false);
		}
	}
}

RectD CItemChest::GetCollisionRect(void)
{
	RectD collisionRect;
	collisionRect.left = GetPosX() - 13;
	collisionRect.right = GetPosX() + 13;
	collisionRect.top = GetPosY() - 5;
	collisionRect.bottom = GetPosY() + 24;

	return collisionRect;
}

void CItemChest::Render(void)
{
	RECT sourceRect;

	sourceRect.left = m_nChestGraphic * 32;
	sourceRect.top = (m_nAnimationIndex/10) * 48;
	sourceRect.right = sourceRect.left + 32;
	sourceRect.bottom = sourceRect.top + 48;

	TEX_MNG->Draw(GetImageID(), GetPosX() - 16, GetPosY() - 24, 1.0f, 1.0f, &sourceRect);
}