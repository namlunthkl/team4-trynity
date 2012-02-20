#ifndef CBASECHARACTER_H_
#define CBASECHARACTER_H_

#include "../StdAfx.h"
#include "../IBaseInterface.h"

class TestPlayer : public IBaseInterface
{
public:

	unsigned int m_uiSpriteIndex;

	// Contructor
	TestPlayer(void) {}
	// Destructor
	~TestPlayer(void) {}

	// Initialize all variables to BASE_CHAR defaults
	virtual void Enter(void)
	{
		m_uiSpriteIndex = TEX_MNG->LoadTexture("resource/test.png", D3DCOLOR_XRGB(255, 255, 255));
		SetPosX(0);
		SetPosY(0);
	}

	// Draw to the screen
	void Render(void)
	{
		TEX_MNG->Draw(m_uiSpriteIndex, GetPosX(), GetPosY());
	}

	// Get the rectangle used for collision
	RECT GetCollisionRect(void)
	{
		RECT collision;
		collision.left = GetPosX();
		collision.top = GetPosY();
		collision.right = GetPosX() + TEX_MNG->GetTextureWidth(m_uiSpriteIndex);
		collision.bottom = GetPosY() + TEX_MNG->GetTextureHeight(m_uiSpriteIndex);

		return collision;
	}

	void Update() {}
	void AddRef() {}
	void Release() {}
	unsigned int GetType() { return 1;}
	bool CheckCollision(IBaseInterface* pBase) { return false; }
};


#endif // CBASECHARACTER_H_