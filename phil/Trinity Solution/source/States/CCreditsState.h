////////////////////////////////////////////////////////////////////////
//    File Name				:	"CCreditsState.h"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the CreditsState
////////////////////////////////////////////////////////////////////////

#ifndef _CCREDITSSTATE_H_
#define _CCREDITSSTATE_H_
#include "IGameState.h"

class CCreditsState : public IGameState
{
private:
	int m_imgBackground;

public:
	void Enter();
	void Exit();
	bool Input();
	void Update(float fElapsedTime);
	void Render();
	static CCreditsState* GetInstance();
};
#endif