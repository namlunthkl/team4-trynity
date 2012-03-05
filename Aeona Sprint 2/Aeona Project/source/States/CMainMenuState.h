////////////////////////////////////////////////////////////////////////
//    File Name				:	"CMainMenuState.h"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the CMainMenuState
////////////////////////////////////////////////////////////////////////

#ifndef _CMAINMENUSTATE_H_
#define _CMAINMENUSTATE_H_
#include "CBaseMenu.h"
#include "../CGame.h"

enum {MAIN_NEW = 0, MAIN_LOAD, MAIN_OPTIONS, MAIN_CREDITS, MAIN_EXIT, MAIN_MAX};

class CMainMenuState : public CBaseMenu
{
private:
	//	Instance
	static CMainMenuState* m_pInstance;

	//	Constructor & Trilogy
	CMainMenuState();
	CMainMenuState(const CMainMenuState&);
	CMainMenuState& operator=(const CMainMenuState&);
	~CMainMenuState();
	
	//	Assets

	//	Members
	int m_imgTempTitle;

public:
	//	Singleton
	static CMainMenuState* GetInstance();
	static void DeleteInstance();

	void Enter();
	void Exit();
	bool Input();
	void Update(float fElapsedTime);
	void Render();
};

#endif