/////////////////////////////////////////////////////////
//	File Name	:	"CGame.h"
//
//	Author Name	:	David Brown (DB)
//
//	Purpose		:	To contain all game related code.
/////////////////////////////////////////////////////////
#pragma once	//	MSVStudio specific (been told it works on GCC)

////	Cross compiler (works on Borland, CodeWarrior, etc)
//#ifndef _CGAME_H_
//#define _CGAME_H_
//
////	Define class here
//
//#endif

//	SGD Wrappers
#include <Windows.h>
#include "SGD Wrappers\CSGD_Direct3D.h"
#include "SGD Wrappers\CSGD_TextureManager.h"
#include "SGD Wrappers\CSGD_DirectInput.h"
#include "CSGD_ObjectFactory.h"
#include "CSGD_ObjectManager.h"
#include "CBase.h"
#include <string>
using std::string;
#include "IGameState.h"

class CGame
{
private:
	//	Singleton pointers:
	CSGD_Direct3D*			m_pD3D;
	CSGD_TextureManager*	m_pTM;
	CSGD_DirectInput*		m_pDI;
	IGameState*				m_pCurState;
	CSGD_ObjectManager*		m_pOM;
	CSGD_ObjectFactory<string, CBase>*	m_pOF;

	DWORD					m_dwTimeStamp;
	float					m_fElapsedTime;		
	float					m_fGameTime;												
	DWORD					m_dwPreviousTimeStamp;
	
	int	m_nScreenH;
	int	m_nScreenW;
	bool m_bWindowed;

	//	Proper singleton:
	//	Constructor
	CGame(void);
	//	Trilogy of EVIL:
	//	Copy constructor
	CGame(const CGame&);
	//	Assignment operator
	CGame& operator=(const CGame&);
	//	Destructor
	~CGame(void);

	bool Input(void);
	void Update(void);
	void Render(void);

public:

	int GetScreenW(void) {return m_nScreenW; }
	int GetScreenH(void) {return m_nScreenH; }


	float GetElapsedTime(void) { return m_fElapsedTime; }

	//	Singleton accessor
	static CGame* GetInstance(void);

	//	3 things a game does during it's lifetime:
	//	Initialization
	void Initialize(HWND hWnd, HINSTANCE hInstance,
						int nScreenWidth, int nScreenHeight, bool bIsWindowed);
	//	Execution
	//	NOTE: Returns false when game should quit
	bool Main(void);
	//	Clean Up
	void Shutdown(void);
	void ChangeState( IGameState* pNewState );

	void PrintText( const char* szTextToPrint, int nPosX, int nPosY, float fScale, DWORD dwColor );
};