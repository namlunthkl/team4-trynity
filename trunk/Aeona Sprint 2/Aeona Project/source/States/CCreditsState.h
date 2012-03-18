////////////////////////////////////////////////////////////////////////
//    File Name				:	"CCreditsState.h"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the CreditsState
////////////////////////////////////////////////////////////////////////

#ifndef _CCREDITSSTATE_H_
#define _CCREDITSSTATE_H_
#include "IGameState.h"
#include "../CBitmapFont.h"

class CCreditsState : public IGameState
{
private:
	//	Instance
	static CCreditsState* m_pInstance;

	int m_imgBackground;
	CBitmapFont* pFont;

	//	Constructor & Trilogy
	CCreditsState();
	CCreditsState(const CCreditsState&);
	CCreditsState& operator=(const CCreditsState&);
	~CCreditsState();

public:
	int m_fWhatever;

	//	Singleton
	static CCreditsState* GetInstance();
	static void DeleteInstance();

	void Enter();
	void Exit();
	bool Input();
	void Update(float fElapsedTime);
	void Render();
};
#endif