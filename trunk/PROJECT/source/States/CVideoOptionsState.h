////////////////////////////////////////////////////////////////////////
//    File Name				:	"CVideoOptionsState.h"
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/13/12 - 6:42 PM
//    Purpose				:	Contains the CVideoOptionsState
////////////////////////////////////////////////////////////////////////

#ifndef _CVIDEOOPTIONSSTATE_H_
#define _CVIDEOOPTIONSSTATE_H_
#include "CBaseMenu.h"
#include "../CGame.h"

enum {VDEO_FULLSCREEN = 0, VDEO_SHOWHUD, VDEO_MINIMAP, VDEO_BACK, VDEO_MAX};

class CVideoOptionsState : public IGameState, public CBaseMenu
{
private:
	//	Instance
	static CVideoOptionsState* m_pInstance;

	//	Constructor & Trilogy
	CVideoOptionsState();
	CVideoOptionsState(const CVideoOptionsState&);
	CVideoOptionsState& operator=(const CVideoOptionsState&);
	~CVideoOptionsState();
	
	//	Assets

	//	Members

public:
	//	Singleton
	static CVideoOptionsState* GetInstance();
	static void DeleteInstance();

	void Enter();
	void Exit();
	bool Input();
	void Update(float fElapsedTime);
	void Render();
};

#endif