////////////////////////////////////////////////////////////////////////
//    File Name				:	"CGameplayState.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09/12 - 1:00 AM
//    Purpose				:	Contains the GameplayState
////////////////////////////////////////////////////////////////////////

// Precompiled header
#include "StdAfx.h"

// Header file for this state
#include "CGameplayState.h"

// Singleton Macros
#define EVENTS CEventSystem::GetInstance()
#define WORLD CWorldEngine::GetInstance()

// Constructor
CGameplayState::CGameplayState(void)
{
}

// Initialize everything
void CGameplayState::Enter(void)
{
	// Initialize the world engine
	WORLD->InitWorldEngine();

	// Register for the event
	EVENTS->RegisterForEvent("SpawnMessageBox", this);
	EVENTS->RegisterForEvent("LightTorch", this);

	// Initialize our particle weapon
	PW.Load("resource/data/FireFlicker.xml");

	pPlayer = new TestPlayer();
	pPlayer->SetPosX(0);
	pPlayer->SetPosY(0);

}

bool CGameplayState::Input(void)
{
	//	Pause
	if(INPUT->KeyPressed(DIK_ESCAPE))
	{
		GAME->SetPaused( true );
	}
	
	if(INPUT->KeyPressed(DIK_RETURN))
	{
		POINT* ptPosition = new POINT;
		ptPosition->x = pPlayer->GetPosX();
		ptPosition->y = pPlayer->GetPosY();

		EVENTS->SendEvent("LightTorch", (void*)ptPosition);
	}



	return true;
}
void CGameplayState::Update(float fElapsedTime)
{
	// Update the best world engine ever created
	WORLD->UpdateWorld(fElapsedTime);
	EVENTS->ProcessEvents();

	if(PW.GetFired())
		PW.Update(fElapsedTime);
}

void CGameplayState::Render(void)
{
	// Render the best world engine ever created
	WORLD->RenderWorld();

	if(PW.GetFired())
		PW.Render();
}

void CGameplayState::Exit(void)
{
	WORLD->ShutdownWorldEngine();
	WORLD->DeleteInstance();
}

CGameplayState* CGameplayState::GetInstance(void)
{
	static CGameplayState pInstance;
	return &pInstance;
}

void CGameplayState::HandleEvent(CEvent* pEvent)
{
	if(pEvent->GetEventID() == "SpawnMessageBox")
	{
		MessageBox(GAME->GetWindowHandle(),"I Punched You","Program Name: PUNCH!",MB_OK);
	}
	else if(pEvent->GetEventID() == "LightTorch")
	{
		POINT* ptPosition = (POINT*)pEvent->GetParam();
		PW.Fire(ptPosition->x, ptPosition->y);
	}
}