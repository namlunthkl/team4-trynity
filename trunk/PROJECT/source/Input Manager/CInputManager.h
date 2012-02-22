////////////////////////////////////////////////////////////////////////
//    File Name				:	"CInputManager.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the inputManager for the Controller/
//								Keyboard
////////////////////////////////////////////////////////////////////////
#ifndef _CINPUTMANAGER_H_
#define _CINPUTMANAGER_H_

// Xbox Controller
#include "CXboxController.h"
#pragma comment(lib,"XInput.lib")

class CInputManager
{
private:
	CXboxController* m_PlayerController;
	static CInputManager m_Instance;
	bool m_bControllerSet,m_bStart,m_bLBumper,m_bRBumper,m_bYButton,m_bRightTrigger;
	CInputManager(void);
	CInputManager(const CInputManager&);
	CInputManager& operator=(const CInputManager&);
public:
	static CInputManager* GetInstance() {return &m_Instance;}
	void SetController(int PlayerController) 
	{
		m_PlayerController = new CXboxController(PlayerController);
		m_bControllerSet = true;
	}
	bool GetPause(void);
	bool GetFoward(void);
	bool GetLeft(void);
	bool GetRight(void);
	bool GetDown(void);
	bool GetSwapWeapon(void);
	bool GetSwapMask(void);
	bool GetInventory(void);
	bool GetAttack(void);
};
#endif