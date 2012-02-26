////////////////////////////////////////////////////////////////////////
//    File Name				:	"CNewGameState.h"
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/16/12 - 5:15 PM
//    Purpose				:	Three-slot menu for New Game File
////////////////////////////////////////////////////////////////////////

#ifndef _CNEWGAMESTATE_H_
#define _CNEWGAMESTATE_H_
#include "CBaseMenu.h"
#include "../CGame.h"

enum {NEWG_SLOT1 = 0, NEWG_SLOT2, NEWG_SLOT3, NEWG_BACK, NEWG_MAX};

class CNewGameState : public CBaseMenu
{
private:
	//	Instance
	static CNewGameState* m_pInstance;

	//	Constructor & Trilogy
	CNewGameState();
	CNewGameState(const CNewGameState&);
	CNewGameState& operator=(const CNewGameState&);
	~CNewGameState();
	
	//	Assets

	//	Members

public:
	//	Singleton
	static CNewGameState* GetInstance();
	static void DeleteInstance();

	void Enter();
	void Exit();
	bool Input();
	void Update(float fElapsedTime);
	void Render();
};

#endif