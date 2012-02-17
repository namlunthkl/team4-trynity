////////////////////////////////////////////////////////////////////////
//    File Name				:	"CMainMenuState.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the CMainMenuState
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "../StdAfx.h"
#include "CMainMenuState.h"
//#include "CNewGameState.h"
//#include "CLoadGameState.h"
#include "COptionsState.h"
#include "CCreditsState.h"

CMainMenuState* CMainMenuState::m_pInstance = NULL;

CMainMenuState::CMainMenuState()
{
	//	Assets
	m_imgBackground = -1;
	m_imgScroll = -1;
	m_imgCursor = -1;
	m_sndMoveCursor = -1;
	m_sndConfirm = -1;

	//	Members
	m_uiCurSelected = 0;
	m_fLoadTimer = 0.0f;
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
	//	Load Assets
	m_imgBackground = TEX_MNG->LoadTexture("resource/TempAsset1.png");
	m_imgScroll = TEX_MNG->LoadTexture("resource/TempAsset2.png");
	m_imgCursor = TEX_MNG->LoadTexture("resource/TempAsset2.png");
	m_sndMoveCursor = -1;
	m_sndConfirm = -1;

	//	Members
	m_uiCurSelected = 0;
	m_fLoadTimer = 0.0f;

	//	Play Song
	//
}
void CMainMenuState::Exit()
{
	//	Stop Song
	//

	//	Unload Assets
	TEX_MNG->UnloadTexture(m_imgBackground);
	TEX_MNG->UnloadTexture(m_imgScroll);
	TEX_MNG->UnloadTexture(m_imgCursor);
	//unloadsonghere
	m_imgBackground = -1;
	m_imgScroll = -1;
	m_imgCursor = -1;
	m_sndMoveCursor = -1;
	m_sndConfirm = -1;
}

bool CMainMenuState::Input()
{	
	if(INPUT->KeyPressed(DIK_RETURN))
	{
		switch(m_uiCurSelected)
		{
		case MAIN_NEW:
			{
				//GAME->ChangeState(CNewGameState::GetInstance());
				break;
			}
		case MAIN_LOAD:
			{
				//GAME->ChangeState(CLoadGameState::GetInstance());
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
	else if(INPUT->KeyPressed(DIK_DOWN))
	{
		++m_uiCurSelected;
		if(m_uiCurSelected == MAIN_MAX)
		{
			m_uiCurSelected = MAIN_NEW;
		}
	}
	else if(INPUT->KeyPressed(DIK_UP))
	{
		--m_uiCurSelected;
		if(m_uiCurSelected > MAIN_MAX)	//	Because it's unsigned, check this way
		{
			m_uiCurSelected = MAIN_MAX - 1;
		}
	}
	return true;
}

void CMainMenuState::Update(float fElapsedTime)
{
}

void CMainMenuState::Render()
{
	TEX_MNG->Draw(m_imgBackground, 0, 0);

	RECT rectScroll;
	rectScroll.left = 0;
	rectScroll.top = 0;
	rectScroll.right = 400;
	rectScroll.bottom = 300;

	TEX_MNG->Draw(m_imgScroll, 200, 150);

	RECT rectCursor;
	rectCursor.left = 0;
	rectCursor.top = 0;
	rectCursor.right = 64;
	rectCursor.bottom = 64;

	//	Draw the text in even intervals
	for(unsigned int i = 0; i < MAIN_MAX; ++i)
	{
		TEX_MNG->Draw(m_imgCursor, 210, 150);
	}

	//	Draw a cursor at intervals of the text
	TEX_MNG->Draw(m_imgCursor, 200-32, 150-32 + m_uiCurSelected*32);
}