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
	m_fLoadTimer = 0.0f;

	//	Imperfect..
	m_uiCurSelected = 0;
}

void CLoadGameState::Exit()
{
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
	return true;
}

void CLoadGameState::Update(float fElapsedTime)
{
	CBaseMenu::Update(fElapsedTime);
}

void CLoadGameState::Render()
{
	//	Draw the base menu's stuff .. NOT SURE
	CBaseMenu::Render();

	//	Draw this menu's stuff
	pFont->Write("Load Slot1", 32, 12, D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Load Slot2", 32, 13, D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Load Slot3", 32, 14, D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Back", 32, 15, D3DCOLOR_XRGB(255, 255, 255));
}