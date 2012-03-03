////////////////////////////////////////////////////////////////////////
//    File Name				:	"CAudioOptionsState.cpp"
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/13/12 - 6:52 PM
//    Purpose				:	Contains the CAudioOptionsState
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "../StdAfx.h"
#include "CAudioOptionsState.h"
#include "COptionsState.h"

CAudioOptionsState* CAudioOptionsState::m_pInstance = NULL;

CAudioOptionsState::CAudioOptionsState()
{
}

CAudioOptionsState::~CAudioOptionsState()
{
}

CAudioOptionsState* CAudioOptionsState::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CAudioOptionsState;
	}
	return m_pInstance;
}

void CAudioOptionsState::DeleteInstance()
{
	if(m_pInstance != NULL)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

void CAudioOptionsState::Enter()
{
	CBaseMenu::Enter();

	//	Load Assets
	m_uiMenuCount = ADIO_MAX;
	m_fLoadTimer = 0.0f;

	//	Imperfect..
	m_uiCurSelected = 0;
}

void CAudioOptionsState::Exit()
{
}

bool CAudioOptionsState::Input()
{
	//	NOT SURE
	CBaseMenu::Input();
	//	ABOVE?

	if(bMenuConfirm == true)
	{
		//	Set it back to false
		bMenuConfirm = false;
		//	Which choice is selected?
		switch(m_uiCurSelected)
		{
		case ADIO_MUSIC:
			{
				GAME->SetMusicVolume( GAME->GetMusicVolume() + 10 );
				if(GAME->GetMusicVolume() == 110)
				{
					GAME->SetMusicVolume(0);
				}
				AUDIO->MusicSetMasterVolume( GAME->GetMusicVolume()/100.0f );
				break;
			}
		case ADIO_SOUND:
			{
				GAME->SetSoundVolume( GAME->GetSoundVolume() + 10 );
				if(GAME->GetSoundVolume() == 110)
				{
					GAME->SetSoundVolume(0);
				}
				AUDIO->SFXSetMasterVolume( GAME->GetSoundVolume()/100.0f );
				break;
			}
		case ADIO_BACK:
			{
				GAME->OutputOptionsToFile();
				GAME->ChangeState(COptionsState::GetInstance());
				break;
			}
		}
	}
	return true;
}

void CAudioOptionsState::Update(float fElapsedTime)
{
	CBaseMenu::Update(fElapsedTime);
}

void CAudioOptionsState::Render()
{
	//	Draw the base menu's stuff .. NOT SURE
	CBaseMenu::Render();

	//	Draw this menu's stuff
	char buffer[10] = {0};
	
	pFont->Write("Music Volume", 32, 12 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
		sprintf_s(buffer, "%d", GAME->GetMusicVolume());
		pFont->Write(buffer, 256, 12 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Sound Volume", 32, 13 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
		sprintf_s(buffer, "%d", GAME->GetSoundVolume());
		pFont->Write(buffer, 256, 13 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
	pFont->Write("Back", 32, 14 * pFont->GetCharHeight(), D3DCOLOR_XRGB(255, 255, 255));
}