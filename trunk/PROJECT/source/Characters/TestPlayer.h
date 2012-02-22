#ifndef CBASECHARACTER_H_
#define CBASECHARACTER_H_

#include "../StdAfx.h"
#include "../IBaseInterface.h"

#include "../Tile Mapping/CWorldEngine.h"
#include "../Animation/CAnimationPlayer.h"
#include "../Animation/CAnimationManager.h"

#define WORLD CWorldEngine::GetInstance()

class TestPlayer : public IBaseInterface
{
public:
	unsigned int m_uiSpriteIndex;
	unsigned int m_uiDirection;
	unsigned int m_uiCurrentAnimation;

	CAnimationPlayer* m_pAnimation[4];

	// Contructor
	TestPlayer(void) {}
	// Destructor
	~TestPlayer(void) {}

	enum Animation { ANM_UP, ANM_DOWN, ANM_RIGHT, ANM_LEFT };

	// Initialize all variables to BASE_CHAR defaults
	virtual void Enter(void)
	{
		m_uiSpriteIndex = TEX_MNG->LoadTexture("resource/test.png", D3DCOLOR_XRGB(255, 255, 255));
		SetPosX(0);
		SetPosY(0);
		m_uiCurrentAnimation = 0;

		CAnimationManager::GetInstance()->LoadAnimation("resource/Char Walk.xml");
		m_pAnimation[ANM_UP] = new CAnimationPlayer(ANM_UP, true);
		m_pAnimation[ANM_DOWN] = new CAnimationPlayer(ANM_DOWN, true);
		m_pAnimation[ANM_LEFT] = new CAnimationPlayer(ANM_LEFT, true);
		m_pAnimation[ANM_RIGHT] = new CAnimationPlayer(ANM_RIGHT, true);
		m_pAnimation[ANM_UP]->Play();
		m_pAnimation[ANM_DOWN]->Play();
		m_pAnimation[ANM_LEFT]->Play();
		m_pAnimation[ANM_RIGHT]->Play();
	}

	// Input
	void Input(void)
	{
		int nNewPosX = GetPosX();
		int nNewPosY = GetPosY();

		if(INPUT->KeyDown(DIK_UP))
		{
			m_uiCurrentAnimation = ANM_UP;
			nNewPosY--;
		}
		if(INPUT->KeyDown(DIK_DOWN))
		{
			m_uiCurrentAnimation = ANM_DOWN;
			nNewPosY++;
		}
		if(INPUT->KeyDown(DIK_LEFT))
		{
			m_uiCurrentAnimation = ANM_LEFT;
			nNewPosX--;
		}
		if(INPUT->KeyDown(DIK_RIGHT))
		{
			m_uiCurrentAnimation = ANM_RIGHT;
			nNewPosX++;
		}

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
	void Render(void)
	{
		//TEX_MNG->Draw(m_uiSpriteIndex, GetPosX(), GetPosY());

		m_pAnimation[m_uiCurrentAnimation]->Render(GetPosX(), GetPosY());
		D3D->GetSprite()->Flush();
	}

	void Update(float fElapsedTime)
	{
		m_pAnimation[m_uiCurrentAnimation]->Update(fElapsedTime);
	}

	// Get the rectangle used for collision
	RECT GetCollisionRect(void)
	{
		RECT rectCollision = m_pAnimation[m_uiCurrentAnimation]->ReturnCollisionRect();
		POINT anchor = m_pAnimation[m_uiCurrentAnimation]->ReturnAnchorPoint();
		
		rectCollision.top += GetPosY() - anchor.y;
		rectCollision.left += GetPosX() - anchor.x;
		rectCollision.bottom += GetPosY() - anchor.y;
		rectCollision.right += GetPosX() - anchor.x;

		return rectCollision;
	}

	void AddRef() {}
	void Release() {}
	unsigned int GetType() { return 1;}
	bool CheckCollision(IBaseInterface* pBase) { return false; }
};


#endif // CBASECHARACTER_H_