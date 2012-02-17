////////////////////////////////////////////////////////////////////////
//    File Name				:	"CAudioOptionsState.h"
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/13/12 - 6:42 PM
//    Purpose				:	Contains the CAudioOptionsState
////////////////////////////////////////////////////////////////////////

#ifndef _CAUDIOOPTIONSSTATE_H_
#define _CAUDIOOPTIONSSTATE_H_
#include "IGameState.h"
#include "../CGame.h"

enum {ADIO_MUSIC = 0, ADIO_SOUND, ADIO_BACK, ADIO_MAX};

class CAudioOptionsState : public IGameState
{
private:
	//	Instance
	static CAudioOptionsState* m_pInstance;

	//	Constructor & Trilogy
	CAudioOptionsState();
	CAudioOptionsState(const CAudioOptionsState&);
	CAudioOptionsState& operator=(const CAudioOptionsState&);
	~CAudioOptionsState();
	
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
	static CAudioOptionsState* GetInstance();
	static void DeleteInstance();

	void Enter();
	void Exit();
	bool Input();
	void Update(float fElapsedTime);
	void Render();
};

#endif