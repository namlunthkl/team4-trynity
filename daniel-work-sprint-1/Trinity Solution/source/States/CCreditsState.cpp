////////////////////////////////////////////////////////////////////////
//    File Name				:	"CCreditsState.cpp"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the CreditsState
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CCreditsState.h"
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

}
CCreditsState* CCreditsState::GetInstance()
{
	static CCreditsState instance;
	return &instance;
}