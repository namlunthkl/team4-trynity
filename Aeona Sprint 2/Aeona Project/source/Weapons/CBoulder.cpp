////////////////////////////////////////////////////////////////////////
//    File Name				:	"CBoulder.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	3/01/12
//    Purpose				:	Arrow
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CBoulder.h"
#include "../Game Objects/CEnemy.h"
#include "../Game Objects/CObjectManager.h"
#include "../Weapons/CCrossBow.h"
#include "../Messaging/CMessageSystem.h"
#include "../Messaging/CEventSystem.h"
CBoulder::CBoulder()
{
	SetWidth(64);
	SetHeight(64);
	timeout = 0;
}
void CBoulder::Update(float fElapsedTime)
{
	CBaseObject::Update(fElapsedTime);
	timeout += fElapsedTime;
	if(timeout > 2.0f)
		CMessageSystem::GetInstance()->SendMsg(new CDestroyObjectMessage(this));
}
void CBoulder::Render(void)
{
	RectD temp(0,0,GetWidth(),GetHeight());
	
	TEX_MNG->Draw(GetImageID(), (int)GetPosX(), (int)GetPosY(),1.0f,1.0f);
}
bool CBoulder::CheckCollision(IBaseInterface* pObject)
{
	RECT rectCollisionResult = { 0, 0, 0, 0 };
	CBaseObject* pBaseObject = (CBaseObject*)pObject;
	if(IntersectRect(&rectCollisionResult, &GetCollisionRect().GetWindowsRECT(), &pBaseObject->GetCollisionRect().GetWindowsRECT()))
	{
		if(pObject->GetType() == TYPE_CHAR_ENEMY)
		//	((CEnemy*)pObject)->SufferDamage(CPlayer::GetInstance()->GetAttackDamage());

		//if(pObject->GetType() != TYPE_CHAR_PLAYER && pObject->GetType() != TYPE_WEAPON_ARROW)
		//{
		//	CMessageSystem::GetInstance()->SendMsg(new CDestroyObjectMessage(this));
		//}
		return true;
	}
	return false;
}
