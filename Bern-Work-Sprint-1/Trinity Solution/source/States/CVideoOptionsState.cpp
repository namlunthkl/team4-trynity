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
	//	Members
	m_uiMenuCount = VDEO_MAX;
	m_fLoadTimer = 0.0f;

	//	Imperfect..
	m_uiCurSelected = 0;
}

void CVideoOptionsState::Exit()
{
}

bool CVideoOptionsState::Input()
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
		case VDEO_FULLSCREEN:
			{
				GAME->SetIsWindowed( !GAME->GetIsWindowed() );
				break;
			}
		case VDEO_SHOWHUD:
			{
				GAME->SetShowHUD( !GAME->GetShowHUD() );
				break;
			}
		case VDEO_MINIMAP:
			{
				GAME->SetMapLocation( GAME->GetMapLocation() + 1 );
				if( GAME->GetMapLocation() == 3 )
				{
					GAME->SetMapLocation( 0 );
				}
				break;
			}
		case VDEO_BACK:
			{
				GAME->ChangeState(COptionsState::GetInstance());
				break;
			}
		}
	}
	return true;
}

void CVideoOptionsState::Update(float fElapsedTime)
{
}

void CVideoOptionsState::Render()
{
	//	Draw the base menu's stuff .. NOT SURE
	CBaseMenu::Render();

	//	Draw this menu's stuff
	pFont->Write("Full Screen", 2, 8 + (2*0), D3DCOLOR_XRGB(255, 255, 255));
	if(GAME->GetIsWindowed() == false)
	{
		pFont->Write("On", 19, 8 + (2*0), D3DCOLOR_XRGB(255, 255, 255));
	}
	else
	{
		pFont->Write("Off", 19, 8 + (2*0), D3DCOLOR_XRGB(255, 255, 255));
	}
	pFont->Write("HUD", 2, 8 + (2*1), D3DCOLOR_XRGB(255, 255, 255));
	if(GAME->GetShowHUD() == true)
	{
		pFont->Write("On", 19, 8 + (2*1), D3DCOLOR_XRGB(255, 255, 255));
	}
	else
	{
		pFont->Write("Off", 19, 8 + (2*1), D3DCOLOR_XRGB(255, 255, 255));
	}
	pFont->Write("Map Location", 2, 8 + (2*2), D3DCOLOR_XRGB(255, 255, 255));
	if(GAME->GetMapLocation() == 0)
	{
		pFont->Write("U.R.", 19, 8 + (2*2), D3DCOLOR_XRGB(255, 255, 255));
	}
	else if(GAME->GetMapLocation() == 1)
	{
		pFont->Write("B.L.", 19, 8 + (2*2), D3DCOLOR_XRGB(255, 255, 255));
	}
	else if(GAME->GetMapLocation() == 2)
	{
		pFont->Write("B.R.", 19, 8 + (2*2), D3DCOLOR_XRGB(255, 255, 255));
	}
	pFont->Write("Back", 2, 8 + (2*3), D3DCOLOR_XRGB(255, 255, 255));
}