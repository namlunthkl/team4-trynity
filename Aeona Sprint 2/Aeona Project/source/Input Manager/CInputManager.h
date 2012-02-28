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
	bool m_bControllerSet,m_bStart,m_bLBumper,m_bRBumper,m_bYButton,m_bRightTrigger,m_bUp,m_bDown,m_bLeft,m_bRight,m_bA,m_bBack,m_bB;
	float m_fTimeheld;
	
	CInputManager(void){}

	~CInputManager(void){}
	CInputManager(const CInputManager&){}
	CInputManager& operator=(const CInputManager&){}
	
public:
	static CInputManager* GetInstance() 
	{
		static CInputManager m_Instance;
		return &m_Instance;
	}

	void SetController(int PlayerController);

	bool GetPause(void);

	bool GetUp(void);
	bool GetLeft(void);
	bool GetRight(void);
	bool GetDown(void);

	bool GetPressedUp(void);
	bool GetPressedLeft(void);
	bool GetPressedRight(void);
	bool GetPressedDown(void);
	bool GetPressedA(void);
	bool GetPressedPause(void);
	//bool GetUpUp(void);
	//bool GetUpLeft(void);
	//bool GetUpRight(void);
	//bool GetUpDown(void);
	bool GetDownBack(void);
	bool DeleteGame(void);
	bool GetPressedBack(void);
	bool GetPressedB(void);
	bool GetSwapWeapon(void);
	bool GetSwapMask(void);
	bool GetInventory(void);
	bool GetAttack(void);
	float Timeheld() const { return m_fTimeheld; }
};
#endif