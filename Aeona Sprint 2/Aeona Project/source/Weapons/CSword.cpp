////////////////////////////////////////////////////////////////////////
//    File Name				:	"CSword.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	3/01/12
//    Purpose				:	CSword
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CSword.h"
#include "../Game Objects/CPlayer.h"
#include "../States/CGameplayState.h"
CSword::CSword()
{
	SetImageID(TEX_MNG->LoadTexture("resource/sword.png",D3DCOLOR_XRGB(255,0,255)));

}
void CSword::Attack(void)
{
	//
}
void CSword::Render()
{
	float y = GetRotation();
	float x = D3DXToRadian(-GetRotation());
	TEX_MNG->Draw(GetImageID(),SCREEN_POS_X(GetWeaponAnchor().x-8),SCREEN_POS_Y(GetWeaponAnchor().y-57),1.0f,1.0f,0,8,57,x);
}
void CSword::ChargedAttack(void)

{
	//
}
void CSword::SetWeaponRotation(float fWeaponRotation)
{
	SetRotation(fWeaponRotation);
}