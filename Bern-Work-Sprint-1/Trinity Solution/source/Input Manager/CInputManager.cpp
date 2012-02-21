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
#include <XInput.h>
CInputManager::CInputManager(int nPlayerNumber)
{
	m_nControllerNum = nPlayerNumber-1;
}
XINPUT_STATE CInputManager::GetState()
{
	ZeroMemory(&m_ControllerState,sizeof(XINPUT_STATE));
	XInputGetState(m_nControllerNum,&m_ControllerState);
	return m_ControllerState;

}
bool CInputManager::IsConnected()
{
	ZeroMemory(&m_ControllerState,sizeof(XINPUT_STATE));
	DWORD Result = XInputGetState(m_nControllerNum,&m_ControllerState);

	if(Result == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void CInputManager::Vibrate(int nLeftVal, int nRightVal)
{
	XINPUT_VIBRATION Vibration;
	ZeroMemory(&Vibration,sizeof(XINPUT_VIBRATION));

	Vibration.wLeftMotorSpeed = nLeftVal;
	Vibration.wRightMotorSpeed = nRightVal;

	XInputSetState(m_nControllerNum,&Vibration);
}
CInputManager* CInputManager::GetInstance()
{
	static CInputManager instance;
	return &instance;
}