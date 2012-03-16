////////////////////////////////////////////////////////////////////////
//    File Name				:	"CFireball.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	3/01/12
//    Purpose				:	Arrow
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CFireball.h"
#include "../Game Objects/CEnemy.h"
#include "../Game Objects/CPlayer.h"
#include "../Game Objects/CObjectManager.h"
#include "../Weapons/CCrossBow.h"
#include "../Messaging/CMessageSystem.h"
#include "../Messaging/CEventSystem.h"

CFireball::CFireball()
{
	SetHeight(32);
	SetWidth(32);
	SetImageID(TEX_MNG->LoadTexture("resource/Fireball.png"));
	timeout = 0;
}
void CFireball::Update(float fElapsedTime)
{
	CBaseObject::Update(fElapsedTime);
	timeout += fElapsedTime;
	if(timeout > 2.0f)
		CMessageSystem::GetInstance()->SendMsg(new CDestroyObjectMessage(this));
}
void CFireball::Render(void)
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
bool CFireball::CheckCollision(IBaseInterface* pObject)
{
	RECT rectCollisionResult = { 0, 0, 0, 0 };
	CBaseObject* pBaseObject = (CBaseObject*)pObject;
	if(IntersectRect(&rectCollisionResult, &GetCollisionRect().GetWindowsRECT(), &pBaseObject->GetCollisionRect().GetWindowsRECT()))
	{
		if(pObject->GetType() == TYPE_CHAR_PLAYER)
		{
			((CPlayer*)pObject)->SufferDamage(1);
			CMessageSystem::GetInstance()->SendMsg(new CDestroyObjectMessage(this));
		}
		
		//if(pObject->GetType() != TYPE_CHAR_PLAYER && pObject->GetType() != TYPE_WEAPON_ARROW)
		//{
		//	CMessageSystem::GetInstance()->SendMsg(new CDestroyObjectMessage(this));
		//}
		return true;
	}
	return false;
}
