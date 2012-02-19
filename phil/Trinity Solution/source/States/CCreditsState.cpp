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

void CCreditsState::Enter()
{
}

void CCreditsState::Exit()
{
}

bool CCreditsState::Input()
{
	return true;
}

void CCreditsState::Update(float fElapsedTime)
{
}

void CCreditsState::Render()
{
	/*pFont->Write("Ari Bodaghee", 2, 8 + (2*0), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Daniel Lima", 2, 8 + (2*1), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Bryan Schotanes", 2, 8 + (2*2), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Phil Sullivan", 2, 8 + (2*3), D3DCOLOR_XRGB(255, 255, 255));*/
}

CCreditsState* CCreditsState::GetInstance()
{
	static CCreditsState instance;
	return &instance;
}