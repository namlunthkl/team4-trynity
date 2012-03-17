////////////////////////////////////////////////////////////////////////
//    File Name				:	"CBaseObject.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/25 - 8:30 PM
//    Purpose				:	Class that inherits from IBaseInterface
//								and contains all the functionality that
//								is common to all game objects
////////////////////////////////////////////////////////////////////////

// Precompiled header
#include "StdAfx.h"
#include "../StdAfx.h"
// Include header file
#include "CBaseObject.h"
// For rendering using screen position
#include "../States/CGameplayState.h"
#include "../Camera/CCameraControl.h"

// Constructor
CBaseObject::CBaseObject(double dPositionX, double dPositionY, unsigned int uiSpeed, int nImageID, unsigned int uiWidth, unsigned int uiHeight, bool bActive)
{
	m_ptPosition.x		= dPositionX;
	m_ptPosition.y		= dPositionY;
	m_ptAnchor.x		= 0;
	m_ptAnchor.y		= 0;
	m_uiSpeed			= uiSpeed;
	m_nImageID			= nImageID;
	m_uiWidth			= uiWidth;
	m_uiHeight			= uiHeight;
	m_bActive			= bActive;
	m_anmCurrent		= -1;
	m_vecVelocity.fX	= 0.0f;
	m_vecVelocity.fY	= 0.0f;
	m_uiRefCount		= 1;
	m_bDebugMode		= false;

	m_uiEnemyBehavior = 0;
	m_uiMiniState = 0;
	m_uiPhilDirection = 0;
	philEnemyColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_bWalkCycle = 0;
	m_bDying = false;
	m_bTrulyDead = false;
	m_fDeathAnim = 0.0f;
	m_bSpecial = false;
	m_uiSpecialCounter = 0;
}

// Common routines
void CBaseObject::Update(float fElapsedTime)
{
	if(!IsActive()) return;

	// Update position based on velocity
	if(m_uiEnemyBehavior == 0 || (m_uiEnemyBehavior != 0 && m_bDying == false))
	{
		m_ptPosition.x = (m_ptPosition.x + m_vecVelocity.fX * fElapsedTime);
		m_ptPosition.y = (m_ptPosition.y + m_vecVelocity.fY * fElapsedTime);
	}

	if(m_anmCurrent != -1 && m_anmCurrent < (int)m_vpAnimations.size())
	{
		m_vpAnimations[m_anmCurrent]->Update(fElapsedTime);
	}

	if(m_bDying == true)
		m_fDeathAnim += fElapsedTime*7.0f;
}

void CBaseObject::Input(void)
{

}

void CBaseObject::Render(void)
{
	if(!IsActive()) return;

	if( m_uiEnemyBehavior == 0)	//	use the animation editor here, if this value is 0
	{
		// If there's no animation, render object's image in its position
		if(m_vpAnimations.empty())
		{
			TEX_MNG->Draw(m_nImageID, (int)m_ptPosition.x - m_ptAnchor.x, (int)m_ptPosition.y - m_ptAnchor.y);
		}
		else if(m_anmCurrent != -1 && m_anmCurrent < (int)m_vpAnimations.size())
		{
			m_vpAnimations[m_anmCurrent]->Render((int)m_ptPosition.x, (int)m_ptPosition.y);
		}
	}
	else	//	Else, if we are an enemy, let's render a different way, for more control for AI and stuff
	{
		if( m_bDying == false )
		{
			RECT enemy;
			enemy.left = 0 + (m_uiPhilDirection*96);
			enemy.top = 0 + (96*(int)m_bWalkCycle) + ((m_uiEnemyBehavior-1)*192);
			enemy.right = 96 + (m_uiPhilDirection*96);
			enemy.bottom = 96 + (96*(int)m_bWalkCycle) + ((m_uiEnemyBehavior-1)*192);

			RECT shadow;
			shadow.left = 512-32;
			shadow.top = 0;
			shadow.right = 512;
			shadow.bottom = 32;

			if( m_bSpecial == true )
			{
				enemy.left = 384;
				enemy.right = 384+96;
			}

			float scale = 1.0f;

			if(m_uiEnemyBehavior == BEHAVIOR_GOLEM || m_uiEnemyBehavior == BEHAVIOR_SNOWGOLEM || m_uiEnemyBehavior == BEHAVIOR_LAVAGOLEM)
				scale = 2.0f;

			//TEX_MNG->Draw(GAME->m_imgEnemies, (int)m_ptPosition.x - (48*1), (int)m_ptPosition.y - (48*1), 1.0f, 1.0f, &enemy, 0.0f, 0.0f, 0.0f, philEnemyColor);
			TEX_MNG->Draw(GAME->m_imgEnemiesDeath, (int)m_ptPosition.x -(24)/*- (48*scale)*/, (int)m_ptPosition.y -(24)/*- (48*scale)*/, scale*1.5f, scale*1.5f, &shadow, 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 255));
			TEX_MNG->Draw(GAME->m_imgEnemies, (int)(m_ptPosition.x - 48*scale), (int)(m_ptPosition.y - 48*scale), scale, scale, &enemy, 0.0f, 0.0f, 0.0f, philEnemyColor);
		}
		else
		{
			if(m_fDeathAnim < 4.0f )
			{
				RECT enemy;
				enemy.left = 0 + ((int)m_fDeathAnim * 96);
				enemy.top = 0;
				enemy.right = 96 + ((int)m_fDeathAnim * 96);
				enemy.bottom = 96;

				if(m_uiEnemyBehavior == BEHAVIOR_GOLEM || m_uiEnemyBehavior == BEHAVIOR_SNOWGOLEM || m_uiEnemyBehavior == BEHAVIOR_LAVAGOLEM)
				{
					enemy.top = 96;
					enemy.bottom = 192;
				}

				TEX_MNG->Draw(GAME->m_imgEnemiesDeath, (int)m_ptPosition.x - 48, (int)m_ptPosition.y - 48, 1.0f, 1.0f, &enemy, 0.0f, 0.0f, 0.0f, philEnemyColor);
			}
			else
			{
				// DANIEL CODE BEGIN
				// That's where the enemy is finally killed,
				// when the death animation has finished playing

				// We won't do this anymore..
				// CMessageSystem::GetInstance()->SendMsg(new CDestroyObjectMessage(this));

				// Instead...
				Deactivate();
				m_bTrulyDead = true;
				// DANIEL CODE END
			}
		}
	}

	//D3D->GetSprite()->Flush();

	if(m_bDebugMode)
	{
		RectD rect = GetCollisionRect();
		rect.OffsetRect(CCameraControl::GetInstance()->GetPositionX(),
			CCameraControl::GetInstance()->GetPositionY());
		D3D->DrawRect(rect.GetWindowsRECT(), 0, 0, 255);
	}
}
void CBaseObject::Render(DWORD WHICHCOLORYOUWANTHIMTOGLOWBRO)
{
	if(!IsActive()) return;

	if( m_uiEnemyBehavior == 0)	//	use the animation editor here, if this value is 0
	{
		// If there's no animation, render object's image in its position
		if(m_vpAnimations.empty())
		{
			TEX_MNG->Draw(m_nImageID, (int)m_ptPosition.x - m_ptAnchor.x, (int)m_ptPosition.y - m_ptAnchor.y,1.0f,1.0f,0,0.0f,0.0f,0.0f,WHICHCOLORYOUWANTHIMTOGLOWBRO);
		}
		else if(m_anmCurrent != -1 && m_anmCurrent < (int)m_vpAnimations.size())
		{
			m_vpAnimations[m_anmCurrent]->Render((int)m_ptPosition.x, (int)m_ptPosition.y,WHICHCOLORYOUWANTHIMTOGLOWBRO);
		}
	}
	else	//	Else, if we are an enemy, let's render a different way, for more control for AI and stuff
	{
		if( m_bDying == false )
		{
			RECT enemy;
			enemy.left = 0 + (m_uiPhilDirection*96);
			enemy.top = 0 + (96*(int)m_bWalkCycle) + ((m_uiEnemyBehavior-1)*192);
			enemy.right = 96 + (m_uiPhilDirection*96);
			enemy.bottom = 96 + (96*(int)m_bWalkCycle) + ((m_uiEnemyBehavior-1)*192);

			RECT shadow;
			shadow.left = 512-32;
			shadow.top = 0;
			shadow.right = 512;
			shadow.bottom = 32;

			if( m_bSpecial == true )
			{
				enemy.left = 384;
				enemy.right = 384+96;
			}

			float scale = 1.0f;

			if(m_uiEnemyBehavior == BEHAVIOR_GOLEM || m_uiEnemyBehavior == BEHAVIOR_SNOWGOLEM || m_uiEnemyBehavior == BEHAVIOR_LAVAGOLEM)
				scale = 2.0f;

			//TEX_MNG->Draw(GAME->m_imgEnemies, (int)m_ptPosition.x - (48*1), (int)m_ptPosition.y - (48*1), 1.0f, 1.0f, &enemy, 0.0f, 0.0f, 0.0f, philEnemyColor);
			TEX_MNG->Draw(GAME->m_imgEnemiesDeath, (int)m_ptPosition.x -(16)/*- (48*scale)*/, (int)m_ptPosition.y -(16)/*- (48*scale)*/, scale, scale, &shadow, 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(100, 255, 255, 255));
			TEX_MNG->Draw(GAME->m_imgEnemies, (int)(m_ptPosition.x - 48*scale), (int)(m_ptPosition.y - 48*scale), scale, scale, &enemy, 0.0f, 0.0f, 0.0f, philEnemyColor);
		}
		else
		{
			if(m_fDeathAnim < 4.0f )
			{
				RECT enemy;
				enemy.left = 0 + ((int)m_fDeathAnim * 96);
				enemy.top = 0;
				enemy.right = 96 + ((int)m_fDeathAnim * 96);
				enemy.bottom = 96;

				if(m_uiEnemyBehavior == BEHAVIOR_GOLEM || m_uiEnemyBehavior == BEHAVIOR_SNOWGOLEM || m_uiEnemyBehavior == BEHAVIOR_LAVAGOLEM)
				{
					enemy.top = 96;
					enemy.bottom = 192;
				}

				TEX_MNG->Draw(GAME->m_imgEnemiesDeath, (int)m_ptPosition.x - 48, (int)m_ptPosition.y - 48, 1.0f, 1.0f, &enemy, 0.0f, 0.0f, 0.0f, philEnemyColor);
			}
			else
			{
				// DANIEL CODE BEGIN
				// That's where the enemy is finally killed,
				// when the death animation has finished playing

				// We won't do this anymore..
				// CMessageSystem::GetInstance()->SendMsg(new CDestroyObjectMessage(this));

				// Instead...
				Deactivate();
				m_bTrulyDead = true;
				// DANIEL CODE END
			}
		}
	}

	//D3D->GetSprite()->Flush();

	if(m_bDebugMode)
	{
		RectD rect = GetCollisionRect();
		rect.OffsetRect(CCameraControl::GetInstance()->GetPositionX(),
			CCameraControl::GetInstance()->GetPositionY());
		D3D->DrawRect(rect.GetWindowsRECT(), 0, 0, 255);
	}
}

RectD CBaseObject::GetCollisionRect(void)
{
	RectD rectCollision;

	rectCollision.left = GetPosX() - m_uiWidth/2;
	rectCollision.top = GetPosY() - m_uiHeight/2;
	rectCollision.right = rectCollision.left + GetWidth();
	rectCollision.bottom = rectCollision.top + GetHeight();


	return rectCollision;
}

// Check Collision against another object
// Return true if collided, false otherwise
bool CBaseObject::CheckCollision(IBaseInterface* pObject)
{
	// if(GetType() == TYPE_CHAR_ENEMY && pObject->GetType() == TYPE_CHAR_PLAYER) return false;
	// if(GetType() == TYPE_CHAR_NPC && pObject->GetType() == TYPE_CHAR_PLAYER) return false;

	RECT rectCollisionResult = { 0, 0, 0, 0 };
	CBaseObject* pBaseObject = (CBaseObject*)pObject;

	if(IntersectRect(&rectCollisionResult, &GetCollisionRect().GetWindowsRECT(), &pBaseObject->GetCollisionRect().GetWindowsRECT()))
	{
		int nRectWidth = rectCollisionResult.right - rectCollisionResult.left;
		int nRectHeight = rectCollisionResult.bottom - rectCollisionResult.top;
		double dAnmHeight = GetCollisionRect().bottom - GetCollisionRect().top;
		double dAnmWidth = GetCollisionRect().right - GetCollisionRect().left;
		if(nRectWidth > nRectHeight)
		{
			// Top/Down Collision
			if(GetCollisionRect().top < pBaseObject->GetCollisionRect().top)
			{
				if(GetVelY() > 0)
					SetPosY(rectCollisionResult.top + GetAnchorPoint().y - dAnmHeight);
				//if(pBaseObject->GetVelY() < 0)
				//	pBaseObject->SetPosY(rectCollisionResult.bottom + pBaseObject->GetAnchorPoint().y);
			}
			else if(GetCollisionRect().bottom > pBaseObject->GetCollisionRect().bottom)
			{
				if(GetVelY() < 0)
					SetPosY(rectCollisionResult.bottom + GetAnchorPoint().y);
				//if(pBaseObject->GetVelY() > 0)
				//	pBaseObject->SetPosY(rectCollisionResult.top + pBaseObject->GetAnchorPoint().y - pBaseObject->GetHeight());
			}
		}
		if(nRectHeight > nRectWidth)
		{
			// Side Collision
			if(GetCollisionRect().left < pBaseObject->GetCollisionRect().left && GetVelX() > 0)
			{
				SetPosX(rectCollisionResult.left + GetAnchorPoint().x - dAnmWidth);
				//if(pBaseObject->GetVelX() <= 0)
				//	pBaseObject->SetPosX(rectCollisionResult.right + pBaseObject->GetAnchorPoint().x);
			}
			else if(GetCollisionRect().right > pBaseObject->GetCollisionRect().right && GetVelX() < 0)
			{
				SetPosX(rectCollisionResult.right + GetAnchorPoint().x);
				//if(pBaseObject->GetVelX() >= 0)
				//	pBaseObject->SetPosX(rectCollisionResult.left + pBaseObject->GetAnchorPoint().x - pBaseObject->GetWidth());
			}
		}		
		return true;
	}
	return false;
}


Point CBaseObject::GetAnchorPoint(void)
{
	//if(m_vpAnimations.empty())
	//{
		m_ptAnchor.x = m_uiWidth / 2;
		m_ptAnchor.y = m_uiHeight / 2;
	//}
	//else if(m_anmCurrent != -1 && m_anmCurrent < (int)m_vpAnimations.size())
	//{
	//	m_ptAnchor = m_vpAnimations[m_anmCurrent]->ReturnAnchorPoint();
	//}
	//
	return m_ptAnchor;
}

// Add and release references
void CBaseObject::AddRef(void)
{
	m_uiRefCount++;
}
void CBaseObject::Release(void)
{
	m_uiRefCount--;

	if(m_uiRefCount == 0)
		delete this;
}

// Destructor
CBaseObject::~CBaseObject(void)
{
	for(unsigned int i = 0; i < m_vpAnimations.size(); ++i)
		delete m_vpAnimations[i];

	m_vpAnimations.clear();
}


// Animation accessors and mutators
CAnimationPlayer* CBaseObject::GetAnimationPlayer (unsigned int uiAnmIndex ) const
{
	if(uiAnmIndex < m_vpAnimations.size())
		return m_vpAnimations[uiAnmIndex];
	else return nullptr;
}
void CBaseObject::PushAnimationPlayer (CAnimationPlayer* pAnimation)
{
	if(pAnimation != nullptr)
		m_vpAnimations.push_back(pAnimation);
}
bool CBaseObject::PopAnimationPlayer (void)
{
	if(m_vpAnimations.empty())
		return false;
	m_vpAnimations.pop_back();
	return true;
}
void CBaseObject::SetCurrentAnimation (int anmCurrent)
{
	if(anmCurrent < (int) m_vpAnimations.size())
		m_anmCurrent = anmCurrent;
}
void CBaseObject::SetPreviousAnimation (int anmPrevious)
{
	if(anmPrevious < (int) m_vpAnimations.size())
		m_anmPrevious = anmPrevious;
}