////////////////////////////////////////////////////////////////////////
//    File Name				:	"CXboxController.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the inputManager for the Controller/
//								Keyboard
////////////////////////////////////////////////////////////////////////
#ifndef _CXBOXCONTROLLER_H_
#define _CXBOXCONTROLLER_H_

// Xbox Controller
#include <XInput.h>
#pragma comment(lib,"XInput.lib")

class CXboxController
{
private:
	XINPUT_STATE m_ControllerState;
	int m_nControllerNum;

public:
	CXboxController(int nPlayerNumber = -1);
	XINPUT_STATE GetState();
	bool IsConnected();
	void Vibrate(int nLeftVal, int nRightVal);
};
#endif