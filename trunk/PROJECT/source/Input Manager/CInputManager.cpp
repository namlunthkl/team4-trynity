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

void CInputManager::SetController(int PlayerController) 
{
	m_PlayerController = new CXboxController(PlayerController);
	if(m_bControllerSet != true)
	{
		m_bA = false;
		m_bDown = false;
		m_bLeft = false;
		m_bRight = false;
		m_bUp = false;
		m_bRightTrigger = false;
		m_bLBumper = false;
	}
	m_bControllerSet = true;
	
	
}
bool CInputManager::GetPause(void)
{
	if(INPUT->KeyPressed(DIK_ESCAPE) || (m_bControllerSet && m_PlayerController->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START))
		return true;

	return false;
}
bool CInputManager::GetUp(void)
{
	if(INPUT->KeyDown(DIK_W) || (m_PlayerController->GetState().Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
		return true;

	return false;
}
bool CInputManager::GetLeft(void)
{
	if(INPUT->KeyDown(DIK_A) || (m_PlayerController->GetState().Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
		return true;

	return false;
}
bool CInputManager::GetRight(void)
{
	if(INPUT->KeyDown(DIK_D) || (m_PlayerController->GetState().Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
		return true;

	return false;
}
bool CInputManager::GetDown(void)
{
	if(INPUT->KeyDown(DIK_S) || (m_PlayerController->GetState().Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
		return true;

	return false;
}
bool CInputManager::GetPressedUp(void)
{
	if(INPUT->KeyPressed(DIK_W) || (m_PlayerController->GetState().Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_bUp == false))
	{
		m_bUp = true;
		return true;
	}
	else if(m_PlayerController->GetState().Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_bUp == true)
		m_bUp = false;

	return false;
}
bool CInputManager::GetPressedLeft(void)
{
	if(INPUT->KeyPressed(DIK_A) || (m_PlayerController->GetState().Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_bLeft == false))
	{
		m_bLeft = true;
		return true;
	}
	else if(m_bControllerSet && m_PlayerController->GetState().Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_bLeft== true)
		m_bLeft = false;

	return false;
}
bool CInputManager::GetPressedRight(void)
{
	if(INPUT->KeyPressed(DIK_D) || (m_PlayerController->GetState().Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_bRight == false))
	{
		m_bRight = true;
		return true;
	}
	else if(m_PlayerController->GetState().Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_bRight == true)
		m_bRight = false;

	return false;
}
bool CInputManager::GetPressedDown(void)
{
	if(INPUT->KeyPressed(DIK_S) || (m_PlayerController->GetState().Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_bDown == false))
	{
		m_bDown = true;
		return true;
	}
	else if(m_PlayerController->GetState().Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_bDown == true)
		m_bDown = false;

	return false;
}
bool CInputManager::GetSwapWeapon(void)
{
	if(INPUT->KeyPressed(DIK_Q) || (m_PlayerController->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER))
		return true;

	return false;
}
bool CInputManager::GetSwapMask(void)
{
	if(INPUT->KeyPressed(DIK_E) || (m_PlayerController->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER))
		return true;

	return false;
}
bool CInputManager::GetInventory(void)
{
	if(m_bControllerSet && INPUT->KeyPressed(DIK_TAB) || (m_PlayerController->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y))
		return true;

	return false;
}
bool CInputManager::GetAttack(void)
{
	if(m_bControllerSet && INPUT->KeyPressed(DIK_RETURN) || (m_PlayerController->GetState().Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD))
		return true;

	return false;
}
bool CInputManager::GetPressedA(void)
{
	if(INPUT->KeyPressed(DIK_E) || m_PlayerController->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A && m_bA == false)
	{
		m_bA = true;
		return true;
	}
	else if(!(m_PlayerController->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A) && m_bA == true)
		m_bA = false;

	return false;
}
bool CInputManager::GetPressedPause(void)
{
	if(INPUT->KeyPressed(DIK_ESCAPE) || m_PlayerController->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START && m_bStart == false)
	{
		m_bStart = true;
		return true;
	}
	else if(!(m_PlayerController->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START) && m_bStart == true)
		m_bStart = false;

	return false;
}
