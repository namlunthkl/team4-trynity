////////////////////////////////////////////////////////////////////////
//    File Name				:	"CBaseMenu.cpp"
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/16/12 - 1:22 AM
//    Purpose				:	Base menu that shares common menu stuff
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "../StdAfx.h"
#include "CBaseMenu.h"

CBaseMenu* CBaseMenu::m_pInstance = NULL;

CBaseMenu::CBaseMenu()
{
	m_imgCursor = -1;
	m_imgTitle = -1;
	m_imgSword = -1;
	m_imgHammer = -1;
	m_imgCrossbow = -1;
	m_sndMoveCursor = -1;
	m_sndConfirm = -1;

	m_uiCurSelected = 0;
	m_uiMenuCount = 0;
	m_fCursorTime = 0.0f;
	m_fLoadTimer = 0.0f;

	bMenuConfirm = false;

	pFont = new CBitmapFont;
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
	m_imgCursor = TEX_MNG->LoadTexture("resource/MenuCursor.png");
	m_imgTitle = TEX_MNG->LoadTexture("resource/TempAsset1.png");
	m_imgSword = TEX_MNG->LoadTexture("resource/TempAsset2.png");
	m_imgHammer = TEX_MNG->LoadTexture("resource/TempAsset2.png");
	m_imgCrossbow = TEX_MNG->LoadTexture("resource/TempAsset2.png");
	m_sndMoveCursor = AUDIO->SFXLoadSound("resource/MenuMove.wav");
	m_sndConfirm = AUDIO->SFXLoadSound("resource/MenuEnter.wav");

	//	Members
	m_fLoadTimer = 0.0f;
	m_fCursorTime = 0.0f;

	//	Play Song
	//
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
	if(INPUT->KeyPressed(DIK_RETURN))
	{
		AUDIO->SFXPlaySound(m_sndConfirm, false);
		bMenuConfirm = true;
	}
	else if(INPUT->KeyPressed(DIK_DOWN))
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
	else if(INPUT->KeyPressed(DIK_UP))
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
}

void CBaseMenu::Render()
{
	/*RECT rCursor;
	rCursor.left = 0;
	rCursor.top = 0;
	rCursor.right = 16;
	rCursor.bottom = 16;*/

	//	Draw a cursor at intervals of the text
	//pFont->Write("XX", 0, 12 + m_uiCurSelected, D3DCOLOR_XRGB(255, 255, 255));
	RECT rCursor;

	if(m_fCursorTime <= 0.1f)
	{
		rCursor.left = 0.0f;
		rCursor.top = 0.0f;
		rCursor.right = 32.0f;
		rCursor.bottom = 32.0f;
	}
	else if(m_fCursorTime <= 0.2f)
	{
		rCursor.left = 32.0f;
		rCursor.top = 0.0f;
		rCursor.right = 64.0f;
		rCursor.bottom = 32.0f;
	}
	else if(m_fCursorTime <= 0.3f)
	{
		rCursor.left = 64.0f;
		rCursor.top = 0.0f;
		rCursor.right = 96.0f;
		rCursor.bottom = 32.0f;
	}
	else if(m_fCursorTime <= 0.4f)
	{
		rCursor.left = 96.0f;
		rCursor.top = 0.0f;
		rCursor.right = 128.0f;
		rCursor.bottom = 32.0f;
	}
	else if(m_fCursorTime <= 0.5f)
	{
		rCursor.left = 0.0f;
		rCursor.top = 32.0f;
		rCursor.right = 32.0f;
		rCursor.bottom = 64.0f;
	}
	else if(m_fCursorTime <= 0.6f)
	{
		rCursor.left = 32.0f;
		rCursor.top = 32.0f;
		rCursor.right = 64.0f;
		rCursor.bottom = 64.0f;
	}
	else if(m_fCursorTime <= 0.7f)
	{
		rCursor.left = 64.0f;
		rCursor.top = 32.0f;
		rCursor.right = 96.0f;
		rCursor.bottom = 64.0f;
	}
	else
	{
		rCursor.left = 96.0f;
		rCursor.top = 32.0f;
		rCursor.right = 128.0f;
		rCursor.bottom = 64.0f;
	}
	TEX_MNG->Draw(m_imgCursor, 0, 384+(m_uiCurSelected*32), 1.0f, 1.0f, &rCursor);
}