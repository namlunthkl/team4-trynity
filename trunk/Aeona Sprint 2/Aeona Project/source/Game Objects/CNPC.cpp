////////////////////////////////////////////////////////////////////////
//    File Name				:	"CNPC.cpp"
//
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 4:13 AM
//    Purpose				:	NPC character class definitions
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CNPC.h"
#include "CPlayer.h"
#include "../Input Manager/CInputManager.h"

// Constructor
CNPC::CNPC(bool bActiveTalk, double dRange, int sndNPC, CBitmapFont* pFont,
	double dPositionX, double dPositionY, unsigned int uiSpeed,
	int nImageID, unsigned int uiWidth, unsigned int uiHeight, bool bActive,
	unsigned int uiMaxHealth, unsigned int uiAttackDamage)
	: CBaseCharacter(dPositionX, dPositionY, uiSpeed, nImageID, uiWidth, uiHeight, bActive, uiMaxHealth, uiAttackDamage)
{
	m_bActiveTalk = bActiveTalk;
	m_sndNPC = sndNPC;
	m_dRange = dRange;
	m_bTalk = false;
	m_szText = "";
	m_pFont = pFont;
	m_uiTextIndex = 0;
	m_dwTimeStamp = 0;
	m_imgMsgBox = TEX_MNG->LoadTexture("resource/MessageBox.png");
}

// Load NPC's speech
void CNPC::LoadText(char* szFilename)
{
	// For now let's just set the text to this
	m_szText = szFilename;

	// TODO: Read that XML file in the dialogue
	// data structure
}

// Common routines
void CNPC::Update(float fElapsedTime)
{
	CBaseCharacter::Update(fElapsedTime);

	if(m_bTalk)
	{
		if(m_uiTextIndex < m_szText.size())
		{
			if(timeGetTime() - m_dwTimeStamp > 50)
			{
				m_uiTextIndex++;
				m_dwTimeStamp = timeGetTime();
			}
		}
	}

	// Get the distance between the player and the NPC
	double dDistance;
	dDistance = GetPosition().GetDistanceUntil(CPlayer::GetInstance()->GetPosition());

	if(dDistance < m_dRange)
	{
		if(m_bActiveTalk)
			m_bTalk = true;
	}
	else
	{
		m_bTalk = false;
		m_uiTextIndex = 0;
	}
}

void CNPC::Input(void)
{
	CBaseCharacter::Input();

	if(!m_bActiveTalk)
	{
		if(CInputManager::GetInstance()->GetPressedA())
		{
			// Get the distance between the player and the NPC
			double dDistance;
			dDistance = GetPosition().GetDistanceUntil(CPlayer::GetInstance()->GetPosition());

			if(dDistance < m_dRange)
				m_bTalk = !m_bTalk;
			else
				m_bTalk = false;

			m_uiTextIndex = 0;
		}
	}
}

void CNPC::Render(void)
{
	CBaseCharacter::Render();

	int nDrawLocationX;
	if(GAME->GetMapLocation() == 2)
		nDrawLocationX = 5;
	else
		nDrawLocationX = 105;


	if(m_bTalk)
	{
		char* textToDraw = new char[m_uiTextIndex + 1];

		for(int i=0; i < m_uiTextIndex; ++i)
			textToDraw[i] = m_szText[i];
		textToDraw[m_uiTextIndex] = '\0';

		TEX_MNG->Draw(m_imgMsgBox, nDrawLocationX, 500);
		
		D3D->GetSprite()->Flush();

		if(m_pFont)
		{
			m_pFont->Write(textToDraw, nDrawLocationX + 15, 16, D3DCOLOR_XRGB(255, 255, 255));
		}
		else
		{
			D3D->DrawTextA(textToDraw, nDrawLocationX + 15, 520, 255, 255, 255);
		}
	}
}