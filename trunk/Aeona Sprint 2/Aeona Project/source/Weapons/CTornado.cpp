////////////////////////////////////////////////////////////////////////
//    File Name				:	"CTornado.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	3/01/12
//    Purpose				:	Arrow
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CTornado.h"
#include "../Game Objects/CEnemy.h"
#include "../Game Objects/CPlayer.h"
#include "../Game Objects/CObjectManager.h"
#include "../Weapons/CCrossBow.h"
#include "../Messaging/CMessageSystem.h"
#include "../Messaging/CEventSystem.h"
CTornado::CTornado()
{
	SetHeight(40);
	SetWidth(32);
	SetImageID(TEX_MNG->LoadTexture("resource/Tornado.png"));
	timeout = 0;
}
void CTornado::Update(float fElapsedTime)
{
	CBaseObject::Update(fElapsedTime);
	timeout += fElapsedTime;
	if(timeout > 2.0f)
		CMessageSystem::GetInstance()->SendMsg(new CDestroyObjectMessage(this));
}
void CTornado::Render(void)
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
bool CTornado::CheckCollision(IBaseInterface* pObject)
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
RectD CTornado::GetCollisionRect(void)
{
	RectD rectCollision;

	rectCollision.left = GetPosX() + 14;
	rectCollision.top = GetPosY() + 102;
	rectCollision.right = rectCollision.left + 8;
	rectCollision.bottom = rectCollision.top + 17;

	return rectCollision;
}