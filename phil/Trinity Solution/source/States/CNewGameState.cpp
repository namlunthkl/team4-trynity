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
	m_fLoadTimer = 0.0f;

	//	Imperfect..
	m_uiCurSelected = 0;
}

void CNewGameState::Exit()
{
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
				GAME->ChangeState(CGameplayState::GetInstance());
				break;
			}
		case NEWG_SLOT2:
			{
				GAME->ChangeState(CGameplayState::GetInstance());
				break;
			}
		case NEWG_SLOT3:
			{
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
	//	Draw the base menu's stuff .. NOT SURE
	CBaseMenu::Render();

	//	Draw this menu's stuff
	pFont->Write("New Slot1", 32, 12, D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("New Slot2", 32, 13, D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("New Slot3", 32, 14, D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Back", 32, 15, D3DCOLOR_XRGB(255, 255, 255));
}