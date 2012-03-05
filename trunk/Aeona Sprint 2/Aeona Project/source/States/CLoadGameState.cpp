////////////////////////////////////////////////////////////////////////
//    File Name				:	"CLoadGameState.cpp"
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/16/12 - 5:15 PM
//    Purpose				:	Three-slot menu for Load Game File
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "../StdAfx.h"
#include "CLoadGameState.h"
#include "CGameplayState.h"
#include "CMainMenuState.h"
#include "../Input Manager/CInputManager.h"
CLoadGameState* CLoadGameState::m_pInstance = NULL;

CLoadGameState::CLoadGameState()
{
}

CLoadGameState::~CLoadGameState()
{
}

CLoadGameState* CLoadGameState::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CLoadGameState;
	}
	return m_pInstance;
}

void CLoadGameState::DeleteInstance()
{
	if(m_pInstance != NULL)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

void CLoadGameState::Enter()
{
	CBaseMenu::Enter();

	//	Members
	m_uiMenuCount = LODG_MAX;

	//	Check the existing save states, 'n crap
	GAME->m_cLoadedOrNot = GAME->ReadSaveSlots();

	//	Imperfect..
	m_uiCurSelected = 0;
}

void CLoadGameState::Exit()
{
	CBaseMenu::Exit();
}

bool CLoadGameState::Input()
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
		case LODG_SLOT1:
			{
				GAME->ChangeState(CGameplayState::GetInstance());
				break;
			}
		case LODG_SLOT2:
			{
				GAME->ChangeState(CGameplayState::GetInstance());
				break;
			}
		case LODG_SLOT3:
			{
				GAME->ChangeState(CGameplayState::GetInstance());
				break;
			}
		case LODG_BACK:
			{
				GAME->ChangeState(CMainMenuState::GetInstance());
				break;
			}
		}
	}
	//	Delete a slot
	else if(CInputManager::GetInstance()->DeleteGame())
	{
		switch(m_uiCurSelected)
		{
		case LODG_SLOT1:
			{
				GAME->DeleteSlot1();
				break;
			}
		case LODG_SLOT2:
			{
				GAME->DeleteSlot2();
				break;
			}
		case LODG_SLOT3:
			{
				GAME->DeleteSlot3();
				break;
			}
		}
	}
	return true;
}

void CLoadGameState::Update(float fElapsedTime)
{
	CBaseMenu::Update(fElapsedTime);
}

void CLoadGameState::Render()
{
	//	Draw the base menu's stuff
	CBaseMenu::Render();

	//	Draw this menu's stuff
	pFont->Write("Load Slot 1", 32, 12 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	if(TestBit(GAME->m_cLoadedOrNot, 0))
		pFont->Write("CONTAINS SAVED DATA", 250, 12 * pFont->GetCharHeight(), D3DCOLOR_XRGB(128, 192, 255));
	else
		pFont->Write("Empty slot", 250, 12 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Load Slot 2", 32, 13 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	if(TestBit(GAME->m_cLoadedOrNot, 1))
		pFont->Write("CONTAINS SAVED DATA", 250, 13 * pFont->GetCharHeight(), D3DCOLOR_XRGB(128, 192, 255));
	else
		pFont->Write("Empty slot", 250, 13 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Load Slot 3", 32, 14 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	if(TestBit(GAME->m_cLoadedOrNot, 2))
		pFont->Write("CONTAINS SAVED DATA", 250, 14 * pFont->GetCharHeight(), D3DCOLOR_XRGB(128, 192, 255));
	else
		pFont->Write("Empty slot", 250, 14 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Back", 32, 15 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("SHIFT DELETE to delete a slot", 32, 17 * pFont->GetCharHeight(), D3DCOLOR_XRGB(80, 0, 0));
}