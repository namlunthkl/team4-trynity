////////////////////////////////////////////////////////////////////////
//    File Name				:	"CMainMenuState.h"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the CMainMenuState
////////////////////////////////////////////////////////////////////////

#ifndef _CMAINMENUSTATE_H_
#define _CMAINMENUSTATE_H_
#include "IGameState.h"
#include "../CGame.h"

enum {MAIN_NEW = 0, MAIN_LOAD, MAIN_OPTIONS, MAIN_CREDITS, MAIN_EXIT, MAIN_MAX};

class CMainMenuState : public IGameState
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
	int m_imgBackground;
	int m_imgScroll;
	int m_imgCursor;
	int m_sndMoveCursor;
	int m_sndConfirm;

	//vector<char*> m_vszMenuItems;

	//	Members
	unsigned int m_uiCurSelected;
	float m_fLoadTimer;

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