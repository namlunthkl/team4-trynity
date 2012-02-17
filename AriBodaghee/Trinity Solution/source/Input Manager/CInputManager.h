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
#include <XInput.h>

class CInputManager
{
private:
	XINPUT_STATE m_ControllerState;
	int m_nControllerNum;
public:
	CInputManager(int nPlayerNumber = -1);
	XINPUT_STATE GetState();
	bool IsConnected();
	void Vibrate(int nLeftVal, int nRightVal);
	static CInputManager* GetInstance();
};
#endif