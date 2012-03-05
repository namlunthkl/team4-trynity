////////////////////////////////////////////////////////////////////////
//    File Name				:	"CBaseMenu.h"
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/16/12 - 1:22 AM
//    Purpose				:	Base menu that shares common menu stuff
////////////////////////////////////////////////////////////////////////

#ifndef _C_BASE_MENU_H_
#define _C_BASE_MENU_H_
#include "IGameState.h"
#include "../CGame.h"
#include "../CBitmapFont.h"

class CBaseMenu : public IGameState
{
private:
	//	Instance
	static CBaseMenu* m_pInstance;

public:
	//	Constructor & Trilogy
	CBaseMenu();
	CBaseMenu(const CBaseMenu&);
	CBaseMenu& operator=(const CBaseMenu&);
	~CBaseMenu();
private:
	//	Assets
	int m_imgCursor;
	int m_imgTitle;
	int m_imgTeamLogo;
	int m_imgLeaderLogo;
	int m_sndMoveCursor;
	int m_sndConfirm;

	int m_imgTempTitle;

protected:
	//	Members
	bool bMenuConfirm;
	float m_fLogoTimer;
	float m_fCursorTime;
	unsigned int m_uiCurSelected;
	unsigned int m_uiMenuCount;
	CBitmapFont* pFont;
	
	//	I AM STUPID AND HAVE NO IDEA HOW DANIEL DID HIS SCROLLING SO I'M DOING IT MY RETARDED WAY -PHIL
	float m_fDerpScroll;
	bool m_bDerpBool;
	unsigned int m_uiPic;

	// Variables for background scrolling
	int* m_pnTitleIndex;
	bool* m_pbTitleScrollDir;
	DWORD m_dwTitleScrollStamp;

public:
	//	Singleton
	static CBaseMenu* GetInstance();
	static void DeleteInstance();

	void Enter();
	void Exit();
	bool Input();
	void Update(float fElapsedTime);
	void Render();

	inline void SetTitleIndex(int* pnTitleIndex) { m_pnTitleIndex = pnTitleIndex; }
	inline void SetTitleScrollDir(bool* pbTitleScrollDir) { m_pbTitleScrollDir = pbTitleScrollDir; }
};

#endif