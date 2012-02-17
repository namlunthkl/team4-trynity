////////////////////////////////////////////////////////////////////////
//    File Name				:	"CMainMenuState.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the CMainMenuState
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "../StdAfx.h"
#include "CMainMenuState.h"
#include "CNewGameState.h"
#include "CLoadGameState.h"
#include "COptionsState.h"
#include "CCreditsState.h"

CMainMenuState* CMainMenuState::m_pInstance = NULL;

CMainMenuState::CMainMenuState()// : CBaseMenu()
{
	m_uiCurSelected = 0;
	//	Call it here, not in Enter(), because I want to be able to specify a CurSelected
	//	when exiting from another menu state.
}

CMainMenuState::~CMainMenuState()
{
}

CMainMenuState* CMainMenuState::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CMainMenuState;
	}
	return m_pInstance;
}

void CMainMenuState::DeleteInstance()
{
	if(m_pInstance != NULL)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

void CMainMenuState::Enter()
{
	//	Members
	m_uiMenuCount = MAIN_MAX;

	//	Imperfect..
	m_uiCurSelected = 0;
}

void CMainMenuState::Exit()
{
}

bool CMainMenuState::Input()
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
		case MAIN_NEW:
			{
				GAME->ChangeState(CNewGameState::GetInstance());
				break;
			}
		case MAIN_LOAD:
			{
				GAME->ChangeState(CLoadGameState::GetInstance());
				break;
			}
		case MAIN_OPTIONS:
			{
				GAME->ChangeState(COptionsState::GetInstance());
				break;
			}
		case MAIN_CREDITS:
			{
				GAME->ChangeState(CCreditsState::GetInstance());
				break;
			}
		case MAIN_EXIT:
			{
				return false;
			}
		}
	}
	return true;
}

void CMainMenuState::Update(float fElapsedTime)
{
	CBaseMenu::Update(fElapsedTime);
}

void CMainMenuState::Render()
{
	//	Draw the base menu's stuff .. NOT SURE
	CBaseMenu::Render();

	//	Draw this menu's stuff
	pFont->Write("New Game", 2, 8 + (2*0), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Load Game", 2, 8 + (2*1), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Options", 2, 8 + (2*2), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Credits", 2, 8 + (2*3), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Exit", 2, 8 + (2*4), D3DCOLOR_XRGB(255, 255, 255));
}