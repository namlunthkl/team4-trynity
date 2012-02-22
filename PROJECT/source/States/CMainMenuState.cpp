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
	CBaseMenu::Enter();

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
				CNewGameState::GetInstance()->SetTitleIndex(m_pnTitleIndex);
				CNewGameState::GetInstance()->SetTitleScrollDir(m_pbTitleScrollDir);
				GAME->ChangeState(CNewGameState::GetInstance());
				break;
			}
		case MAIN_LOAD:
			{
				CLoadGameState::GetInstance()->SetTitleIndex(m_pnTitleIndex);
				CLoadGameState::GetInstance()->SetTitleScrollDir(m_pbTitleScrollDir);
				GAME->ChangeState(CLoadGameState::GetInstance());
				break;
			}
		case MAIN_OPTIONS:
			{
				COptionsState::GetInstance()->SetTitleIndex(m_pnTitleIndex);
				COptionsState::GetInstance()->SetTitleScrollDir(m_pbTitleScrollDir);
				GAME->ChangeState(COptionsState::GetInstance());
				break;
			}
		case MAIN_CREDITS:
			{
				CBaseMenu::Exit();	//	To make sure the pFont gets deleted.
				GAME->ChangeState(CCreditsState::GetInstance());
				break;
			}
		case MAIN_EXIT:
			{

				GAME->ChangeState(NULL);
				CBaseMenu::Exit();	//	To make sure the pFont gets deleted.
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
	//	Draw the base menu's stuff
	CBaseMenu::Render();
	

	//	DELETELATER JUST TO SHOW CHARS
	//pFont->Write("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 32, 9, D3DCOLOR_XRGB(255, 255, 255));
	//pFont->Write("abcdefghijklmnopqrstuvwxyz", 32, 10, D3DCOLOR_XRGB(255, 255, 255));

	//	Draw this menu's stuff
	pFont->Write("New Game", 32, 12, D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Load Game", 32, 13, D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Settings", 32, 14, D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Credits", 32, 15, D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Exit", 32, 16, D3DCOLOR_XRGB(255, 255, 255));
}