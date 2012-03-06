////////////////////////////////////////////////////////////////////////
//    File Name				:	"CChest.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/09/12 - 3:57 AM
//    Purpose				:	CChest
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CChest.h"
CChest::CChest(const char* szName, bool bActiveTalk, double dRange, int sndNPC,double dPositionX, double dPositionY, unsigned int uiSpeed,
	int nImageID, unsigned int uiWidth, unsigned int uiHeight, bool bActive,unsigned int uiMaxHealth, unsigned int uiAttackDamage) 
	: CNPC(szName,bActiveTalk,dRange,sndNPC,dPositionX,dPositionY,uiSpeed,nImageID,uiWidth,uiHeight,bActive,uiMaxHealth,uiAttackDamage)
{
	
}
void CChest::LoadAnimations(char const * const szFilename)
{
	CNPC::LoadAnimations(szFilename);
	GetAnimationPlayer(GetCurrentAnimation())->SetLooping(false);
	GetAnimationPlayer(GetCurrentAnimation())->Stop();
}
void CChest::Render(void)
{
	CNPC::Render();
}
CChest::~CChest()
{

}
void CChest::OpenChest(void)
{
	GetAnimationPlayer(GetCurrentAnimation())->Play();
}