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
}

CCreditsState::~CCreditsState()
{
}

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
}

void CCreditsState::Exit()
{
	//	Delete font
	if(pFont)
	{
		delete pFont;
		pFont = NULL;
	}
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
}

void CCreditsState::Render()
{
	pFont->Write("PROGRAMMING BY", 24, 1 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Ari Bodaghee", 32, 2 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Daniel Lima", 32, 3 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Bryan Schotanes", 32, 4 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Phil Sullivan", 32, 5 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("MUSIC BY", 24, 7 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Kim Stennabb Caesar", 32, 8 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("LED BY", 24, 10 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("John OLeske", 32, 11 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Rob Martinez", 32, 12 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Shawn Paris", 32, 13 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Sean Hathaway", 32, 14 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Press Enter", 32, 16 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
}