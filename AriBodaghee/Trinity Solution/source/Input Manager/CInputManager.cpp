////////////////////////////////////////////////////////////////////////
//    File Name				:	"CInputManager.cpp"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the inputManager for the Controller/
//								Keyboard
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CInputManager.h"
CInputManager::CInputManager(int nPlayerNumber)
{

}
XINPUT_STATE CInputManager::GetState()
{
	XINPUT_STATE returnable;

	return returnable;
}
bool CInputManager::IsConnected()
{
	return true;
}
void CInputManager::Vibrate(int nLeftVal, int nRightVal)
{

}
CInputManager* CInputManager::GetInstance()
{
	static CInputManager instance;
	return &instance;
}