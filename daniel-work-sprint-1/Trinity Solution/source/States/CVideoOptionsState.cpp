////////////////////////////////////////////////////////////////////////
//    File Name				:	"CVideoOptionsState.cpp"
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/13/12 - 6:52 PM
//    Purpose				:	Contains the CVideoOptionsState
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "../StdAfx.h"
#include "CVideoOptionsState.h"
#include "COptionsState.h"

CVideoOptionsState* CVideoOptionsState::m_pInstance = NULL;

CVideoOptionsState::CVideoOptionsState()
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

CVideoOptionsState::~CVideoOptionsState()
{
}

CVideoOptionsState* CVideoOptionsState::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CVideoOptionsState;
	}
	return m_pInstance;
}

void CVideoOptionsState::DeleteInstance()
{
	if(m_pInstance != NULL)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

void CVideoOptionsState::Enter()
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
void CVideoOptionsState::Exit()
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

bool CVideoOptionsState::Input()
{
	if(INPUT->KeyPressed(DIK_RETURN))
	{
		switch(m_uiCurSelected)
		{
		case VDEO_FULLSCREEN:
			{
				//toggle fullscreen
				break;
			}
		case VDEO_SHOWHUD:
			{
				//toggleHud
				break;
			}
		case VDEO_MINIMAP:
			{
				//setmap
				break;
			}
		case VDEO_BACK:
			{
				GAME->ChangeState(COptionsState::GetInstance());
				break;
			}
		}
	}
	else if(INPUT->KeyPressed(DIK_DOWN))
	{
		++m_uiCurSelected;
		if(m_uiCurSelected == VDEO_MAX)
		{
			m_uiCurSelected = VDEO_FULLSCREEN;
		}
	}
	else if(INPUT->KeyPressed(DIK_UP))
	{
		--m_uiCurSelected;
		if(m_uiCurSelected > VDEO_MAX)	//	Because it's unsigned, check this way
		{
			m_uiCurSelected = VDEO_MAX - 1;
		}
	}
	return true;
}

void CVideoOptionsState::Update(float fElapsedTime)
{
}

void CVideoOptionsState::Render()
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
	for(unsigned int i = 0; i < VDEO_MAX; ++i)
	{
		TEX_MNG->Draw(m_imgCursor, 210, 150);
	}

	//	Draw a cursor at intervals of the text
	TEX_MNG->Draw(m_imgCursor, 200-32, 150-32 + m_uiCurSelected*32);
}