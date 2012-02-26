#include "StdAfx.h"
#include "TestPlayer.h"

#include "../Input Manager/CInputManager.h"
#include "../States/CGameplayState.h"
#include "../Tile Mapping/CWorldEngine.h"
#define WORLD CWorldEngine::GetInstance()


// Initialize all variables to BASE_CHAR defaults
void TestPlayer::Enter(void)
{
	m_uiSpriteIndex = TEX_MNG->LoadTexture("resource/test.png", D3DCOLOR_XRGB(255, 255, 255));
	SetPosX(0);
	SetPosY(0);
	m_uiCurrentAnimation = 0;
	CAnimationManager::GetInstance()->LoadAnimation("resource/Char Walk.xml");
	m_footsteps.Load("Resource/data/leafyburst.xml");
	m_pAnimation[ANM_UP] = new CAnimationPlayer(ANM_FILE_UP, true);
	m_pAnimation[ANM_DOWN] = new CAnimationPlayer(ANM_FILE_DOWN, true);
	m_pAnimation[ANM_LEFT] = new CAnimationPlayer(ANM_FILE_LEFT, true);
	m_pAnimation[ANM_RIGHT] = new CAnimationPlayer(ANM_FILE_RIGHT, true);
	m_pAnimation[ANM_UP]->Play();
	m_pAnimation[ANM_DOWN]->Play();
	m_pAnimation[ANM_LEFT]->Play();
	m_pAnimation[ANM_RIGHT]->Play();
}

// Input
void TestPlayer::Input(void)
{
	int nNewPosX = GetPosX();
	int nNewPosY = GetPosY();

	if(CInputManager::GetInstance()->GetLeft())
	{
		m_uiCurrentAnimation = ANM_LEFT;
		nNewPosX-= 2;
	}
	if(CInputManager::GetInstance()->GetRight())
	{
		m_uiCurrentAnimation = ANM_RIGHT;
		nNewPosX+= 2;

	}

	if(CInputManager::GetInstance()->GetUp())
	{
		m_uiCurrentAnimation = ANM_UP;
		nNewPosY-= 2;
	}
	if(CInputManager::GetInstance()->GetDown())
	{
		m_uiCurrentAnimation = ANM_DOWN;
		nNewPosY+= 2;
	}

	if(nNewPosY < GetPosY() && nNewPosX < GetPosX())
	{
		m_uiCurrentAnimation = ANM_LEFT;
	}
	else if(nNewPosY < GetPosY() && nNewPosX > GetPosX())
	{
		m_uiCurrentAnimation = ANM_RIGHT;
	}
	else if(nNewPosY < GetPosY())
	{
		m_uiCurrentAnimation = ANM_UP;
	}
	else if(nNewPosY > GetPosY() && nNewPosX < GetPosX())
	{
		m_uiCurrentAnimation = ANM_LEFT;
	}
	else if(nNewPosY > GetPosY() && nNewPosX > GetPosX())
	{
		m_uiCurrentAnimation = ANM_RIGHT;
	}
	else if(nNewPosY > GetPosY())
	{
		m_uiCurrentAnimation = ANM_DOWN;
	}

	if(nNewPosX != GetPosX() || nNewPosY != GetPosY())
		m_footsteps.Fire(
		CGameplayState::GetInstance()->GetScreenPositionX(nNewPosX),
		CGameplayState::GetInstance()->GetScreenPositionY(nNewPosY));

	TestPlayer test;
	test.Enter();
	test.SetPosX(nNewPosX);
	test.SetPosY(nNewPosY);

	if(!WORLD->CheckCollisions(&test))
	{
		SetPosX(nNewPosX);
		SetPosY(nNewPosY);
	}
}

// Draw to the screen
void TestPlayer::Render(void)
{
	//TEX_MNG->Draw(m_uiSpriteIndex, GetPosX(), GetPosY());

	m_pAnimation[m_uiCurrentAnimation]->Render(
		CGameplayState::GetInstance()->GetScreenPositionX(GetPosX()),
		CGameplayState::GetInstance()->GetScreenPositionY(GetPosY()));
	m_footsteps.Render();
}

void TestPlayer::Update(float fElapsedTime)
{
	m_pAnimation[m_uiCurrentAnimation]->Update(fElapsedTime);
	m_footsteps.Update(fElapsedTime);
}

// Get the rectangle used for collision
RECT TestPlayer::GetCollisionRect(void) const
{
	RECT rectCollision = m_pAnimation[m_uiCurrentAnimation]->ReturnCollisionRect();
	Point anchor = m_pAnimation[m_uiCurrentAnimation]->ReturnAnchorPoint();

	rectCollision.top += GetPosY() - anchor.y;
	rectCollision.left += GetPosX() - anchor.x;
	rectCollision.bottom += GetPosY() - anchor.y;
	rectCollision.right += GetPosX() - anchor.x;

	return rectCollision;
}
