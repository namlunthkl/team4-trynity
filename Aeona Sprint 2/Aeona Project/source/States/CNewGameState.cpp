////////////////////////////////////////////////////////////////////////
//    File Name				:	"CNewGameState.cpp"
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/16/12 - 5:15 PM
//    Purpose				:	Three-slot menu for New Game File
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "../StdAfx.h"
#include "CNewGameState.h"
#include "CGameplayState.h"
#include "CMainMenuState.h"

CNewGameState* CNewGameState::m_pInstance = NULL;

CNewGameState::CNewGameState()
{
}

CNewGameState::~CNewGameState()
{
}

CNewGameState* CNewGameState::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CNewGameState;
	}
	return m_pInstance;
}

void CNewGameState::DeleteInstance()
{
	if(m_pInstance != NULL)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

void CNewGameState::Enter()
{
	CBaseMenu::Enter();

	//	Members
	m_uiMenuCount = NEWG_MAX;

	//	Check the existing save states, 'n crap
	GAME->m_cLoadedOrNot = GAME->ReadSaveSlots();

	//	Imperfect..
	m_uiCurSelected = 0;
}

void CNewGameState::Exit()
{
	CBaseMenu::Exit();
}

bool CNewGameState::Input()
{
	//	NOT SURE
	CBaseMenu::Input();
	//	ABOVE?

	if(bMenuConfirm == true)
	{
		//	Set it back to false
		bMenuConfirm = false;
		//	Which choice is selected?
		switch(m_uiCurSelected)
		{
		case NEWG_SLOT1:
			{
				AUDIO->MusicStopSong(GetBGMusic());
				GAME->m_uiYoManWhichSlotAreWePlayingInBro = 1;
				GAME->m_uiWhichSlotAreWeLoadingDawgQuestionMark = 0;
				GAME->ChangeState(CGameplayState::GetInstance());
				break;
			}
		case NEWG_SLOT2:
			{
				AUDIO->MusicStopSong(GetBGMusic());
				GAME->m_uiYoManWhichSlotAreWePlayingInBro = 2;
				GAME->m_uiWhichSlotAreWeLoadingDawgQuestionMark = 0;
				GAME->ChangeState(CGameplayState::GetInstance());
				break;
			}
		case NEWG_SLOT3:
			{
				AUDIO->MusicStopSong(GetBGMusic());
				GAME->m_uiYoManWhichSlotAreWePlayingInBro = 3;
				GAME->m_uiWhichSlotAreWeLoadingDawgQuestionMark = 0;
				GAME->ChangeState(CGameplayState::GetInstance());
				break;
			}
		case NEWG_BACK:
			{
				GAME->ChangeState(CMainMenuState::GetInstance());
				break;
			}
		}
	}
	return true;
}

void CNewGameState::Update(float fElapsedTime)
{
	CBaseMenu::Update(fElapsedTime);
}

void CNewGameState::Render()
{
	//	Draw the base menu's stuff
	CBaseMenu::Render();

	//	Draw this menu's stuff
	pFont->Write("New Slot 1", 32, 12 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	if(TestBit(GAME->m_cLoadedOrNot, 0))
		pFont->Write("CONTAINS SAVED DATA", 250, 12 * pFont->GetCharHeight(), D3DCOLOR_XRGB(128, 192, 255));
	else
		pFont->Write("Empty slot", 250, 12 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("New Slot 2", 32, 13 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	if(TestBit(GAME->m_cLoadedOrNot, 1))
		pFont->Write("CONTAINS SAVED DATA", 250, 13 * pFont->GetCharHeight(), D3DCOLOR_XRGB(128, 192, 255));
	else
		pFont->Write("Empty slot", 250, 13 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("New Slot 3", 32, 14 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	if(TestBit(GAME->m_cLoadedOrNot, 2))
		pFont->Write("CONTAINS SAVED DATA", 250, 14 * pFont->GetCharHeight(), D3DCOLOR_XRGB(128, 192, 255));
	else
		pFont->Write("Empty slot", 250, 14 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Back", 32, 15 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
}