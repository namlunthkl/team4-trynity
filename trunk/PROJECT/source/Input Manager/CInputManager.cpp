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

bool CInputManager::GetPause(void)
{
	if(INPUT->KeyPressed(DIK_ESCAPE))
		return true;
	else if(m_bControllerSet && m_PlayerController->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START)
		return true;

	return false;
}
bool CInputManager::GetFoward(void)
{
	if(INPUT->KeyPressed(DIK_W))
		return true;
	else if(m_bControllerSet && m_PlayerController->GetState().Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return true;

	return false;
}
bool CInputManager::GetLeft(void)
{
	if(INPUT->KeyPressed(DIK_A))
		return true;
	else if(m_bControllerSet && m_PlayerController->GetState().Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return true;

	return false;
}
bool CInputManager::GetRight(void)
{
	if(INPUT->KeyPressed(DIK_D))
		return true;
	else if(m_bControllerSet && m_PlayerController->GetState().Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return true;

	return false;
}
bool CInputManager::GetDown(void)
{
	if(INPUT->KeyPressed(DIK_S))
		return true;
	else if(m_bControllerSet && m_PlayerController->GetState().Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return true;

	return false;
}
bool CInputManager::GetSwapWeapon(void)
{
	if(INPUT->KeyPressed(DIK_Q))
		return true;
	else if(m_bControllerSet && m_PlayerController->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
		return true;

	return false;
}
bool CInputManager::GetSwapMask(void)
{
	if(INPUT->KeyPressed(DIK_E))
		return true;
	else if(m_bControllerSet && m_PlayerController->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
		return true;

	return false;
}
bool CInputManager::GetInventory(void)
{
	if(m_bControllerSet && INPUT->KeyPressed(DIK_TAB))
		return true;
	else if(m_PlayerController->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		return true;

	return false;
}
bool CInputManager::GetAttack(void)
{
	if(m_bControllerSet && INPUT->KeyPressed(DIK_RETURN))
		return true;
	else if(m_PlayerController->GetState().Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return true;

	return false;
}
