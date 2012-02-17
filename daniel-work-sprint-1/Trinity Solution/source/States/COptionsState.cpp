////////////////////////////////////////////////////////////////////////
//    File Name				:	"COptionsState.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the COptionsState
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "../StdAfx.h"
#include "CMainMenuState.h"
#include "COptionsState.h"
#include "CVideoOptionsState.h"
#include "CAudioOptionsState.h"

COptionsState* COptionsState::m_pInstance = NULL;

COptionsState::COptionsState()
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

COptionsState::~COptionsState()
{
}

COptionsState* COptionsState::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new COptionsState;
	}
	return m_pInstance;
}

void COptionsState::DeleteInstance()
{
	if(m_pInstance != NULL)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

void COptionsState::Enter()
{
	//	Load Assets
	m_imgBackground = TEX_MNG->LoadTexture("TempAsset1.png");
	m_imgScroll = TEX_MNG->LoadTexture("TempAsset2.png");
	m_imgCursor = TEX_MNG->LoadTexture("TempAsset2.png");
	m_sndMoveCursor = -1;
	m_sndConfirm = -1;

	//	Members
	m_uiCurSelected = 0;
	m_fLoadTimer = 0.0f;

	//	Play Song
	//
}
void COptionsState::Exit()
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

bool COptionsState::Input()
{
	if(INPUT->KeyPressed(DIK_RETURN))
	{
		switch(m_uiCurSelected)
		{
		case OPTN_VIDEO:
			{
				GAME->ChangeState(CVideoOptionsState::GetInstance());
				break;
			}
		case OPTN_AUDIO:
			{
				GAME->ChangeState(CAudioOptionsState::GetInstance());
				break;
			}
		case OPTN_BACK:
			{
				GAME->ChangeState(CMainMenuState::GetInstance());
				break;
			}
		}
	}
	else if(INPUT->KeyPressed(DIK_DOWN))
	{
		++m_uiCurSelected;
		if(m_uiCurSelected == OPTN_MAX)
		{
			m_uiCurSelected = OPTN_VIDEO;
		}
	}
	else if(INPUT->KeyPressed(DIK_UP))
	{
		--m_uiCurSelected;
		if(m_uiCurSelected > OPTN_MAX)	//	Because it's unsigned, check this way
		{
			m_uiCurSelected = OPTN_MAX - 1;
		}
	}
	return true;
}

void COptionsState::Update(float fElapsedTime)
{
}

void COptionsState::Render()
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
	for(unsigned int i = 0; i < OPTN_MAX; ++i)
	{
		TEX_MNG->Draw(m_imgCursor, 210, 150);
	}

	//	Draw a cursor at intervals of the text
	TEX_MNG->Draw(m_imgCursor, 200-32, 150-32 + m_uiCurSelected*32);
}