////////////////////////////////////////////////////////////////////////
//    File Name				:	"CBaseMenu.cpp"
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/16/12 - 1:22 AM
//    Purpose				:	Base menu that shares common menu stuff
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "../StdAfx.h"
#include "CBaseMenu.h"
#include "../Input Manager/CInputManager.h"
CBaseMenu* CBaseMenu::m_pInstance = NULL;


/////////////////////////////////////////////////////
// Change between the two logo versions here

// #define LOGO LOGO2
#define LOGO LOGO2

////////////////////////////////////////////////////


#define LOGO1 "resource/Logo.png"
#define LOGO2 "resource/Logo2.png"

CBaseMenu::CBaseMenu()
{
	m_imgCursor = -1;
	m_imgTitle = -1;
	m_imgSword = -1;
	m_imgHammer = -1;
	m_imgCrossbow = -1;
	m_sndMoveCursor = -1;
	m_sndConfirm = -1;

	m_imgTempTitle = -1;

	m_uiCurSelected = 0;
	m_uiMenuCount = 0;
	m_fCursorTime = 0.0f;
	m_fLoadTimer = 0.0f;

	m_pnTitleIndex = new int;
	m_pbTitleScrollDir = new bool;
	*m_pnTitleIndex = 0;
	*m_pbTitleScrollDir = true;

	m_dwTitleScrollStamp = timeGetTime();

	bMenuConfirm = false;

	//phil scrolling
	m_fDerpScroll = 0.0f;
	m_bDerpBool = false;
	m_uiPic = 0;
	//phil

	CInputManager::GetInstance()->SetController(1);
}

CBaseMenu::~CBaseMenu()
{
}

CBaseMenu* CBaseMenu::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CBaseMenu;
	}
	return m_pInstance;
}

void CBaseMenu::DeleteInstance()
{
	if(m_pInstance != NULL)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

void CBaseMenu::Enter()
{
	//	Load Assets
	m_imgCursor = TEX_MNG->LoadTexture("resource/MenuCursor.png", D3DCOLOR_XRGB(0,0,0));
	m_imgTitle = TEX_MNG->LoadTexture("resource/MenuHorizons.png");
	m_imgSword = TEX_MNG->LoadTexture("resource/TempAsset2.png");
	m_imgHammer = TEX_MNG->LoadTexture("resource/TempAsset2.png");
	m_imgCrossbow = TEX_MNG->LoadTexture("resource/TempAsset2.png");
	m_sndMoveCursor = AUDIO->SFXLoadSound("resource/MenuMove.wav");
	m_sndConfirm = AUDIO->SFXLoadSound("resource/MenuEnter.wav");

	SetBGMusic(AUDIO->MusicLoadSong("resource/KSC_Dramatic.xwm"));

	m_imgTempTitle = TEX_MNG->LoadTexture(LOGO);

	//	Members
	m_fLoadTimer = 0.0f;
	m_fCursorTime = 0.0f;

	//phil
	m_fDerpScroll = 0.0f;
	m_bDerpBool = false;
	m_uiPic = 0;
	//

	//	Play Song
	if(!AUDIO->MusicIsSongPlaying(GetBGMusic()))
		AUDIO->MusicPlaySong(GetBGMusic(),true);

	pFont = new CBitmapFont;
}

void CBaseMenu::Exit()
{
	//	Stop Song
	//

	//	Unload Assets
	TEX_MNG->UnloadTexture(m_imgCursor);
	TEX_MNG->UnloadTexture(m_imgTitle);
	TEX_MNG->UnloadTexture(m_imgSword);
	TEX_MNG->UnloadTexture(m_imgHammer);
	TEX_MNG->UnloadTexture(m_imgCrossbow);
	//unloadsonghere
	m_imgCursor = -1;
	m_imgTitle = -1;
	m_imgSword = -1;
	m_imgHammer = -1;
	m_imgCrossbow = -1;
	m_sndMoveCursor = -1;
	m_sndConfirm = -1;

	//	Delete font
	if(pFont)
	{
		delete pFont;
		pFont = NULL;
	}
}

bool CBaseMenu::Input()
{	
	if(CInputManager::GetInstance()->GetPressedA())
	{
		AUDIO->SFXPlaySound(m_sndConfirm, false);
		bMenuConfirm = true;
	}
	else if(CInputManager::GetInstance()->GetPressedDown())
	{
		if(m_uiMenuCount > 0)
		{
			AUDIO->SFXPlaySound(m_sndMoveCursor, false);
			++m_uiCurSelected;
			if(m_uiCurSelected == m_uiMenuCount)
			{
				m_uiCurSelected = 0;
			}
		}
	}
	else if(CInputManager::GetInstance()->GetPressedUp())
	{
		if(m_uiMenuCount > 0)
		{
			AUDIO->SFXPlaySound(m_sndMoveCursor, false);
			--m_uiCurSelected;
			if(m_uiCurSelected > m_uiMenuCount)	//	We are checking if it is *above* the max menu count, because it is an unsigned int.
			{
				m_uiCurSelected = m_uiMenuCount - 1;
			}
		}
	}
	return true;
}

void CBaseMenu::Update(float fElapsedTime)
{
	m_fCursorTime += fElapsedTime;
	if(m_fCursorTime >= 0.8f)
	{
		m_fCursorTime = 0.0f;
	}
	
	m_fDerpScroll += (fElapsedTime * 25);
}

void CBaseMenu::Render()
{
	/*RECT rCursor;
	rCursor.left = 0;
	rCursor.top = 0;
	rCursor.right = 16;
	rCursor.bottom = 16;*/


	// Draw Title Background Moving
	RECT rectSourceTitle;
	//rectSourceTitle.left = (long)((*m_pnTitleIndex) * 0.35);
	rectSourceTitle.left = (long)(m_fDerpScroll);
	rectSourceTitle.top = 0 + m_uiPic*256;
	rectSourceTitle.right = rectSourceTitle.left + 400;
	rectSourceTitle.bottom = 256 + m_uiPic*256;

	if(m_fDerpScroll >= 624)	//	Please don't change this number, it's an exact relation of image size/scale and game width/resolution so that the image can perfectly reach the end before swapping images
	{
		++m_uiPic;
		m_fDerpScroll = 0.0f;
		if(m_uiPic == 3)
			m_uiPic = 0;
	}

	float alpha = 0.0f;

	if(m_fDerpScroll <= 100)
	{
		alpha = (m_fDerpScroll) * (255.0f/100);
	}
	else if(m_fDerpScroll >= 524)
	{
		alpha = (100 - (m_fDerpScroll - 524)) * (255.0f/100);
	}
	else
		alpha = 255;
	D3D->Clear(0, 0, 0);
	TEX_MNG->Draw(m_imgTitle, 0, 0, 2.0f, 2.34375f, &rectSourceTitle, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB((unsigned int)alpha, 255, 255, 255));	//	2.34375 IS CORRECT!  Because the original height of panoram is 256, and it needs to be scaled to exactly 600.

	/*if (timeGetTime() - m_dwTitleScrollStamp > 10)
	{
		if(*m_pbTitleScrollDir)
		{
			(*m_pnTitleIndex)++;
			if(GAME->GetScreenWidth() + (*m_pnTitleIndex) * 0.35 >= 1200)
				*m_pbTitleScrollDir = false;
		}
		else
		{
			(*m_pnTitleIndex)--;
			if((*m_pnTitleIndex) == 0)
				*m_pbTitleScrollDir = true;
		}
		m_dwTitleScrollStamp = timeGetTime();
	}*/
	
	//	TODO Temp Title
	TEX_MNG->Draw(m_imgTempTitle, GAME->GetScreenWidth()/2 - 268,
		GAME->GetScreenHeight()/2 - 243);

	//	Draw a cursor at intervals of the text
	//pFont->Write("XX", 0, 12 + m_uiCurSelected, D3DCOLOR_XRGB(255, 255, 255));
	RECT rCursor;

	if(m_fCursorTime <= 0.1f)
	{
		rCursor.left = 0;
		rCursor.top = 0;
		rCursor.right = 32;
		rCursor.bottom = 32;
	}
	else if(m_fCursorTime <= 0.2f)
	{
		rCursor.left = 32;
		rCursor.top = 0;
		rCursor.right = 64;
		rCursor.bottom = 32;
	}
	else if(m_fCursorTime <= 0.3f)
	{
		rCursor.left = 64;
		rCursor.top = 0;
		rCursor.right = 96;
		rCursor.bottom = 32;
	}
	else if(m_fCursorTime <= 0.4f)
	{
		rCursor.left = 96;
		rCursor.top = 0;
		rCursor.right = 128;
		rCursor.bottom = 32;
	}
	else if(m_fCursorTime <= 0.5f)
	{
		rCursor.left = 0;
		rCursor.top = 32;
		rCursor.right = 32;
		rCursor.bottom = 64;
	}
	else if(m_fCursorTime <= 0.6f)
	{
		rCursor.left = 32;
		rCursor.top = 32;
		rCursor.right = 64;
		rCursor.bottom = 64;
	}
	else if(m_fCursorTime <= 0.7f)
	{
		rCursor.left = 64;
		rCursor.top = 32;
		rCursor.right = 96;
		rCursor.bottom = 64;
	}
	else
	{
		rCursor.left = 96;
		rCursor.top = 32;
		rCursor.right = 128;
		rCursor.bottom = 64;
	}
	TEX_MNG->Draw(m_imgCursor, 0, 384+(m_uiCurSelected*32), 1.0f, 1.0f, &rCursor);
}