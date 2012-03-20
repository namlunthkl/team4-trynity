////////////////////////////////////////////////////////////////////////
//    File Name				:	"CArrow.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	3/01/12
//    Purpose				:	Arrow
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CArrow.h"
#include "../Game Objects/CPlayer.h"
#include "../Game Objects/CObjectManager.h"
#include "../Weapons/CCrossBow.h"
#include "../Messaging/CMessageSystem.h"
#include "../Messaging/CEventSystem.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CFinalBoss.h"

#include "..\Camera\CCameraControl.h"
#include "..\CGame.h"
CArrow::CArrow()
{
	timeout = 0;
}
void CArrow::Update(float fElapsedTime)
{
	CBaseObject::Update(fElapsedTime);
	timeout += fElapsedTime;
	if(timeout > 0.50f)
		CMessageSystem::GetInstance()->SendMsg(new CDestroyObjectMessage(this));
}
void CArrow::Render(void)
{
	RectD temp(0,0,GetWidth(),GetHeight());
	if(GetVelX() == 0 && GetVelY() > 0)
		TEX_MNG->Draw(GetImageID(), (int)GetPosX(), (int)GetPosY(),1.0f,1.0f,&temp.GetWindowsRECT(),GetWidth()*0.5f,GetHeight()*0.5f,3.14f*2.0f);
	else if(GetVelX() == 0 && GetVelY() < 0)
		TEX_MNG->Draw(GetImageID(), (int)GetPosX(), (int)GetPosY(),1.0f,1.0f,&temp.GetWindowsRECT(),GetWidth()*0.5f,GetHeight()*0.5f,3.14f*1.0f);
	else if(GetVelX() < 0 && GetVelY() == 0)
		TEX_MNG->Draw(GetImageID(), (int)GetPosX(), (int)GetPosY(),1.0f,1.0f,&temp.GetWindowsRECT(),GetWidth()*0.5f,GetHeight()*0.5f,3.14f*0.5f);
	else if(GetVelX() > 0 && GetVelY() == 0)
		TEX_MNG->Draw(GetImageID(), (int)GetPosX(), (int)GetPosY(),1.0f,1.0f,&temp.GetWindowsRECT(),GetWidth()*0.5f,GetHeight()*0.5f,-3.14f*0.5f);
}
bool CArrow::CheckCollision(IBaseInterface* pObject)
{
	RECT rectCollisionResult = { 0, 0, 0, 0 };
	CBaseObject* pBaseObject = (CBaseObject*)pObject;
	if(IntersectRect(&rectCollisionResult, &GetCollisionRect().GetWindowsRECT(), &pBaseObject->GetCollisionRect().GetWindowsRECT()))
	{
		if(pObject->GetType() == TYPE_CHAR_ENEMY )
		{
			CMessageSystem::GetInstance()->SendMsg(new CDestroyObjectMessage(this));
			((CEnemy*)pObject)->SufferDamage(CPlayer::GetInstance()->GetAttackDamage());
		}
		if(pObject->GetType() == TYPE_CHAR_FINALBOSS)
		{
			CMessageSystem::GetInstance()->SendMsg(new CDestroyObjectMessage(this));
			((CFinalBoss*)pObject)->SufferDamage(CPlayer::GetInstance()->GetAttackDamage());
		}
		//if(pObject->GetType() != TYPE_CHAR_PLAYER && pObject->GetType() != TYPE_WEAPON_ARROW)
		//{
		//	CMessageSystem::GetInstance()->SendMsg(new CDestroyObjectMessage(this));
		//}
		return true;
	}
	return false;
}
RectD CArrow::GetCollisionRect(void)
{
	RectD rectCollision;

	rectCollision.left = GetPosX() + 14;
	rectCollision.top = GetPosY() + 102;
	rectCollision.right = rectCollision.left + 8;
	rectCollision.bottom = rectCollision.top + 17;

	return rectCollision;
}