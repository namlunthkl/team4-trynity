////////////////////////////////////////////////////////////////////////
//    File Name				:	"CLoadGameState.h"
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/16/12 - 5:15 PM
//    Purpose				:	Three-slot menu for Load Game File
////////////////////////////////////////////////////////////////////////

#ifndef _CLOADGAMESTATE_H_
#define _CLOADGAMESTATE_H_
#include "CBaseMenu.h"
#include "../CGame.h"

enum {LODG_SLOT1 = 0, LODG_SLOT2, LODG_SLOT3, LODG_BACK, LODG_MAX};

class CLoadGameState : public IGameState, public CBaseMenu
{
private:
	//	Instance
	static CLoadGameState* m_pInstance;

	//	Constructor & Trilogy
	CLoadGameState();
	CLoadGameState(const CLoadGameState&);
	CLoadGameState& operator=(const CLoadGameState&);
	~CLoadGameState();
	
	//	Assets

	//	Members

public:
	//	Singleton
	static CLoadGameState* GetInstance();
	static void DeleteInstance();

	void Enter();
	void Exit();
	bool Input();
	void Update(float fElapsedTime);
	void Render();
};

#endif