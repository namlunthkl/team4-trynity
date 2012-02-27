#include "StdAfx.h"
//#include "TestPlayer.h"
//
//#include "../Input Manager/CInputManager.h"
//#include "../States/CGameplayState.h"
//#include "../Tile Mapping/CWorldEngine.h"
//#define WORLD CWorldEngine::GetInstance()
//
//
//// Initialize all variables to BASE_CHAR defaults
//void TestPlayer::Enter(void)
//{
//	Activate();
//	CBaseCharacter::LoadAnimations("resource/Char Walk.xml");
//	m_footsteps.Load("Resource/data/leafyburst.xml");
//}
//
//// Input
//void TestPlayer::Input(void)
//{
//	int nOffsetX, nOffsetY;
//	nOffsetX = nOffsetY = 0;
//
//	if(CInputManager::GetInstance()->GetLeft())
//	{
//		SetCurrentAnimation(ANM_WALK_LEFT);
//		nOffsetX = -2;
//	}
//	if(CInputManager::GetInstance()->GetRight())
//	{
//		SetCurrentAnimation(ANM_WALK_RIGHT);
//		nOffsetX = 2;
//
//	}
//	if(CInputManager::GetInstance()->GetUp())
//	{
//		SetCurrentAnimation(ANM_WALK_UP);
//		nOffsetY = -2;
//	}
//	if(CInputManager::GetInstance()->GetDown())
//	{
//		SetCurrentAnimation(ANM_WALK_DOWN);
//		nOffsetY = 2;
//	}
//
//	/*if(nNewPosY < GetPosY() && nNewPosX < GetPosX())
//	{
//		SetCurrentAnimation(ANM_WALK_LEFT);
//	}
//	else if(nNewPosY < GetPosY() && nNewPosX > GetPosX())
//	{
//		SetCurrentAnimation(ANM_WALK_RIGHT);
//	}
//	else if(nNewPosY < GetPosY())
//	{
//		SetCurrentAnimation(ANM_WALK_UP);
//	}
//	else if(nNewPosY > GetPosY() && nNewPosX < GetPosX())
//	{
//		SetCurrentAnimation(ANM_WALK_LEFT);
//	}
//	else if(nNewPosY > GetPosY() && nNewPosX > GetPosX())
//	{
//		SetCurrentAnimation(ANM_WALK_RIGHT);
//	}
//	else if(nNewPosY > GetPosY())
//	{
//		SetCurrentAnimation(ANM_WALK_DOWN);
//	}*/
//
//	//if(nNewPosX != GetPosX() || nNewPosY != GetPosY())
//	//	m_footsteps.Fire(
//	//	SCREEN_POS_X((int)nNewPosX),
//	//	SCREEN_POS_Y((int)nNewPosY));
//
//	//TestPlayer test;
//	//test.Enter();
//	//test.SetPosX(nNewPosX);
//	//test.SetPosY(nNewPosY);
//
//	RectD CollisionRect = GetCollisionRect();
//	CollisionRect.left += nOffsetX;
//	CollisionRect.right += nOffsetX;
//	CollisionRect.top += nOffsetY;
//	CollisionRect.bottom += nOffsetY;
//
//	//SetPosX(nNewPosX);
//	//SetPosY(nNewPosY);
//
//	if(!WORLD->CheckCollisions(CollisionRect.GetWindowsRECT(), GetType()))
//	{
//		SetPosX(GetPosX() + nOffsetX);
//		SetPosY(GetPosY() + nOffsetY);
//	}
//}
//
////// Draw to the screen
////void TestPlayer::Render(void)
////{
////	//TEX_MNG->Draw(m_uiSpriteIndex, GetPosX(), GetPosY());
////
////	CBaseObject::Render();
////
////	/*GetAnimationPlayer(m_uiCurrentAnimation)->Render(
////		SCREEN_POS_X((int)GetPosX()),
////		SCREEN_POS_Y((int)GetPosY()));
////	m_footsteps.Render();*/
////}
////
////void TestPlayer::Update(float fElapsedTime)
////{
////	CBaseCharacter::Update(fElapsedTime);
////
////	//GetAnimationPlayer(m_uiCurrentAnimation)->Update(fElapsedTime);
////	//m_footsteps.Update(fElapsedTime);
////}
////
////// Get the rectangle used for collision
////RectD TestPlayer::GetCollisionRect(void) const
////{
////	return CBaseCharacter::GetCollisionRect();
////
////	//RectD rectCollision = m_pAnimation[m_uiCurrentAnimation]->ReturnCollisionRect();
////	//Point anchor = m_pAnimation[m_uiCurrentAnimation]->ReturnAnchorPoint();
////
////	//rectCollision.top += GetPosY() - anchor.y;
////	//rectCollision.left += GetPosX() - anchor.x;
////	//rectCollision.bottom += GetPosY() - anchor.y;
////	//rectCollision.right += GetPosX() - anchor.x;
////
////	//return rectCollision;
////}
