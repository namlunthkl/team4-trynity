////////////////////////////////////////////////////////////////////////
//    File Name				:	"CCreditsState.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the CreditsState
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "../StdAfx.h"
#include "CCreditsState.h"
#include "CMainMenuState.h"

CCreditsState* CCreditsState::m_pInstance = NULL;
CCreditsState::CCreditsState()
{
	m_fWhatever = 0.0f;
}
CCreditsState::~CCreditsState(){}
CCreditsState* CCreditsState::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CCreditsState;
	}
	return m_pInstance;
}
void CCreditsState::DeleteInstance()
{
	if(m_pInstance != NULL)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}
void CCreditsState::Enter()
{
	pFont = new CBitmapFont;
	m_fWhatever = 0.0f;
}
bool CCreditsState::Input()
{
	if(INPUT->KeyPressed(DIK_RETURN))
	{
		GAME->ChangeState(CMainMenuState::GetInstance());
	}
	return true;
}
void CCreditsState::Update(float fElapsedTime)
{
	m_fWhatever -= (int)(fElapsedTime * 60);
	if(m_fWhatever <= -1200.0f)
	{
		GAME->ChangeState(CMainMenuState::GetInstance());
	}
}
void CCreditsState::Render()
{
	pFont->Write("PROGRAMMING BY",		10, (int)(480 + m_fWhatever), D3DCOLOR_XRGB(200, 100, 255));
	pFont->Write("Ari Bodaghee",		10, (int)(550 + m_fWhatever), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Daniel Lima",			10, (int)(580 + m_fWhatever), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Bryan Schotanes",		10, (int)(610 + m_fWhatever), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Phil Sullivan",		10, (int)(640 + m_fWhatever), D3DCOLOR_XRGB(255, 255, 255));
											
	pFont->Write("MUSIC BY",			10, (int)(740 + m_fWhatever), D3DCOLOR_XRGB(200, 100, 255));
	pFont->Write("Kim Stennabb Caesar",	10, (int)(810 + m_fWhatever), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Heather Pluckard",	10, (int)(840 + m_fWhatever), D3DCOLOR_XRGB(255, 255, 255));
											
	pFont->Write("SPECIAL THANKS",		10, (int)(940 + m_fWhatever), D3DCOLOR_XRGB(200, 100, 255));
	pFont->Write("John OLeske",			10, (int)(970 + m_fWhatever), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Rob Martinez",		10, (int)(1000 + m_fWhatever), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Shawn Paris",			10, (int)(1030 + m_fWhatever), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Sean Hathaway",		10, (int)(1060 + m_fWhatever), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Lari Norri",			10, (int)(1090 + m_fWhatever), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("David Brown",			10, (int)(1120 + m_fWhatever), D3DCOLOR_XRGB(255, 255, 255));

	pFont->Write("Press Enter",			600, 550, D3DCOLOR_XRGB(255, 0, 0));
}
void CCreditsState::Exit()
{
	//	Delete font
	if(pFont)
	{
		delete pFont;
		pFont = NULL;
	}
	m_fWhatever = 0.0f;
}